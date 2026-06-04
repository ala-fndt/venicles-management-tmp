#include "../include/view/VehicleCarouselWidget.hpp"
#include "../include/classes/VehicleList.hpp"
#include "../include/additionalScripts/Logger.hpp"
#include "../include/database/Database.hpp"

VehicleCarouselWidget::VehicleCarouselWidget(
        wxWindow *parent, Database *database, Logger *logger)
    : wxPanel(parent) {

    VehicleList vehicleList(database, logger);
    vehicleList.initList(
            "SELECT brand, model, year, color FROM vehicle ORDER BY id;");
    const std::vector<VehicleSummary> vehicles = vehicleList.getList();

  SetBackgroundColour(wxColour(17, 24, 39));

  wxBoxSizer *contentRow = new wxBoxSizer(wxHORIZONTAL);

  // ----------------------------------------------------------------
  // PRAWY PANEL: szczegoly wybranego auta
  // ----------------------------------------------------------------
  wxPanel *detailPanel = new wxPanel(this, wxID_ANY);
  detailPanel->SetBackgroundColour(wxColour(31, 41, 55));
  wxBoxSizer *detailSizer = new wxBoxSizer(wxVERTICAL);

  wxStaticText *detailPlaceholder = new wxStaticText(
      detailPanel, wxID_ANY,
      "Wybierz auto z listy\naby zobaczyc szczegoly.",
      wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
  detailPlaceholder->SetForegroundColour(wxColour(107, 114, 128));
  detailPlaceholder->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT,
                                    wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

  // Etykiety szczegolow (ukryte dopoki nie wybrano auta)
  wxStaticText *detailBrand = new wxStaticText(detailPanel, wxID_ANY, "",
      wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
  detailBrand->SetForegroundColour(wxColour(255, 255, 255));
  detailBrand->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT,
                               wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  detailBrand->Hide();

  wxStaticText *detailYear = new wxStaticText(detailPanel, wxID_ANY, "",
      wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
  detailYear->SetForegroundColour(wxColour(156, 163, 175));
  detailYear->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT,
                              wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
  detailYear->Hide();

  wxStaticText *detailColor = new wxStaticText(detailPanel, wxID_ANY, "",
      wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
  detailColor->SetForegroundColour(wxColour(156, 163, 175));
  detailColor->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT,
                               wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
  detailColor->Hide();

  wxButton *reserveBtn = new wxButton(detailPanel, wxID_ANY, "Zarezerwuj auto");
  reserveBtn->SetBackgroundColour(wxColour(59, 130, 246));
  reserveBtn->SetForegroundColour(wxColour(255, 255, 255));
  reserveBtn->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT,
                              wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  reserveBtn->Hide();

  detailSizer->AddStretchSpacer(1);
  detailSizer->Add(detailPlaceholder, 0, wxALIGN_CENTER | wxALL, 16);
  detailSizer->Add(detailBrand,  0, wxLEFT | wxRIGHT | wxTOP, 20);
  detailSizer->Add(detailYear,   0, wxLEFT | wxRIGHT | wxTOP, 20);
  detailSizer->Add(detailColor,  0, wxLEFT | wxRIGHT | wxTOP, 20);
  detailSizer->AddStretchSpacer(1);
  detailSizer->Add(reserveBtn, 0, wxALIGN_CENTER | wxBOTTOM, 20);
  detailPanel->SetSizer(detailSizer);

  // ----------------------------------------------------------------
  // LEWY PANEL: przewijalna lista aut
  // ----------------------------------------------------------------
  wxPanel *listContainer = new wxPanel(this, wxID_ANY);
  listContainer->SetBackgroundColour(wxColour(31, 41, 55));
  wxBoxSizer *listContainerSizer = new wxBoxSizer(wxVERTICAL);

  wxStaticText *listTitle = new wxStaticText(listContainer, wxID_ANY, "Lista aut");
  listTitle->SetForegroundColour(wxColour(255, 255, 255));
  listTitle->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT,
                             wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

  wxScrolledWindow *scrollList = new wxScrolledWindow(
      listContainer, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL);
  scrollList->SetBackgroundColour(wxColour(31, 41, 55));
  scrollList->SetScrollRate(0, 10);
  wxBoxSizer *scrollSizer = new wxBoxSizer(wxVERTICAL);

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

    wxStaticText *rowTitle = new wxStaticText(
        row, wxID_ANY,
        wxString::Format("%s %s", v.brand, v.model));
    rowTitle->SetForegroundColour(wxColour(255, 255, 255));
    rowTitle->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT,
                              wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    wxStaticText *rowSub = new wxStaticText(
        row, wxID_ANY,
        wxString::Format("Rok: %s | Kolor: %s", v.year, v.color));
    rowSub->SetForegroundColour(wxColour(156, 163, 175));
    rowSub->SetFont(wxFont(9, wxFONTFAMILY_DEFAULT,
                            wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    rowSizer->Add(rowTitle, 0, wxLEFT | wxTOP | wxRIGHT, 10);
    rowSizer->Add(rowSub,   0, wxLEFT | wxBOTTOM | wxRIGHT, 10);
    row->SetSizer(rowSizer);

    // Klikniecie w wiersz -> pokaz szczegoly po prawej
    auto showDetail = [v, detailPlaceholder, detailBrand, detailYear,
                       detailColor, reserveBtn, detailPanel](wxMouseEvent &) {
      detailPlaceholder->Hide();
      detailBrand->SetLabel(wxString::Format("%s %s", v.brand, v.model));
      detailYear->SetLabel(wxString::Format("Rok produkcji: %s", v.year));
      detailColor->SetLabel(wxString::Format("Kolor: %s", v.color));
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

  scrollList->SetSizer(scrollSizer);
  scrollList->FitInside();

  listContainerSizer->Add(listTitle,  0, wxTOP | wxLEFT | wxRIGHT, 12);
  listContainerSizer->Add(scrollList, 1, wxEXPAND | wxALL, 8);
  listContainer->SetSizer(listContainerSizer);

  contentRow->Add(listContainer, 1, wxEXPAND | wxALL, 10);
  contentRow->Add(detailPanel,   2, wxEXPAND | wxALL, 10);

  SetSizer(contentRow);
}
