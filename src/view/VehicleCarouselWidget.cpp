#include "../include/view/VehicleCarouselWidget.hpp"
#include "../include/classes/Session.hpp"
#include "../include/classes/VehicleList.hpp"
#include "../include/additionalScripts/Logger.hpp"
#include "../include/classes/Session.hpp"
#include "../include/classes/VehicleList.hpp"
#include "../include/database/Database.hpp"
#include <memory>

namespace {
wxString toWx(const std::string &text) {
    return wxString::From8BitData(text.c_str());
}
} // namespace

VehicleCarouselWidget::VehicleCarouselWidget(
        wxWindow *parent, Database *database, Logger *logger)
        : wxPanel(parent), database(database), logger(logger),
            reserveInfo(nullptr), selectedVehicleId(-1) {
    if (this->logger) {
        this->logger->log(LogLevel::Debug, "VehicleCarouselWidget: constructor start");
    }
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
  detailPanel = new wxPanel(this, wxID_ANY);
  detailPanel->SetBackgroundColour(wxColour(31, 41, 55));
  wxBoxSizer *detailSizer = new wxBoxSizer(wxVERTICAL);

  detailPlaceholder = new wxStaticText(
      detailPanel, wxID_ANY,
      "Wybierz auto z listy\naby zobaczyc szczegoly.",
      wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
  detailPlaceholder->SetForegroundColour(wxColour(107, 114, 128));
  detailPlaceholder->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT,
                                    wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

  // Etykiety szczegolow (ukryte dopoki nie wybrano auta)
  detailBrand = new wxStaticText(detailPanel, wxID_ANY, "",
      wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
  detailBrand->SetForegroundColour(wxColour(255, 255, 255));
  detailBrand->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT,
                               wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  detailBrand->Hide();

  detailYear = new wxStaticText(detailPanel, wxID_ANY, "",
      wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
  detailYear->SetForegroundColour(wxColour(156, 163, 175));
  detailYear->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT,
                              wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
  detailYear->Hide();

  detailColor = new wxStaticText(detailPanel, wxID_ANY, "",
      wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
  detailColor->SetForegroundColour(wxColour(156, 163, 175));
  detailColor->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT,
                               wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
  detailColor->Hide();

  reserveBtn = new wxButton(detailPanel, wxID_ANY, "Zarezerwuj auto");
  reserveBtn->SetBackgroundColour(wxColour(59, 130, 246));
  reserveBtn->SetForegroundColour(wxColour(255, 255, 255));
  reserveBtn->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT,
                              wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  reserveBtn->Hide();
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

    reserveInfo = new wxStaticText(detailPanel, wxID_ANY, "");
    reserveInfo->SetForegroundColour(wxColour(156, 163, 175));
    reserveInfo->SetFont(wxFont(9, wxFONTFAMILY_DEFAULT,
                                                            wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

  detailSizer->AddStretchSpacer(1);
  detailSizer->Add(m_detailPlaceholder, 0, wxALIGN_CENTER | wxALL, 16);
  detailSizer->Add(m_detailBrand, 0, wxLEFT | wxRIGHT | wxTOP, 20);
  detailSizer->Add(m_detailYear, 0, wxLEFT | wxRIGHT | wxTOP, 20);
  detailSizer->Add(m_detailColor, 0, wxLEFT | wxRIGHT | wxTOP, 20);
  detailSizer->AddStretchSpacer(1);
  detailSizer->Add(reserveBtn, 0, wxALIGN_CENTER | wxBOTTOM, 20);
    detailSizer->Add(reserveInfo, 0, wxALIGN_CENTER | wxBOTTOM, 10);
  detailPanel->SetSizer(detailSizer);

    reserveBtn->Bind(wxEVT_BUTTON, [this](wxCommandEvent &) {
        if (!this->database) {
            reserveInfo->SetLabel("Blad: Brak polaczenia z baza.");
            reserveInfo->SetForegroundColour(wxColour(248, 113, 113));
            detailPanel->Layout();
            return;
        }

        if (selectedVehicleId < 0) {
            reserveInfo->SetLabel("Wybierz auto z listy.");
            reserveInfo->SetForegroundColour(wxColour(248, 113, 113));
            detailPanel->Layout();
            return;
        }

        int userId = Session::getInstance().getUserId();
        if (userId < 0) {
            reserveInfo->SetLabel("Blad: Uzytkownik niezalogowany.");
            reserveInfo->SetForegroundColour(wxColour(248, 113, 113));
            detailPanel->Layout();
            return;
        }

        std::string existsSql =
                "SELECT COUNT(*) FROM rentalHistory WHERE idUser = " +
                std::to_string(userId) + " AND idVehicle = " +
                std::to_string(selectedVehicleId) + ";";

        auto mapCount = [](sqlite3_stmt *stmt) -> int {
            return sqlite3_column_int(stmt, 0);
        };

        std::vector<int> counts = this->database->fetch<int>(existsSql, mapCount);
        if (!counts.empty() && counts[0] > 0) {
            reserveInfo->SetLabel("To auto jest juz zarezerwowane.");
            reserveInfo->SetForegroundColour(wxColour(245, 158, 11));
            detailPanel->Layout();
            return;
        }

        std::string historySql =
                "INSERT OR IGNORE INTO rentalHistory (idUser, idVehicle, date) VALUES (" +
                std::to_string(userId) + ", " + std::to_string(selectedVehicleId) +
                ", date('now'));";
        this->database->executeQuery(historySql);

        std::string userVehicleSql =
                "INSERT OR IGNORE INTO userVehicle (idUser, idVehicle, date) VALUES (" +
                std::to_string(userId) + ", " + std::to_string(selectedVehicleId) +
                ", date('now'));";
        this->database->executeQuery(userVehicleSql);

        reserveInfo->SetLabel("Sukces: Auto zostalo zarezerwowane.");
        reserveInfo->SetForegroundColour(wxColour(52, 211, 153));
        detailPanel->Layout();
    });

  // ----------------------------------------------------------------
  // LEWY PANEL: przewijalna lista aut
  // ----------------------------------------------------------------
  wxPanel *listContainer = new wxPanel(this, wxID_ANY);
  listContainer->SetBackgroundColour(wxColour(31, 41, 55));
  wxBoxSizer *listContainerSizer = new wxBoxSizer(wxVERTICAL);
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

    scrollList = new wxScrolledWindow(
      listContainer, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL);
  scrollList->SetBackgroundColour(wxColour(31, 41, 55));
  scrollList->SetScrollRate(0, 10);
    scrollSizer = new wxBoxSizer(wxVERTICAL);

  scrollList->SetSizer(scrollSizer);

  listContainerSizer->Add(listTitle,  0, wxTOP | wxLEFT | wxRIGHT, 12);
  listContainerSizer->Add(scrollList, 1, wxEXPAND | wxALL, 8);
  listContainer->SetSizer(listContainerSizer);

  contentRow->Add(listContainer, 1, wxEXPAND | wxALL, 10);
  contentRow->Add(detailPanel,   2, wxEXPAND | wxALL, 10);

  SetSizer(contentRow);

    refreshVehicles();
    if (this->logger) {
        this->logger->log(LogLevel::Debug, "VehicleCarouselWidget: constructor end");
    }
}

void VehicleCarouselWidget::buildVehicleRows(
        const std::vector<VehicleSummary> &vehicles) {
    if (logger) {
        logger->log(LogLevel::Debug,
                                "VehicleCarouselWidget: buildVehicleRows count=" +
                                        std::to_string(vehicles.size()));
    }
    scrollSizer->Clear(true);

    detailPlaceholder->Show();
    detailBrand->Hide();
    detailYear->Hide();
    detailColor->Hide();
    reserveBtn->Hide();
    reserveInfo->SetLabel("");
    selectedVehicleId = -1;

    if (vehicles.empty()) {
        wxStaticText *emptyLabel =
                new wxStaticText(scrollList, wxID_ANY, "Brak aut w bazie");
        emptyLabel->SetForegroundColour(wxColour(156, 163, 175));
        scrollSizer->Add(emptyLabel, 0, wxALL, 12);
    }

    for (size_t i = 0; i < vehicles.size(); ++i) {
        VehicleSummary v = vehicles[i];

        wxPanel *row = new wxPanel(scrollList, wxID_ANY);
        row->SetBackgroundColour(wxColour(55, 65, 81));
        row->SetCursor(wxCURSOR_HAND);
        wxBoxSizer *rowSizer = new wxBoxSizer(wxVERTICAL);

        wxString titleText = toWx(v.brand) + " " + toWx(v.model);
        wxStaticText *rowTitle = new wxStaticText(row, wxID_ANY, titleText);
        rowTitle->SetForegroundColour(wxColour(255, 255, 255));
        rowTitle->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                                                         wxFONTWEIGHT_BOLD));

        wxString subtitleText = "Rok: " + toWx(v.year) +
                                " | Kolor: " + toWx(v.color);
        wxStaticText *rowSub = new wxStaticText(row, wxID_ANY, subtitleText);
        rowSub->SetForegroundColour(wxColour(156, 163, 175));
        rowSub->SetFont(wxFont(9, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                                                     wxFONTWEIGHT_NORMAL));

        rowSizer->Add(rowTitle, 0, wxLEFT | wxTOP | wxRIGHT, 10);
        rowSizer->Add(rowSub, 0, wxLEFT | wxBOTTOM | wxRIGHT, 10);
        row->SetSizer(rowSizer);

        auto showDetail =
                [v, this](wxMouseEvent &) {
                                        selectedVehicleId = v.id;
                    detailPlaceholder->Hide();
                      detailBrand->SetLabel(toWx(v.brand) + " " + toWx(v.model));
                      detailYear->SetLabel("Rok produkcji: " + toWx(v.year));
                      detailColor->SetLabel("Kolor: " + toWx(v.color));
                                        reserveInfo->SetLabel("");
                    detailBrand->Show();
                    detailYear->Show();
                    detailColor->Show();
                    reserveBtn->Show();
                    detailPanel->Layout();
                };

        row->Bind(wxEVT_LEFT_DOWN, showDetail);
        rowTitle->Bind(wxEVT_LEFT_DOWN, showDetail);
        rowSub->Bind(wxEVT_LEFT_DOWN, showDetail);

        scrollSizer->Add(row, 0, wxEXPAND | wxBOTTOM, 6);
    }

    scrollList->FitInside();
    scrollList->Layout();
    detailPanel->Layout();
    Layout();
    if (logger) {
        logger->log(LogLevel::Debug, "VehicleCarouselWidget: buildVehicleRows end");
    }
}

void VehicleCarouselWidget::refreshVehicles() {
    if (logger) {
        logger->log(LogLevel::Debug, "VehicleCarouselWidget: refreshVehicles start");
    }
    VehicleList vehicleList(database, logger);
    vehicleList.initList(
            "SELECT id, brand, model, year, color FROM vehicle ORDER BY id;");

    buildVehicleRows(vehicleList.getList());
    if (logger) {
        logger->log(LogLevel::Debug, "VehicleCarouselWidget: refreshVehicles end");
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
