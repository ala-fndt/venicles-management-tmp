#include "../include/controller/HomeController.hpp"
#include "../include/classes/Router.hpp"
#include "../include/classes/Session.hpp"

HomeController::HomeController(HomeView *view, HomeModel *model, Router *router)
    : _view(view), _model(model), router(router) {
  if (_view && _view->logoutBtn) {
    _view->logoutBtn->Bind(wxEVT_BUTTON, &HomeController::OnLogoutClicked,
                           this);
  } else if (router && router->logger) {
    router->logger->log(LogLevel::Warning,
                        "HomeController: logoutBtn is null");
  }
  if (_view && _view->userPageBtn) {
    _view->userPageBtn->Bind(wxEVT_BUTTON, &HomeController::OnUserPageClicked,
                             this);
  } else if (router && router->logger) {
    router->logger->log(LogLevel::Warning,
                        "HomeController: userPageBtn is null");
  }
}

HomeController::~HomeController() = default;

void HomeController::OnLogoutClicked(wxCommandEvent &event) {
  Session::getInstance().logout();

  this->router->navigate("login");
}

void HomeController::OnUserPageClicked(wxCommandEvent &event) {
  this->router->navigate("userPage");
};
