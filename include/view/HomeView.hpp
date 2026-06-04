#ifndef HOMEVIEW_HPP
#define HOMEVIEW_HPP

#include "../include/view/VehicleCarouselWidget.hpp"
#include <wx/wx.h>

class Router;
class Database;
class Logger;

class HomeView : public wxPanel {
private:
  Router *router;

public:
  wxButton *logoutBtn;
  wxButton *userPageBtn;

  HomeView(wxWindow *window, Router *router, Database *database,
           Logger *logger);

  void change();
};

#endif // !HOMEVIEW_HPP
