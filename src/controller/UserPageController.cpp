#include "../../include/controller/UserPageController.hpp"
#include "../../include/classes/Session.hpp"
#include <ctime>

UserPageController::UserPageController(UserPageView *view, UserPageModel *model,
                                       Router *router, Validator *validator)
    : _view(view), _model(model), _validator(validator), router(router) {

  _view->backButton->Bind(wxEVT_BUTTON, &UserPageController::OnBackButtonClick,
                          this);

  _view->addVehicleButton->Bind(wxEVT_BUTTON, &UserPageController::OnAddVehicleClicked, this);

  _view->isAdmin = Session::getInstance().getAdmin();
}

void UserPageController::OnBackButtonClick(wxCommandEvent &event) {
  _view->clearInputs();
  this->router->navigate("home");
  _view->GetParent()->Layout(); // Force layout update on the container
}

void UserPageController::OnAddVehicleClicked(wxCommandEvent &event) {
    std::string vin = _view->vinInput->GetValue().Upper().ToStdString();
    std::string brand = _view->brandInput->GetValue().Upper().ToStdString();
    std::string model = _view->modelInput->GetValue().Upper().ToStdString();
    std::string year = _view->yearInput->GetValue().ToStdString();
    std::string color = _view->colorInput->GetValue().Upper().ToStdString();
    std::string pricePerDay = _view->pricePerDayInput->GetValue().ToStdString();
    
    _view->info->SetLabel("");

    if (_validator->checkEmpty(vin) || 
        _validator->checkEmpty(brand) || 
        _validator->checkEmpty(model) ||
        _validator->checkEmpty(year)) {
        
        _view->info->SetLabel("Blad: Wszystkie pola musza byc wypelnione!");
        _view->info->SetForegroundColour(wxColour(248, 113, 113));
        _view->Layout();
        return;
    }

    // Walidacja zakresu roku
    int yearInt = std::stoi(year);
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    int currentYear = now->tm_year + 1900;

    if (yearInt < 1885 || yearInt > currentYear) {
        std::string errorMsg = "Blad: Rok musi byc miedzy 1885 a " + std::to_string(currentYear) + "!";
        _view->info->SetLabel(errorMsg);
        _view->info->SetForegroundColour(wxColour(248, 113, 113));
        _view->Layout();
        return;
    }
    if (!_model->addVehicle(vin, brand, model, year, color)) {
        _view->info->SetLabel("Blad: Nie udalo sie dodac pojazdu do bazy danych!");
        _view->info->SetForegroundColour(wxColour(248, 113, 113));
        _view->Layout();
        return;
    }
  
    _view->clearInputs();
    _view->refresh();
    
    _view->info->SetLabel("Sukces: Pojazd zostal dodany pomyslnie!");
    _view->info->SetForegroundColour(wxColour(52, 211, 153));
    _view->Layout();
}
