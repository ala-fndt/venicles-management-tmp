#ifndef HOMEVIEW_HPP
#define HOMEVIEW_HPP

#include "../include/classes/IRefreshable.hpp"
#include "../include/view/VehicleCarouselWidget.hpp"
#include "../classes/Router.hpp"
#include "../model/HomeModel.hpp"
#include <wx/wx.h>

class Router;
class Database;
class Logger;

class HomeView : public wxPanel, public IRefreshable {
private:
  Router *router;
  HomeModel *model;
  VehicleCarouselWidget *carousel;

public:
  wxButton *logoutBtn;
  wxButton *userPageBtn;
  wxStaticText *accountBalanceLabel;

  HomeView(wxWindow *window, Router *router, HomeModel *model, Database *database,
           Logger *logger);

  void change();
  void refresh() override;
};

#endif // !HOMEVIEW_HPP
