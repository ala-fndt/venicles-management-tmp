#include "../include/view/VehicleCarouselWidget.hpp"
#include "../include/additionalScripts/Logger.hpp"
#include "../include/classes/Session.hpp"
#include "../include/classes/VehicleList.hpp"
#include "../include/database/Database.hpp"
#include <memory>

VehicleCarouselWidget::VehicleCarouselWidget(wxWindow *parent,
                                             Database *database, Logger *logger,
                                             IRefreshable *listToRefresh)
    : wxPanel(parent), m_database(database), m_logger(logger),
      m_listToRefresh(listToRefresh),
      m_selected(std::make_shared<VehicleSummary>()) {

  SetBackgroundColour(wxColour(17, 24, 39));
  wxBoxSizer *contentRow = new wxBoxSizer(wxHORIZONTAL);

  // ----------------------------------------------------------------
  // LEWY PANEL: przewijalna lista aut
  // ----------------------------------------------------------------
  wxPanel *listContainer = new wxPanel(this, wxID_ANY);
  listContainer->SetBackgroundColour(wxColour(31, 41, 55));
  wxBoxSizer *listContainerSizer = new wxBoxSizer(wxVERTICAL);

  wxStaticText *listTitle =
      new wxStaticText(listContainer, wxID_ANY, "Lista aut");
  listTitle->SetForegroundColour(wxColour(255, 255, 255));
  listTitle->SetFont(
      wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

  m_scrollList = new wxScrolledWindow(
      listContainer, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL);
  m_scrollList->SetBackgroundColour(wxColour(31, 41, 55));
  m_scrollList->SetScrollRate(0, 10);

  m_scrollSizer = new wxBoxSizer(wxVERTICAL);
  m_scrollList->SetSizer(m_scrollSizer);

  listContainerSizer->Add(listTitle, 0, wxTOP | wxLEFT | wxRIGHT, 12);
  listContainerSizer->Add(m_scrollList, 1, wxEXPAND | wxALL, 8);
  listContainer->SetSizer(listContainerSizer);

  // ----------------------------------------------------------------
  // PRAWY PANEL: szczegoly wybranego auta
  // ----------------------------------------------------------------
  m_detailPanel = new wxPanel(this, wxID_ANY);
  m_detailPanel->SetBackgroundColour(wxColour(31, 41, 55));
  wxBoxSizer *detailSizer = new wxBoxSizer(wxVERTICAL);

  m_detailPlaceholder = new wxStaticText(
      m_detailPanel, wxID_ANY, "Wybierz auto z listy\naby zobaczyc szczegoly.",
      wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
  m_detailPlaceholder->SetForegroundColour(wxColour(107, 114, 128));
  m_detailPlaceholder->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT,
                                      wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

  m_detailBrand =
      new wxStaticText(m_detailPanel, wxID_ANY, "", wxDefaultPosition,
                       wxDefaultSize, wxALIGN_LEFT);
  m_detailBrand->SetForegroundColour(wxColour(255, 255, 255));
  m_detailBrand->SetFont(
      wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  m_detailBrand->Hide();

  m_detailYear =
      new wxStaticText(m_detailPanel, wxID_ANY, "", wxDefaultPosition,
                       wxDefaultSize, wxALIGN_LEFT);
  m_detailYear->SetForegroundColour(wxColour(156, 163, 175));
  m_detailYear->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                               wxFONTWEIGHT_NORMAL));
  m_detailYear->Hide();

  m_detailColor =
      new wxStaticText(m_detailPanel, wxID_ANY, "", wxDefaultPosition,
                       wxDefaultSize, wxALIGN_LEFT);
  m_detailColor->SetForegroundColour(wxColour(156, 163, 175));
  m_detailColor->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                                wxFONTWEIGHT_NORMAL));
  m_detailColor->Hide();

  m_reserveBtn = new wxButton(m_detailPanel, wxID_ANY, "Zarezerwuj auto");
  m_reserveBtn->SetBackgroundColour(wxColour(59, 130, 246));
  m_reserveBtn->SetForegroundColour(wxColour(255, 255, 255));
  m_reserveBtn->SetFont(
      wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  m_reserveBtn->Hide();

  detailSizer->AddStretchSpacer(1);
  detailSizer->Add(m_detailPlaceholder, 0, wxALIGN_CENTER | wxALL, 16);
  detailSizer->Add(m_detailBrand, 0, wxLEFT | wxRIGHT | wxTOP, 20);
  detailSizer->Add(m_detailYear, 0, wxLEFT | wxRIGHT | wxTOP, 20);
  detailSizer->Add(m_detailColor, 0, wxLEFT | wxRIGHT | wxTOP, 20);
  detailSizer->AddStretchSpacer(1);
  detailSizer->Add(m_reserveBtn, 0, wxALIGN_CENTER | wxBOTTOM, 20);
  m_detailPanel->SetSizer(detailSizer);

  m_reserveBtn->Bind(wxEVT_BUTTON, [this](wxCommandEvent &) {
    if (m_selected->id <= 0)
      return;

    Session &session = Session::getInstance();
    if (!session.isLogged()) {
      wxMessageBox("Musisz byc zalogowany aby zarezerwowac auto.", "Blad",
                   wxOK | wxICON_WARNING);
      return;
    }

    const int userId = session.getUserId();
    const int vehicleId = m_selected->id;

    wxDateTime now = wxDateTime::Now();
    std::string date = now.Format("%Y-%m-%d").ToStdString();

    m_database->executeQuery(
        "INSERT OR IGNORE INTO userVehicle (idUser, idVehicle, date) "
        "VALUES(" +
        std::to_string(userId) + ", " + std::to_string(vehicleId) + ", '" +
        date + "');");

    m_database->executeQuery(
        "INSERT OR IGNORE INTO rentalHistory (idUser, idVehicle, date) "
        "VALUES(" +
        std::to_string(userId) + ", " + std::to_string(vehicleId) + ", '" +
        date + "');");

    wxMessageBox(wxString::Format("Zarezerwowano: %s %s", m_selected->brand,
                                  m_selected->model),
                 "Sukces", wxOK | wxICON_INFORMATION);

    m_selected->id = 0;
    m_detailBrand->Hide();
    m_detailYear->Hide();
    m_detailColor->Hide();
    m_reserveBtn->Hide();
    m_detailPlaceholder->Show();
    m_detailPanel->Layout();
    m_detailPanel->Refresh();

    rebuildList();

    if (m_listToRefresh)
      m_listToRefresh->refresh();
  });

  contentRow->Add(listContainer, 1, wxEXPAND | wxALL, 10);
  contentRow->Add(m_detailPanel, 2, wxEXPAND | wxALL, 10);
  SetSizer(contentRow);

  rebuildList();
}

void VehicleCarouselWidget::rebuildList() {
  VehicleList vehicleList(m_database, m_logger);
  vehicleList.initList("SELECT v.id, v.brand, v.model, v.year, v.color "
                       "FROM vehicle v "
                       "WHERE v.id NOT IN (SELECT idVehicle FROM userVehicle) "
                       "ORDER BY v.id;");
  const std::vector<VehicleSummary> vehicles = vehicleList.getList();

  m_scrollList->DestroyChildren();
  m_scrollSizer->Clear(false);

  if (vehicles.empty()) {
    wxStaticText *emptyLabel =
        new wxStaticText(m_scrollList, wxID_ANY, "Brak dostepnych aut");
    emptyLabel->SetForegroundColour(wxColour(156, 163, 175));
    m_scrollSizer->Add(emptyLabel, 0, wxALL, 12);
  }

  for (size_t i = 0; i < vehicles.size(); ++i) {
    VehicleSummary v = vehicles[i];

    wxPanel *row = new wxPanel(m_scrollList, wxID_ANY);
    row->SetBackgroundColour(wxColour(55, 65, 81));
    row->SetCursor(wxCURSOR_HAND);
    wxBoxSizer *rowSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText *rowTitle = new wxStaticText(
        row, wxID_ANY, wxString::Format("%s %s", v.brand, v.model));
    rowTitle->SetForegroundColour(wxColour(255, 255, 255));
    rowTitle->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                             wxFONTWEIGHT_BOLD));

    wxStaticText *rowSub = new wxStaticText(
        row, wxID_ANY,
        wxString::Format("Rok: %s | Kolor: %s", v.year, v.color));
    rowSub->SetForegroundColour(wxColour(156, 163, 175));
    rowSub->SetFont(wxFont(9, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                           wxFONTWEIGHT_NORMAL));

    rowSizer->Add(rowTitle, 0, wxLEFT | wxTOP | wxRIGHT, 10);
    rowSizer->Add(rowSub, 0, wxLEFT | wxBOTTOM | wxRIGHT, 10);
    row->SetSizer(rowSizer);

    auto showDetail = [this, v](wxMouseEvent &) {
      *m_selected = v;
      m_detailPlaceholder->Hide();
      m_detailBrand->SetLabel(wxString::Format("%s %s", v.brand, v.model));
      m_detailYear->SetLabel(wxString::Format("Rok produkcji: %s", v.year));
      m_detailColor->SetLabel(wxString::Format("Kolor: %s", v.color));
      m_detailBrand->Show();
      m_detailYear->Show();
      m_detailColor->Show();
      m_reserveBtn->Show();
      m_detailPanel->Layout();
    };

    row->Bind(wxEVT_LEFT_DOWN, showDetail);
    rowTitle->Bind(wxEVT_LEFT_DOWN, showDetail);
    rowSub->Bind(wxEVT_LEFT_DOWN, showDetail);

    m_scrollSizer->Add(row, 0, wxEXPAND | wxBOTTOM, 6);
  }

  m_scrollList->FitInside();
  m_scrollList->Layout();
  GetParent()->Layout();
}
