#include "../include/controller/HomeController.hpp"
#include "../include/classes/Router.hpp"
#include "../include/classes/Session.hpp"

HomeController::HomeController(HomeView *view, HomeModel *model, Router *router)
    : _view(view), _model(model), router(router) {

  _view->logoutBtn->Bind(wxEVT_BUTTON, &HomeController::OnLogoutClicked, this);
  _view->userPageBtn->Bind(wxEVT_BUTTON, &HomeController::OnUserPageClicked,
                           this);
}

HomeController::~HomeController() = default;

void HomeController::OnLogoutClicked(wxCommandEvent &event) {
  Session::getInstance().logout();

  this->router->navigate("login");
}

void HomeController::OnUserPageClicked(wxCommandEvent &event) {
  this->router->navigate("userPage");
};
