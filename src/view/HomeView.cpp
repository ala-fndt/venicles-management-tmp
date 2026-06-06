#include "../include/view/HomeView.hpp"
#include "../include/additionalScripts/Logger.hpp"
#include "../include/database/Database.hpp"

static Logger *g_homeLogger = nullptr;

HomeView::HomeView(wxWindow *window, Router *router, Database *database,
                   Logger *logger)
    : wxPanel(window), router(router), carousel(nullptr) {
  g_homeLogger = logger;
  if (g_homeLogger) {
    g_homeLogger->log(LogLevel::Debug, "HomeView: constructor start");
  }
  SetBackgroundColour(wxColour(17, 24, 39));
  SetForegroundColour(wxColour(229, 231, 235));

  wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *titleRow = new wxBoxSizer(wxHORIZONTAL);

  wxStaticText *labelTitle = new wxStaticText(this, wxID_ANY, "Home page");
  labelTitle->SetForegroundColour(wxColour(255, 255, 255));

  logoutBtn = new wxButton(this, wxID_ANY, "Log out");
  logoutBtn->SetBackgroundColour(wxColour(55, 65, 81));
  logoutBtn->SetForegroundColour(wxColour(255, 255, 255));
  logoutBtn->SetFont(
      wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

  userPageBtn = new wxButton(this, wxID_ANY, "Your account");
  userPageBtn->SetBackgroundColour(wxColour(55, 65, 81));
  userPageBtn->SetForegroundColour(wxColour(255, 255, 255));
  userPageBtn->SetFont(
      wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

  titleRow->Add(labelTitle, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
  titleRow->AddStretchSpacer(1);
  titleRow->Add(logoutBtn, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
  titleRow->Add(userPageBtn, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

  mainSizer->Add(titleRow, 0, wxEXPAND | wxALL, 5);

  carousel = new VehicleCarouselWidget(this, database, logger);
  if (g_homeLogger) {
    g_homeLogger->log(LogLevel::Debug, "HomeView: carousel created");
  }
  mainSizer->Add(carousel, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5);

  this->SetSizer(mainSizer);
  mainSizer->Fit(this);
  if (g_homeLogger) {
    g_homeLogger->log(LogLevel::Debug, "HomeView: constructor end");
  }
}

void HomeView::refresh() {
  if (g_homeLogger) {
    g_homeLogger->log(LogLevel::Debug, "HomeView: refresh start");
  }

  if (carousel) {
    carousel->refreshVehicles();
  }

  Layout();
  if (g_homeLogger) {
    g_homeLogger->log(LogLevel::Debug, "HomeView: refresh end");
  }
}
