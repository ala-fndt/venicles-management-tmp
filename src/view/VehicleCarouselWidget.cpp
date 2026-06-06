#include "../include/view/VehicleCarouselWidget.hpp"
#include "../include/classes/Session.hpp"
#include "../include/classes/VehicleList.hpp"
#include "../include/additionalScripts/Logger.hpp"
#include "../include/database/Database.hpp"

namespace {
wxString toWx(const std::string &text) {
    return wxString::From8BitData(text.c_str());
}

std::string trim(const std::string &text) {
    const std::string whitespace = " \t\n\r";
    const std::size_t begin = text.find_first_not_of(whitespace);
    if (begin == std::string::npos) {
        return "";
    }
    const std::size_t end = text.find_last_not_of(whitespace);
    return text.substr(begin, end - begin + 1);
}
} // namespace

VehicleCarouselWidget::VehicleCarouselWidget(
        wxWindow *parent, Database *database, Logger *logger)
        : wxPanel(parent), database(database), logger(logger),
            detailReservationStatus(nullptr), reserveInfo(nullptr),
            reserveBtn(nullptr), returnBtn(nullptr), takeBtn(nullptr), selectedVehicleId(-1),
            reservedPanel(nullptr), reservedScrollList(nullptr), reservedListSizer(nullptr) {
    if (this->logger) {
        this->logger->log(LogLevel::Debug, "VehicleCarouselWidget: constructor start");
    }

  SetBackgroundColour(wxColour(17, 24, 39));

  wxBoxSizer *contentRow = new wxBoxSizer(wxHORIZONTAL);
    wxPanel *mainContentPanel = new wxPanel(this, wxID_ANY);
    mainContentPanel->SetBackgroundColour(wxColour(17, 24, 39));
    wxBoxSizer *mainContentSizer = new wxBoxSizer(wxHORIZONTAL);

  // ----------------------------------------------------------------
  // PRAWY PANEL: szczegoly wybranego auta
  // ----------------------------------------------------------------
    detailPanel = new wxPanel(mainContentPanel, wxID_ANY);
  detailPanel->SetBackgroundColour(wxColour(31, 41, 55));
  wxBoxSizer *detailSizer = new wxBoxSizer(wxVERTICAL);

  detailPlaceholder = new wxStaticText(
      detailPanel, wxID_ANY,
      "Select a vehicle from the list\nto see details.",
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

    detailReservationStatus = new wxStaticText(detailPanel, wxID_ANY, "");
    detailReservationStatus->SetForegroundColour(wxColour(156, 163, 175));
    detailReservationStatus->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT,
                                                                                    wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    detailReservationStatus->Hide();

    reserveBtn = new wxButton(detailPanel, wxID_ANY, "Reserve vehicle");
  reserveBtn->SetBackgroundColour(wxColour(59, 130, 246));
  reserveBtn->SetForegroundColour(wxColour(255, 255, 255));
  reserveBtn->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT,
                              wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  reserveBtn->Hide();

    returnBtn = new wxButton(detailPanel, wxID_ANY, "Return vehicle");
    returnBtn->SetBackgroundColour(wxColour(34, 197, 94));
    returnBtn->SetForegroundColour(wxColour(255, 255, 255));
    returnBtn->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT,
                                                         wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    returnBtn->Hide();

    takeBtn = new wxButton(detailPanel, wxID_ANY, "Take vehicle");
    takeBtn->SetBackgroundColour(wxColour(239, 68, 68));
    takeBtn->SetForegroundColour(wxColour(255, 255, 255));
    takeBtn->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT,
                                                     wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    takeBtn->Hide();

    reserveInfo = new wxStaticText(detailPanel, wxID_ANY, "");
    reserveInfo->SetForegroundColour(wxColour(156, 163, 175));
    reserveInfo->SetFont(wxFont(9, wxFONTFAMILY_DEFAULT,
                                                            wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

  detailSizer->AddStretchSpacer(1);
  detailSizer->Add(detailPlaceholder, 0, wxALIGN_CENTER | wxALL, 16);
  detailSizer->Add(detailBrand,  0, wxLEFT | wxRIGHT | wxTOP, 20);
  detailSizer->Add(detailYear,   0, wxLEFT | wxRIGHT | wxTOP, 20);
  detailSizer->Add(detailColor,  0, wxLEFT | wxRIGHT | wxTOP, 20);
    detailSizer->Add(detailReservationStatus, 0, wxLEFT | wxRIGHT | wxTOP, 20);
  detailSizer->AddStretchSpacer(1);
  detailSizer->Add(reserveBtn, 0, wxALIGN_CENTER | wxBOTTOM, 20);
    detailSizer->Add(returnBtn, 0, wxALIGN_CENTER | wxBOTTOM, 20);
    detailSizer->Add(takeBtn, 0, wxALIGN_CENTER | wxBOTTOM, 20);
    detailSizer->Add(reserveInfo, 0, wxALIGN_CENTER | wxBOTTOM, 10);
  detailPanel->SetSizer(detailSizer);

    reserveBtn->Bind(wxEVT_BUTTON, [this](wxCommandEvent &) {
        if (!this->database) {
            reserveInfo->SetLabel("Error: No database connection.");
            reserveInfo->SetForegroundColour(wxColour(248, 113, 113));
            detailPanel->Layout();
            return;
        }

        if (selectedVehicleId < 0) {
            reserveInfo->SetLabel("Select a vehicle from the list.");
            reserveInfo->SetForegroundColour(wxColour(248, 113, 113));
            detailPanel->Layout();
            return;
        }

        int userId = Session::getInstance().getUserId();
        if (userId < 0) {
            reserveInfo->SetLabel("Error: User not logged in.");
            reserveInfo->SetForegroundColour(wxColour(248, 113, 113));
            detailPanel->Layout();
            return;
        }

        if (isVehicleReservedByAnotherUser(selectedVehicleId, userId)) {
            reserveInfo->SetLabel("This vehicle is already reserved.");
            reserveInfo->SetForegroundColour(wxColour(245, 158, 11));
            detailPanel->Layout();
            return;
        }

        ActiveReservationInfo currentReservation = getReservationInfo(selectedVehicleId);
        if (currentReservation.isReserved && currentReservation.userId == userId) {
            reserveInfo->SetLabel("This vehicle is already assigned to you.");
            reserveInfo->SetForegroundColour(wxColour(245, 158, 11));
            detailPanel->Layout();
            return;
        }

        std::size_t errorsBeforeInsert = this->database->errors.size();
        std::string reserveSql =
                "INSERT INTO activeReservation (idUser, idVehicle, date) VALUES (" +
                std::to_string(userId) + ", " + std::to_string(selectedVehicleId) +
                ", date('now'));";
        this->database->executeQuery(reserveSql);

        if (this->database->errors.size() > errorsBeforeInsert) {
            reserveInfo->SetLabel("Error: Reservation failed. Vehicle may already be occupied.");
            reserveInfo->SetForegroundColour(wxColour(248, 113, 113));
            detailPanel->Layout();
            return;
        }

        std::string historySql =
                "INSERT OR IGNORE INTO rentalHistory (idUser, idVehicle, date) VALUES (" +
                std::to_string(userId) + ", " + std::to_string(selectedVehicleId) +
                ", date('now'));";
        this->database->executeQuery(historySql);

        reserveInfo->SetLabel("Success: Vehicle reserved.");
        reserveInfo->SetForegroundColour(wxColour(52, 211, 153));
        refreshVehicles();
        Layout();
        Refresh();
        Update();
    });

    returnBtn->Bind(wxEVT_BUTTON, [this](wxCommandEvent &) {
        if (!this->database) {
            reserveInfo->SetLabel("Error: No database connection.");
            reserveInfo->SetForegroundColour(wxColour(248, 113, 113));
            detailPanel->Layout();
            return;
        }

        if (selectedVehicleId < 0) {
            reserveInfo->SetLabel("Select a vehicle from the list.");
            reserveInfo->SetForegroundColour(wxColour(248, 113, 113));
            detailPanel->Layout();
            return;
        }

        int userId = Session::getInstance().getUserId();
        if (userId < 0) {
            reserveInfo->SetLabel("Error: User not logged in.");
            reserveInfo->SetForegroundColour(wxColour(248, 113, 113));
            detailPanel->Layout();
            return;
        }

        ActiveReservationInfo reservation = getReservationInfo(selectedVehicleId);
        if (!reservation.isReserved || reservation.userId != userId) {
            reserveInfo->SetLabel("Error: You can return only your own reserved vehicle.");
            reserveInfo->SetForegroundColour(wxColour(248, 113, 113));
            detailPanel->Layout();
            return;
        }

        std::size_t errorsBeforeDelete = this->database->errors.size();
        std::string returnSql =
                "DELETE FROM activeReservation WHERE idVehicle = " +
                std::to_string(selectedVehicleId) + " AND idUser = " +
                std::to_string(userId) + ";";
        this->database->executeQuery(returnSql);

        if (this->database->errors.size() > errorsBeforeDelete) {
            reserveInfo->SetLabel("Error: Failed to return vehicle.");
            reserveInfo->SetForegroundColour(wxColour(248, 113, 113));
            detailPanel->Layout();
            return;
        }

        reserveInfo->SetLabel("Success: Vehicle returned.");
        reserveInfo->SetForegroundColour(wxColour(52, 211, 153));
        refreshVehicles();
        Layout();
        Refresh();
        Update();
    });

    takeBtn->Bind(wxEVT_BUTTON, [this](wxCommandEvent &) {
        if (!this->database) {
            reserveInfo->SetLabel("Error: No database connection.");
            reserveInfo->SetForegroundColour(wxColour(248, 113, 113));
            detailPanel->Layout();
            return;
        }

        if (!Session::getInstance().getAdmin()) {
            reserveInfo->SetLabel("Error: Administrator permissions required.");
            reserveInfo->SetForegroundColour(wxColour(248, 113, 113));
            detailPanel->Layout();
            return;
        }

        if (selectedVehicleId < 0) {
            reserveInfo->SetLabel("Select a vehicle from the list.");
            reserveInfo->SetForegroundColour(wxColour(248, 113, 113));
            detailPanel->Layout();
            return;
        }

        ActiveReservationInfo reservation = getReservationInfo(selectedVehicleId);
        if (!reservation.isReserved) {
            reserveInfo->SetLabel("Vehicle is already available.");
            reserveInfo->SetForegroundColour(wxColour(245, 158, 11));
            detailPanel->Layout();
            return;
        }

        std::size_t errorsBeforeDelete = this->database->errors.size();
        std::string takeSql =
                "DELETE FROM activeReservation WHERE idVehicle = " +
                std::to_string(selectedVehicleId) + ";";
        this->database->executeQuery(takeSql);

        if (this->database->errors.size() > errorsBeforeDelete) {
            reserveInfo->SetLabel("Error: Failed to remove current assignment.");
            reserveInfo->SetForegroundColour(wxColour(248, 113, 113));
            detailPanel->Layout();
            return;
        }

        reserveInfo->SetLabel("Success: Vehicle taken from current user.");
        reserveInfo->SetForegroundColour(wxColour(52, 211, 153));
        refreshVehicles();
        Layout();
        Refresh();
        Update();
    });

  // ----------------------------------------------------------------
  // LEWY PANEL: przewijalna lista aut
  // ----------------------------------------------------------------
    wxPanel *listContainer = new wxPanel(mainContentPanel, wxID_ANY);
  listContainer->SetBackgroundColour(wxColour(31, 41, 55));
  wxBoxSizer *listContainerSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText *listTitle = new wxStaticText(listContainer, wxID_ANY, "Vehicle list");
  listTitle->SetForegroundColour(wxColour(255, 255, 255));
  listTitle->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT,
                             wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    scrollList = new wxScrolledWindow(
      listContainer, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL);
  scrollList->SetBackgroundColour(wxColour(31, 41, 55));
  scrollList->SetScrollRate(0, 10);
    scrollSizer = new wxBoxSizer(wxVERTICAL);

  scrollList->SetSizer(scrollSizer);

  listContainerSizer->Add(listTitle,  0, wxTOP | wxLEFT | wxRIGHT, 12);
  listContainerSizer->Add(scrollList, 1, wxEXPAND | wxALL, 8);
  listContainer->SetSizer(listContainerSizer);

    mainContentSizer->Add(listContainer, 1, wxEXPAND | wxALL, 10);
    mainContentSizer->Add(detailPanel,   2, wxEXPAND | wxALL, 10);
    mainContentPanel->SetSizer(mainContentSizer);

    reservedPanel = new wxPanel(this, wxID_ANY);
    reservedPanel->SetBackgroundColour(wxColour(31, 41, 55));
    wxBoxSizer *reservedSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText *reservedTitle = new wxStaticText(reservedPanel, wxID_ANY, "Reserved vehicles");
    reservedTitle->SetForegroundColour(wxColour(255, 255, 255));
    reservedTitle->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT,
                                                                 wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    reservedScrollList = new wxScrolledWindow(
            reservedPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL);
    reservedScrollList->SetBackgroundColour(wxColour(31, 41, 55));
    reservedScrollList->SetScrollRate(0, 10);
    reservedListSizer = new wxBoxSizer(wxVERTICAL);
    reservedScrollList->SetSizer(reservedListSizer);

    reservedSizer->Add(reservedTitle, 0, wxTOP | wxLEFT | wxRIGHT, 12);
    reservedSizer->Add(reservedScrollList, 1, wxEXPAND | wxALL, 8);
    reservedPanel->SetSizer(reservedSizer);

    contentRow->Add(mainContentPanel, 3, wxEXPAND | wxALL, 0);
    contentRow->Add(reservedPanel, 1, wxEXPAND | wxALL, 10);

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
    detailReservationStatus->Hide();
    reserveBtn->Hide();
    returnBtn->Hide();
    takeBtn->Hide();
    reserveInfo->SetLabel("");
    selectedVehicleId = -1;

    if (vehicles.empty()) {
        wxStaticText *emptyLabel =
                new wxStaticText(scrollList, wxID_ANY, "No vehicles in the database");
        emptyLabel->SetForegroundColour(wxColour(156, 163, 175));
        scrollSizer->Add(emptyLabel, 0, wxALL, 12);
    }

    for (size_t i = 0; i < vehicles.size(); ++i) {
        VehicleSummary v = vehicles[i];
        const bool isReserved = getReservationInfo(v.id).isReserved;

        wxPanel *row = new wxPanel(scrollList, wxID_ANY);
        row->SetBackgroundColour(isReserved ? wxColour(110, 125, 155)
                                            : wxColour(55, 65, 81));
        row->SetCursor(wxCURSOR_HAND);
        wxBoxSizer *rowSizer = new wxBoxSizer(wxVERTICAL);

        wxString titleText = toWx(v.brand) + " " + toWx(v.model);
        wxStaticText *rowTitle = new wxStaticText(row, wxID_ANY, titleText);
        rowTitle->SetForegroundColour(wxColour(255, 255, 255));
        rowTitle->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                                                         wxFONTWEIGHT_BOLD));

        wxString subtitleText = "Year: " + toWx(v.year) +
                    " | Color: " + toWx(v.color);
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
                                        populateDetailPanel(v);
                                        refreshActionButtons();
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
    refreshReservedList();
    if (logger) {
        logger->log(LogLevel::Debug, "VehicleCarouselWidget: refreshVehicles end");
    }
}

void VehicleCarouselWidget::refreshReservedList() {
    if (!database || !reservedPanel || !reservedScrollList || !reservedListSizer) {
        return;
    }

    const bool isAdmin = Session::getInstance().getAdmin();
    const int currentUserId = Session::getInstance().getUserId();
    if (!isAdmin && currentUserId < 0) {
        reservedListSizer->Clear(true);
        wxStaticText *emptyLabel =
            new wxStaticText(reservedScrollList, wxID_ANY, "No reserved vehicles");
        emptyLabel->SetForegroundColour(wxColour(156, 163, 175));
        reservedListSizer->Add(emptyLabel, 0, wxALL, 12);
        reservedScrollList->FitInside();
        reservedScrollList->Layout();
        reservedPanel->Layout();
        return;
    }

    reservedListSizer->Clear(true);

    auto mapper = [](sqlite3_stmt *stmt) -> VehicleSummary {
        VehicleSummary v;
        v.id = sqlite3_column_int(stmt, 0);
        v.brand = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        v.model = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        v.year = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
        v.color = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
        return v;
    };

    std::string sql = "SELECT v.id, v.brand, v.model, v.year, v.color "
                      "FROM activeReservation ar "
                      "JOIN vehicle v ON v.id = ar.idVehicle ";

    if (!isAdmin) {
        sql += "WHERE ar.idUser = " + std::to_string(currentUserId) + " ";
    }

    sql += "ORDER BY ar.date DESC;";

    std::vector<VehicleSummary> reservedVehicles =
        database->fetch<VehicleSummary>(sql, mapper);

    if (reservedVehicles.empty()) {
        wxStaticText *emptyLabel =
            new wxStaticText(reservedScrollList, wxID_ANY, "No reserved vehicles");
        emptyLabel->SetForegroundColour(wxColour(156, 163, 175));
        reservedListSizer->Add(emptyLabel, 0, wxALL, 12);
    } else {
        for (const auto &v : reservedVehicles) {
            wxPanel *row = new wxPanel(reservedScrollList, wxID_ANY);
            row->SetBackgroundColour(wxColour(90, 100, 122));
            wxBoxSizer *rowSizer = new wxBoxSizer(wxVERTICAL);

            wxString titleText = toWx(v.brand) + " " + toWx(v.model);
            wxStaticText *rowTitle = new wxStaticText(row, wxID_ANY, titleText);
            rowTitle->SetForegroundColour(wxColour(255, 255, 255));
            rowTitle->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                                     wxFONTWEIGHT_BOLD));

            wxString subtitleText = "Year: " + toWx(v.year) +
                                    " | Color: " + toWx(v.color);
            wxStaticText *rowSub = new wxStaticText(row, wxID_ANY, subtitleText);
            rowSub->SetForegroundColour(wxColour(156, 163, 175));
            rowSub->SetFont(wxFont(9, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                                   wxFONTWEIGHT_NORMAL));

            rowSizer->Add(rowTitle, 0, wxLEFT | wxTOP | wxRIGHT, 10);
            rowSizer->Add(rowSub, 0, wxLEFT | wxBOTTOM | wxRIGHT, 10);
            row->SetSizer(rowSizer);

            reservedListSizer->Add(row, 0, wxEXPAND | wxBOTTOM, 6);
        }
    }

    reservedScrollList->FitInside();
    reservedScrollList->Layout();
    reservedPanel->Layout();
}

VehicleCarouselWidget::ActiveReservationInfo VehicleCarouselWidget::getReservationInfo(int vehicleId) const {
    ActiveReservationInfo reservation;
    if (!database || vehicleId < 0) {
        return reservation;
    }

    std::string sql =
            "SELECT ar.idUser, COALESCE(u.name, ''), COALESCE(u.surname, '') "
            "FROM activeReservation ar "
            "LEFT JOIN users u ON u.id = ar.idUser "
            "WHERE ar.idVehicle = " + std::to_string(vehicleId) + " LIMIT 1;";

    auto mapper = [](sqlite3_stmt *stmt) -> ActiveReservationInfo {
        ActiveReservationInfo info;
        info.isReserved = true;
        info.userId = sqlite3_column_int(stmt, 0);

        const unsigned char *nameRaw = sqlite3_column_text(stmt, 1);
        const unsigned char *surnameRaw = sqlite3_column_text(stmt, 2);
        std::string name = nameRaw ? reinterpret_cast<const char *>(nameRaw) : "";
        std::string surname = surnameRaw ? reinterpret_cast<const char *>(surnameRaw) : "";
        info.userFullName = trim(name + " " + surname);
        return info;
    };

    std::vector<ActiveReservationInfo> rows = database->fetch<ActiveReservationInfo>(sql, mapper);
    if (!rows.empty()) {
        return rows[0];
    }
    return reservation;
}

bool VehicleCarouselWidget::isVehicleReservedByAnotherUser(int vehicleId, int userId) const {
    ActiveReservationInfo reservation = getReservationInfo(vehicleId);
    return reservation.isReserved && reservation.userId != userId;
}

void VehicleCarouselWidget::populateDetailPanel(const VehicleSummary &vehicle) {
    selectedVehicleId = vehicle.id;
    detailPlaceholder->Hide();
    reserveInfo->SetLabel("");
    detailBrand->SetLabel(toWx(vehicle.brand) + " " + toWx(vehicle.model));
    detailYear->SetLabel("Production year: " + toWx(vehicle.year));
    detailColor->SetLabel("Color: " + toWx(vehicle.color));

    detailBrand->Show();
    detailYear->Show();
    detailColor->Show();
    detailReservationStatus->Show();
}

void VehicleCarouselWidget::refreshActionButtons() {
    if (selectedVehicleId < 0) {
        return;
    }

    const bool isAdmin = Session::getInstance().getAdmin();
    const int currentUserId = Session::getInstance().getUserId();
    ActiveReservationInfo reservation = getReservationInfo(selectedVehicleId);

    reserveBtn->Hide();
    returnBtn->Hide();
    takeBtn->Hide();

    if (!reservation.isReserved) {
        detailReservationStatus->SetLabel("Status: Available");
        detailReservationStatus->SetForegroundColour(wxColour(52, 211, 153));
        if (currentUserId >= 0) {
            reserveBtn->Show();
        }
    } else {
        std::string holder = reservation.userFullName.empty()
                                     ? ("User ID " + std::to_string(reservation.userId))
                                     : reservation.userFullName;
        detailReservationStatus->SetLabel(wxString("Status: Reserved by ") + toWx(holder));
        detailReservationStatus->SetForegroundColour(wxColour(245, 158, 11));

        if (isAdmin) {
            takeBtn->Show();
        } else if (currentUserId == reservation.userId) {
            returnBtn->Show();
        }
    }

    detailReservationStatus->Show();
}
