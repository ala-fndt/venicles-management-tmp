#include "../include/view/VehicleListPanel.hpp"

VehicleListPanel::VehicleListPanel(wxWindow *parent,
                   const std::vector<VehicleSummary> &vehicles)
    : wxPanel(parent) {
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
    wxStaticText *itemTitle = new wxStaticText(
        vehicleItem, wxID_ANY,
        wxString::Format("Auto %d: %s %s", static_cast<int>(i + 1),
                         vehicles[i].brand, vehicles[i].model));
    itemTitle->SetForegroundColour(wxColour(255, 255, 255));
    itemTitle->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                              wxFONTWEIGHT_BOLD));

    wxStaticText *itemSubtitle = new wxStaticText(
        vehicleItem, wxID_ANY,
        wxString::Format("Rok: %s | Kolor: %s", vehicles[i].year,
                         vehicles[i].color));
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
