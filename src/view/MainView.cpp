#include "../include/view/MainView.hpp"
#include "../include/additionalScripts/Validator.hpp"
#include "../include/classes/Router.hpp"
#include "../include/controller/HomeController.hpp"
#include "../include/controller/LoginController.hpp"
#include "../include/controller/RegisterController.hpp"
#include "../include/controller/UserPageController.hpp"
#include "../include/database/Database.hpp"
#include "../include/model/HomeModel.hpp"
#include "../include/model/LoginModel.hpp"
#include "../include/model/RegisterModel.hpp"
#include "../include/model/UserPageModel.hpp"
#include "../include/view/HomeView.hpp"
#include "../include/view/LoginView.hpp"
#include "../include/view/RegisterView.hpp"
#include "../include/view/UserPageView.hpp"
#include <memory>

MainView::MainView(Logger *logger, Database *database)
    : wxFrame(NULL, wxID_ANY, "Venicle Management App") {
  this->database = database;
  this->logger = logger;
  SetClientSize(wxSize(600, 400));

  validator = std::make_unique<Validator>(*logger);

  container = new wxPanel(this);
  router = std::make_unique<Router>(container, logger);

  loginModel = std::make_unique<LoginModel>(database, logger);
  registerModel = std::make_unique<RegisterModel>(database, logger);

  loginView = new LoginView(container, router.get(), validator.get());
  registerView = new RegisterView(container, router.get(), validator.get());

  loginController = std::make_unique<LoginController>(
      loginModel.get(), loginView, router.get(), this->database, this->logger,
      validator.get(), this);

  registerController = std::make_unique<RegisterController>(
      registerModel.get(), registerView, router.get(), this->logger,
      validator.get());

  router->add("login", loginView);
  router->add("register", registerView);

  registerView->Hide();

  containerSizer = new wxBoxSizer(wxVERTICAL);
  containerSizer->Add(loginView, 1, wxEXPAND);
  containerSizer->Add(registerView, 1, wxEXPAND);
  container->SetSizer(containerSizer);

  wxBoxSizer *frameSizer = new wxBoxSizer(wxVERTICAL);
  frameSizer->Add(container, 1, wxEXPAND);
  this->SetSizer(frameSizer);

  router->navigate("login");
  container->Layout();
  this->Layout();
  this->Centre(wxBOTH);
  this->Raise();
  this->Update();
}

void MainView::initViews() {
    logger->log(LogLevel::Debug, "initViews: start");
  homeModel = std::make_unique<HomeModel>(database, logger);
    logger->log(LogLevel::Debug, "initViews: homeModel created");
  userPageModel = std::make_unique<UserPageModel>(database, logger);
    logger->log(LogLevel::Debug, "initViews: userPageModel created");

  homeView = new HomeView(container, router.get(), database, logger);
    logger->log(LogLevel::Debug, "initViews: homeView created");
  userPageView = new UserPageView(container, validator.get(), userPageModel.get());
    logger->log(LogLevel::Debug, "initViews: userPageView created");

    logger->log(LogLevel::Debug, "initViews: creating homeController");
    homeController =
      std::make_unique<HomeController>(homeView, homeModel.get(), router.get());
    logger->log(LogLevel::Debug, "initViews: homeController created");

    logger->log(LogLevel::Debug, "initViews: creating userPageController");
    userPageController = std::make_unique<UserPageController>(
      userPageView, userPageModel.get(), router.get(), validator.get());
    logger->log(LogLevel::Debug, "initViews: userPageController created");

  homeView->Hide();
  userPageView->Hide();

  router->add("home", homeView);
  router->add("userPage", userPageView);
    logger->log(LogLevel::Debug, "initViews: routes added");

  containerSizer->Add(homeView, 1, wxEXPAND);
  containerSizer->Add(userPageView, 1, wxEXPAND);
  container->Layout();

  router->navigate("home");
    logger->log(LogLevel::Debug, "initViews: navigated home");
}

MainView::~MainView() = default;
