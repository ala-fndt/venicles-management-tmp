#include "../../include/view/UserPageView.hpp"
#include "../include/classes/Session.hpp"
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/valtext.h>

// Konstruktor nie przyjmuje już wskaźnika do modelu, aby zachować czyste MVC
UserPageView::UserPageView(wxWindow *window, Validator *validator, UserPageModel *model)
    : wxPanel(window),
      _validator(validator),
      _model(model)
{
    SetBackgroundColour(wxColour(17, 24, 39));
    SetForegroundColour(wxColour(229, 231, 235));

    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

    wxScrolledWindow *scrolledWindow = new wxScrolledWindow(this, wxID_ANY);
    scrolledWindow->SetScrollRate(0, 10);
    scrolledWindow->SetBackgroundColour(wxColour(17, 24, 39));

    wxBoxSizer *contentSizer = new wxBoxSizer(wxVERTICAL);

    backButton = new wxButton(scrolledWindow, wxID_ANY, "Powrot", wxDefaultPosition, wxSize(-1, 38));
    backButton->SetBackgroundColour(wxColour(55, 65, 81));
    backButton->SetForegroundColour(wxColour(255, 255, 255));
    backButton->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    wxBoxSizer *headerSizer = new wxBoxSizer(wxVERTICAL);

    labelTitle = new wxStaticText(scrolledWindow, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    labelTitle->SetFont(wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    labelTitle->SetForegroundColour(wxColour(255, 255, 255));

    headerSizer->Add(labelTitle, 0, wxALIGN_CENTER | wxBOTTOM, 4);

    wxStaticText *subTitle = new wxStaticText(scrolledWindow, wxID_ANY, "Panel uzytkownika", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    subTitle->SetForegroundColour(wxColour(107, 114, 128));
    subTitle->SetFont(wxFont(9, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    headerSizer->Add(subTitle, 0, wxALIGN_CENTER | wxBOTTOM, 24);

    contentSizer->Add(backButton, 0, wxALIGN_LEFT | wxLEFT | wxTOP, 10);
    contentSizer->Add(headerSizer, 0, wxEXPAND | wxTOP, 30);

    wxPanel *mainPanel = new wxPanel(scrolledWindow, wxID_ANY);
    mainPanel->SetBackgroundColour(wxColour(31, 41, 55));

    wxBoxSizer *panelSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText *panelTitle = new wxStaticText(mainPanel, wxID_ANY, "Panel", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    panelTitle->SetForegroundColour(wxColour(255, 255, 255));
    panelTitle->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    panelSizer->Add(panelTitle, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 20);

    wxStaticText *panelText = new wxStaticText(mainPanel, wxID_ANY, "Witaj w panelu uzytkownika", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    panelText->SetForegroundColour(wxColour(156, 163, 175));
    panelText->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    panelSizer->Add(panelText, 0, wxALIGN_CENTER | wxBOTTOM, 25);
    mainPanel->SetSizer(panelSizer);

    contentSizer->Add(mainPanel, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 40);

    historyPanel = new wxPanel(scrolledWindow, wxID_ANY);
    historyPanel->SetBackgroundColour(wxColour(31, 41, 55));
    wxBoxSizer *historySizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText *historyTitle = new wxStaticText(historyPanel, wxID_ANY, "Historia Wynajmu", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    historyTitle->SetForegroundColour(wxColour(255, 255, 255));
    historyTitle->SetFont(wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    historySizer->Add(historyTitle, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 20);

    historyListSizer = new wxBoxSizer(wxVERTICAL);
    historySizer->Add(historyListSizer, 1, wxEXPAND | wxLEFT | wxRIGHT, 20);
    historyPanel->SetSizer(historySizer);

    contentSizer->Add(historyPanel, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 40);

    adminPanel = new wxPanel(scrolledWindow, wxID_ANY);
    adminPanel->SetBackgroundColour(wxColour(31, 41, 55));

    wxBoxSizer *adminSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText *adminTitle = new wxStaticText(adminPanel, wxID_ANY, "Panel Administratora", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    adminTitle->SetForegroundColour(wxColour(255, 255, 255));
    adminTitle->SetFont(wxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    adminSizer->Add(adminTitle, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 6);

    wxStaticText *adminSubTitle = new wxStaticText(adminPanel, wxID_ANY, "Dodaj nowe auto do systemu", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    adminSubTitle->SetForegroundColour(wxColour(107, 114, 128));
    adminSubTitle->SetFont(wxFont(9, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    adminSizer->Add(adminSubTitle, 0, wxALIGN_CENTER | wxBOTTOM, 24);

    wxFlexGridSizer *formSizer = new wxFlexGridSizer(2, 12, 12);
    formSizer->AddGrowableCol(1, 1);

    wxStaticText *vinLabel = new wxStaticText(adminPanel, wxID_ANY, "VIN:");
    vinLabel->SetForegroundColour(wxColour(156, 163, 175));
    vinLabel->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    vinInput = new wxTextCtrl(adminPanel, wxID_ANY);
    vinInput->SetBackgroundColour(wxColour(17, 24, 39));
    vinInput->SetForegroundColour(wxColour(243, 244, 246));

    wxStaticText *brandLabel = new wxStaticText(adminPanel, wxID_ANY, "Marka:");
    brandLabel->SetForegroundColour(wxColour(156, 163, 175));
    brandLabel->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    brandInput = new wxTextCtrl(adminPanel, wxID_ANY);
    brandInput->SetValidator(wxTextValidator(wxFILTER_ALPHA));
    brandInput->SetBackgroundColour(wxColour(17, 24, 39));
    brandInput->SetForegroundColour(wxColour(243, 244, 246));

    wxStaticText *modelLabel = new wxStaticText(adminPanel, wxID_ANY, "Model:");
    modelLabel->SetForegroundColour(wxColour(156, 163, 175));
    modelLabel->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    modelInput = new wxTextCtrl(adminPanel, wxID_ANY);
    modelInput->SetBackgroundColour(wxColour(17, 24, 39));
    modelInput->SetForegroundColour(wxColour(243, 244, 246));

    wxStaticText *yearLabel = new wxStaticText(adminPanel, wxID_ANY, "Rok:");
    yearLabel->SetForegroundColour(wxColour(156, 163, 175));
    yearLabel->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    yearInput = new wxTextCtrl(adminPanel, wxID_ANY);
    yearInput->SetValidator(wxTextValidator(wxFILTER_DIGITS));
    yearInput->SetBackgroundColour(wxColour(17, 24, 39));
    yearInput->SetForegroundColour(wxColour(243, 244, 246));

    wxStaticText *colorLabel = new wxStaticText(adminPanel, wxID_ANY, "Kolor:");
    colorLabel->SetForegroundColour(wxColour(156, 163, 175));
    colorLabel->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    colorInput = new wxTextCtrl(adminPanel, wxID_ANY);
    colorInput->SetBackgroundColour(wxColour(17, 24, 39));
    colorInput->SetForegroundColour(wxColour(243, 244, 246));

    wxStaticText *fuelLabel = new wxStaticText(adminPanel, wxID_ANY, "Paliwo:");
    fuelLabel->SetForegroundColour(wxColour(156, 163, 175));
    fuelLabel->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    fuelTypeInput = new wxTextCtrl(adminPanel, wxID_ANY);
    fuelTypeInput->SetBackgroundColour(wxColour(17, 24, 39));
    fuelTypeInput->SetForegroundColour(wxColour(243, 244, 246));

    wxStaticText *statusLabel = new wxStaticText(adminPanel, wxID_ANY, "Stan:");
    statusLabel->SetForegroundColour(wxColour(156, 163, 175));
    statusLabel->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    technicalStatusInput = new wxTextCtrl(adminPanel, wxID_ANY);
    technicalStatusInput->SetBackgroundColour(wxColour(17, 24, 39));
    technicalStatusInput->SetForegroundColour(wxColour(243, 244, 246));

    wxStaticText *mileageLabel = new wxStaticText(adminPanel, wxID_ANY, "Przebieg:");
    mileageLabel->SetForegroundColour(wxColour(156, 163, 175));
    mileageLabel->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    mileageInput = new wxTextCtrl(adminPanel, wxID_ANY);
    mileageInput->SetValidator(wxTextValidator(wxFILTER_DIGITS));
    mileageInput->SetBackgroundColour(wxColour(17, 24, 39));
    mileageInput->SetForegroundColour(wxColour(243, 244, 246));

    wxStaticText *seatsLabel = new wxStaticText(adminPanel, wxID_ANY, "Miejsca:");
    seatsLabel->SetForegroundColour(wxColour(156, 163, 175));
    seatsLabel->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    numberOfSeatsInput = new wxTextCtrl(adminPanel, wxID_ANY);
    numberOfSeatsInput->SetValidator(wxTextValidator(wxFILTER_DIGITS));
    numberOfSeatsInput->SetBackgroundColour(wxColour(17, 24, 39));
    numberOfSeatsInput->SetForegroundColour(wxColour(243, 244, 246));

    wxStaticText *engineLabel = new wxStaticText(adminPanel, wxID_ANY, "Pojemnosc:");
    engineLabel->SetForegroundColour(wxColour(156, 163, 175));
    engineLabel->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    engineCapacityInput = new wxTextCtrl(adminPanel, wxID_ANY);
    engineCapacityInput->SetValidator(wxTextValidator(wxFILTER_DIGITS));
    engineCapacityInput->SetBackgroundColour(wxColour(17, 24, 39));
    engineCapacityInput->SetForegroundColour(wxColour(243, 244, 246));

    wxStaticText *handleLabel = new wxStaticText(adminPanel, wxID_ANY, "Kierownica:");
    handleLabel->SetForegroundColour(wxColour(156, 163, 175));
    handleLabel->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    handleBarsTypeInput = new wxTextCtrl(adminPanel, wxID_ANY);
    handleBarsTypeInput->SetBackgroundColour(wxColour(17, 24, 39));
    handleBarsTypeInput->SetForegroundColour(wxColour(243, 244, 246));

    wxStaticText *cargoLabel = new wxStaticText(adminPanel, wxID_ANY, "Ladunek:");
    cargoLabel->SetForegroundColour(wxColour(156, 163, 175));
    cargoLabel->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    maxCargoWeightInput = new wxTextCtrl(adminPanel, wxID_ANY);
    maxCargoWeightInput->SetValidator(wxTextValidator(wxFILTER_DIGITS));
    maxCargoWeightInput->SetBackgroundColour(wxColour(17, 24, 39));
    maxCargoWeightInput->SetForegroundColour(wxColour(243, 244, 246));

    wxStaticText *axlesLabel = new wxStaticText(adminPanel, wxID_ANY, "Osie:");
    axlesLabel->SetForegroundColour(wxColour(156, 163, 175));
    axlesLabel->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    numberOfAxlesInput = new wxTextCtrl(adminPanel, wxID_ANY);
    numberOfAxlesInput->SetValidator(wxTextValidator(wxFILTER_DIGITS));
    numberOfAxlesInput->SetBackgroundColour(wxColour(17, 24, 39));
    numberOfAxlesInput->SetForegroundColour(wxColour(243, 244, 246));

    formSizer->Add(vinLabel, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
    formSizer->Add(vinInput, 1, wxEXPAND);
    formSizer->Add(brandLabel, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
    formSizer->Add(brandInput, 1, wxEXPAND);
    formSizer->Add(modelLabel, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
    formSizer->Add(modelInput, 1, wxEXPAND);
    formSizer->Add(yearLabel, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
    formSizer->Add(yearInput, 1, wxEXPAND);
    formSizer->Add(colorLabel, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
    formSizer->Add(colorInput, 1, wxEXPAND);
    formSizer->Add(fuelLabel, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
    formSizer->Add(fuelTypeInput, 1, wxEXPAND);
    formSizer->Add(statusLabel, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
    formSizer->Add(technicalStatusInput, 1, wxEXPAND);
    formSizer->Add(mileageLabel, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
    formSizer->Add(mileageInput, 1, wxEXPAND);
    formSizer->Add(seatsLabel, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
    formSizer->Add(numberOfSeatsInput, 1, wxEXPAND);
    formSizer->Add(engineLabel, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
    formSizer->Add(engineCapacityInput, 1, wxEXPAND);
    formSizer->Add(handleLabel, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
    formSizer->Add(handleBarsTypeInput, 1, wxEXPAND);
    formSizer->Add(cargoLabel, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
    formSizer->Add(maxCargoWeightInput, 1, wxEXPAND);
    formSizer->Add(axlesLabel, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
    formSizer->Add(numberOfAxlesInput, 1, wxEXPAND);

    adminSizer->Add(formSizer, 1, wxEXPAND | wxLEFT | wxRIGHT, 30);
    adminSizer->AddSpacer(28);

    info = new wxStaticText(adminPanel, wxID_ANY, "");
    info->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    adminSizer->Add(info, 0, wxALIGN_CENTER | wxBOTTOM, 10);

    wxBoxSizer *btnSizer = new wxBoxSizer(wxHORIZONTAL);
    addVehicleButton = new wxButton(adminPanel, wxID_ANY, "Dodaj auto", wxDefaultPosition, wxSize(-1, 38));
    addVehicleButton->SetBackgroundColour(wxColour(99, 102, 241));
    addVehicleButton->SetForegroundColour(wxColour(255, 255, 255));
    addVehicleButton->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    btnSizer->Add(addVehicleButton, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
    adminSizer->Add(btnSizer, 0, wxALIGN_CENTER | wxBOTTOM, 25);

    adminPanel->SetSizer(adminSizer);
    contentSizer->Add(adminPanel, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 40);

    // Domyślnie panel administratora pozostaje ukryty do momentu wywołania updateUserData
    adminPanel->Hide();

    scrolledWindow->SetSizer(contentSizer);
    contentSizer->FitInside(scrolledWindow);
    mainSizer->Add(scrolledWindow, 1, wxEXPAND);

    SetSizer(mainSizer);
}

void UserPageView::refresh()
{
    auto &session = Session::getInstance();

    info->SetLabel("");

    labelTitle->SetLabel(
        session.getName() +
        " " +
        session.getSurname());

    if (session.getAdmin())
    {
        adminPanel->Show();
    }
    else
    {
        adminPanel->Hide();
    }

    historyListSizer->Clear(true);
    std::vector<VehicleSummary> history = _model->getRentalHistory();

    if (history.empty())
    {
        wxStaticText *emptyLabel = new wxStaticText(historyPanel, wxID_ANY, "Brak historii wynajmu.");
        emptyLabel->SetForegroundColour(wxColour(156, 163, 175));
        historyListSizer->Add(emptyLabel, 0, wxALIGN_CENTER | wxBOTTOM, 20);
    }
    else
    {
        for (const auto &v : history)
        {
            wxPanel *row = new wxPanel(historyPanel, wxID_ANY);
            row->SetBackgroundColour(wxColour(55, 65, 81));
            wxBoxSizer *rowSizer = new wxBoxSizer(wxVERTICAL);

            wxStaticText *txt = new wxStaticText(row, wxID_ANY,
                                                 wxString::Format("%s %s (%s) - %s", 
                                                     v.brand.c_str(), 
                                                     v.model.c_str(), 
                                                     v.year.c_str(), 
                                                     v.color.c_str()));
            txt->SetForegroundColour(wxColour(229, 231, 235));
            rowSizer->Add(txt, 0, wxALL, 10);

            row->SetSizer(rowSizer);
            historyListSizer->Add(row, 0, wxEXPAND | wxBOTTOM, 10);
        }
    }

    Layout();
}

void UserPageView::updateUserData(const std::string& fullName, bool isAdmin, const std::vector<VehicleSummary>& history)
{
    if (!labelTitle || !historyListSizer || !adminPanel || !historyPanel)
    {
        return;
    }

    info->SetLabel("");
    labelTitle->SetLabel(wxString::FromUTF8(fullName.c_str()));

    if (isAdmin)
    {
        adminPanel->Show();
    }
    else
    {
        adminPanel->Hide();
    }

    historyListSizer->Clear(true);

    if (history.empty())
    {
        wxStaticText *emptyLabel = new wxStaticText(historyPanel, wxID_ANY, "Brak historii wynajmu.");
        emptyLabel->SetForegroundColour(wxColour(156, 163, 175));
        historyListSizer->Add(emptyLabel, 0, wxALIGN_CENTER | wxBOTTOM, 20);
    }
    else
    {
        for (const auto &v : history)
        {
            wxPanel *row = new wxPanel(historyPanel, wxID_ANY);
            row->SetBackgroundColour(wxColour(55, 65, 81));
            wxBoxSizer *rowSizer = new wxBoxSizer(wxVERTICAL);

            wxStaticText *txt = new wxStaticText(row, wxID_ANY,
                wxString::Format("%s %s (%s) - %s", 
                    v.brand.c_str(), 
                    v.model.c_str(), 
                    v.year.c_str(), 
                    v.color.c_str()));
            
            txt->SetForegroundColour(wxColour(229, 231, 235));
            rowSizer->Add(txt, 0, wxALL, 10);

            row->SetSizer(rowSizer);
            historyListSizer->Add(row, 0, wxEXPAND | wxBOTTOM, 10);
        }
    }

    Layout();
}

void UserPageView::clearInputs()
{
    if (_validator)
    {
        _validator->clearFields(std::vector<wxTextCtrl*>{
            vinInput, brandInput, modelInput, yearInput, colorInput,
            fuelTypeInput, technicalStatusInput, mileageInput, numberOfSeatsInput,
            engineCapacityInput, handleBarsTypeInput, maxCargoWeightInput, numberOfAxlesInput
        });
    }
    info->SetLabel("");
}