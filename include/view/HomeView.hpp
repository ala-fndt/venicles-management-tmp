#ifndef HOMEVIEW_HPP
#define HOMEVIEW_HPP

#include "../include/classes/IRefreshable.hpp"
#include "../include/view/VehicleCarouselWidget.hpp"
#include <wx/wx.h>

class Router;
class Database;
class Logger;

class HomeView : public wxPanel, public IRefreshable {
private:
  Router *router;
  VehicleCarouselWidget *carousel;

public:
  wxButton *logoutBtn;
  wxButton *userPageBtn;

  HomeView(wxWindow *window, Router *router, Database *database,
           Logger *logger);

  void change();
  void refresh() override;
};

#endif // !HOMEVIEW_HPP
