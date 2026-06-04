#include "../../include/classes/Router.hpp"
#include "../../include/classes/IRefreshable.hpp"

Router::Router(wxWindow *container, Logger *logger)
    : container(container), logger(logger) {}

Router::~Router() = default;

// TODO: dodanie json-a z opcjami np: debug: on/off ect
bool Router::findRoute(const std::string &name, bool isSilent) {
  auto search_elem = routes.find(name);

  if (search_elem != routes.end()) {
    if (!isSilent) {
      logger->log(LogLevel::Info, "Element " + name + " istnieje w routerze");
    }

    return true;
  } else {
    if (!isSilent) {
      logger->log(LogLevel::Info,
                  "Element " + name + " nie istnieje w routerze");
    }
    return false;
  }
}

void Router::add(const std::string &name, wxWindow *window) {

  if (!findRoute(name, true)) {
    routes.insert({name, window});
    logger->log(LogLevel::Info, "Pomyslnie dodano element route: " + name);
  } else {
    logger->log(LogLevel::Info, "Nie udalo sie dodac elementu route: " + name +
                                    ". Element juz istnieje.");
  }
}

void Router::remove(std::string name) {

  if (findRoute(name, true)) {
    routes.erase(name);

    logger->log(LogLevel::Info, "Pomyslnie usunieto route: " + name);
  } else {
    logger->log(LogLevel::Error,
                "Nie udalo sie usunac elementu route: " + name);
  }
}

void Router::navigate(std::string name) {
  if (!findRoute(name, true)) {
    logger->log(LogLevel::Error,
                "Element " + name + " nie istnieje w routerze.");
    return;
  }

  if (!current.empty() && routes[current]) {
    routes[current]->Hide();
  }

  if (routes[name] == nullptr) {
    logger->log(LogLevel::Error, "Element " + name + " jest `nullptr`.");
    return;
  }

  if (auto *refreshable = dynamic_cast<IRefreshable *>(routes[name])) {
    refreshable->refresh();
  }
  routes[name]->Show();

  container->Layout();
  container->Refresh();
  container->Update();
  current = name;
}

void Router::showAllRoutes() {
  int index = 1;
  for (const auto &route : routes) {
    logger->log(LogLevel::Debug,
                std::to_string(index) + ".router: " + route.first);
    index++;
  }
}
