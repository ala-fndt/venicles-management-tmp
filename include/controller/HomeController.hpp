#ifndef HOMECONTROLLER_HPP
#define HOMECONTROLLER_HPP

#include "../include/model/HomeModel.hpp"
#include "../include/view/HomeView.hpp"
#include <wx/event.h>

class Router;

class HomeController {
private:
  HomeView *_view;
  HomeModel *_model;

  void OnLogoutClicked(wxCommandEvent &event);
  void OnUserPageClicked(wxCommandEvent &event);

public:
  Router *router;
  HomeController(HomeView *view, HomeModel *model, Router *router);
  virtual ~HomeController();
};

#endif // !HOMECONTROLLER_HPP
