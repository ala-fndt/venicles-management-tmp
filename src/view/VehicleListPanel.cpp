#include "../include/view/VehicleListPanel.hpp"
#include "../include/classes/VehicleList.hpp"
#include "../include/classes/Session.hpp"

namespace {
wxString toWx(const std::string &text) {
  return wxString::From8BitData(text.c_str());
}
} // namespace

VehicleListPanel::VehicleListPanel(wxWindow *parent, Database *database,
                                   Logger *logger)
    : wxPanel(parent), m_database(database), m_logger(logger) {
  SetBackgroundColour(wxColour(31, 41, 55));

  wxBoxSizer *rootSizer = new wxBoxSizer(wxVERTICAL);

  wxStaticText *title =
      new wxStaticText(this, wxID_ANY, "Vehicle list", wxDefaultPosition,
                       wxDefaultSize, wxALIGN_LEFT);
  title->SetForegroundColour(wxColour(255, 255, 255));
  title->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                        wxFONTWEIGHT_BOLD));

  wxScrolledWindow *scrollArea = new wxScrolledWindow(
      this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL);
  scrollArea->SetBackgroundColour(wxColour(31, 41, 55));
  scrollArea->SetScrollRate(0, 10);

  wxBoxSizer *listSizer = new wxBoxSizer(wxVERTICAL);

  m_scrollArea = scrollArea;
  m_listSizer = listSizer;

  scrollArea->SetSizer(listSizer);
  scrollArea->FitInside();

  rootSizer->Add(title, 0, wxTOP | wxLEFT | wxRIGHT, 12);
  rootSizer->Add(scrollArea, 1, wxEXPAND | wxALL, 10);
  SetSizer(rootSizer);

  refresh();
}

void VehicleListPanel::refresh() {
  VehicleList vehicleList(m_database, m_logger);
  vehicleList.initList(
      "SELECT v.id, v.brand, v.model, v.year, v.color "
      "FROM vehicle v "
      "WHERE v.id IN (SELECT idVehicle FROM userVehicle WHERE idUser = " +
      std::to_string(Session::getInstance().getUserId()) +
      ") ORDER BY v.id;");
  populateList(vehicleList.getList());
}

void VehicleListPanel::clearList() {
  m_scrollArea->DestroyChildren();
  m_listSizer->Clear(false);
}

void VehicleListPanel::populateList(const std::vector<VehicleSummary> &vehicles) {
  clearList();

  if (vehicles.empty()) {
    wxStaticText *emptyLabel =
        new wxStaticText(scrollArea, wxID_ANY, "No vehicles in the database");
        new wxStaticText(m_scrollArea, wxID_ANY, "Brak aut w bazie");
    emptyLabel->SetForegroundColour(wxColour(156, 163, 175));
    m_listSizer->Add(emptyLabel, 0, wxALL, 8);
  }

  for (size_t i = 0; i < vehicles.size(); ++i) {
    wxPanel *vehicleItem = new wxPanel(m_scrollArea, wxID_ANY);
    vehicleItem->SetBackgroundColour(wxColour(55, 65, 81));

    wxBoxSizer *itemSizer = new wxBoxSizer(wxVERTICAL);
    wxString itemTitleText =
      "Vehicle " + wxString::Format("%d", static_cast<int>(i + 1)) + ": " +
      toWx(vehicles[i].brand) + " " +
      toWx(vehicles[i].model);
    wxStaticText *itemTitle =
      new wxStaticText(vehicleItem, wxID_ANY, itemTitleText);
    itemTitle->SetForegroundColour(wxColour(255, 255, 255));
    itemTitle->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                              wxFONTWEIGHT_BOLD));

    wxString itemSubtitleText = "Year: " + toWx(vehicles[i].year) +
            " | Color: " + toWx(vehicles[i].color);
    wxStaticText *itemSubtitle =
      new wxStaticText(vehicleItem, wxID_ANY, itemSubtitleText);
    itemSubtitle->SetForegroundColour(wxColour(156, 163, 175));

    itemSizer->Add(itemTitle, 0, wxALL, 8);
    itemSizer->Add(itemSubtitle, 0, wxLEFT | wxRIGHT | wxBOTTOM, 8);
    vehicleItem->SetSizer(itemSizer);

    m_listSizer->Add(vehicleItem, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 8);
  }

  m_scrollArea->FitInside();
  m_scrollArea->Layout();
}
