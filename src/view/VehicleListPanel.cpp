#include "../include/view/VehicleListPanel.hpp"

namespace {
wxString toWx(const std::string &text) {
  return wxString::From8BitData(text.c_str());
}
} // namespace

VehicleListPanel::VehicleListPanel(wxWindow *parent,
                   const std::vector<VehicleSummary> &vehicles)
    : wxPanel(parent) {
VehicleListPanel::VehicleListPanel(wxWindow *parent, Database *database,
                                   Logger *logger)
    : wxPanel(parent), m_database(database), m_logger(logger) {
  SetBackgroundColour(wxColour(31, 41, 55));

  wxBoxSizer *rootSizer = new wxBoxSizer(wxVERTICAL);

  wxStaticText *title =
      new wxStaticText(this, wxID_ANY, "Lista aut", wxDefaultPosition,
                       wxDefaultSize, wxALIGN_LEFT);
  title->SetForegroundColour(wxColour(255, 255, 255));
  title->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                        wxFONTWEIGHT_BOLD));

  wxScrolledWindow *scrollArea = new wxScrolledWindow(
      this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL);
  scrollArea->SetBackgroundColour(wxColour(31, 41, 55));
  scrollArea->SetScrollRate(0, 10);

  wxBoxSizer *listSizer = new wxBoxSizer(wxVERTICAL);

  if (vehicles.empty()) {
    wxStaticText *emptyLabel =
        new wxStaticText(scrollArea, wxID_ANY, "Brak aut w bazie");
    emptyLabel->SetForegroundColour(wxColour(156, 163, 175));
    listSizer->Add(emptyLabel, 0, wxALL, 8);
  }

  for (size_t i = 0; i < vehicles.size(); ++i) {
    wxPanel *vehicleItem = new wxPanel(scrollArea, wxID_ANY);
    vehicleItem->SetBackgroundColour(wxColour(55, 65, 81));

    wxBoxSizer *itemSizer = new wxBoxSizer(wxVERTICAL);
    wxString itemTitleText =
      "Auto " + wxString::Format("%d", static_cast<int>(i + 1)) + ": " +
      toWx(vehicles[i].brand) + " " +
      toWx(vehicles[i].model);
    wxStaticText *itemTitle =
      new wxStaticText(vehicleItem, wxID_ANY, itemTitleText);
    itemTitle->SetForegroundColour(wxColour(255, 255, 255));
    itemTitle->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                              wxFONTWEIGHT_BOLD));

    wxString itemSubtitleText = "Rok: " + toWx(vehicles[i].year) +
                  " | Kolor: " + toWx(vehicles[i].color);
    wxStaticText *itemSubtitle =
      new wxStaticText(vehicleItem, wxID_ANY, itemSubtitleText);
    itemSubtitle->SetForegroundColour(wxColour(156, 163, 175));

    itemSizer->Add(itemTitle, 0, wxALL, 8);
    itemSizer->Add(itemSubtitle, 0, wxLEFT | wxRIGHT | wxBOTTOM, 8);
    vehicleItem->SetSizer(itemSizer);

    listSizer->Add(vehicleItem, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 8);
  }

  scrollArea->SetSizer(listSizer);
  scrollArea->FitInside();

  rootSizer->Add(title, 0, wxTOP | wxLEFT | wxRIGHT, 12);
  rootSizer->Add(scrollArea, 1, wxEXPAND | wxALL, 10);
  SetSizer(rootSizer);
}
