#include "../../include/controller/UserPageController.hpp"
#include "../../include/view/UserPageView.hpp"
#include "../../include/model/UserPageModel.hpp"
#include <ctime>

UserPageController::UserPageController(UserPageView *view, UserPageModel *model,
                                       Router *router, Validator *validator)
    : _view(view), _model(model), _validator(validator), router(router) {
    
    if (!_view || !_model) {
        return;
    }

    _view->backButton->Bind(wxEVT_BUTTON, &UserPageController::OnBackButtonClick, this);
    _view->addVehicleButton->Bind(wxEVT_BUTTON, &UserPageController::OnAddVehicleClicked, this);

    // KONTROLER decyduje co przekazać do widoku
    _view->updateUserData(
        _model->getCurrentUserFullName(),
        _model->isCurrentUserAdmin(),
        _model->getRentalHistory()
    );
}

void UserPageController::OnBackButtonClick(wxCommandEvent &event) {
    _view->clearInputs();
    this->router->navigate("home");
    _view->GetParent()->Layout();
}

void UserPageController::OnAddVehicleClicked(wxCommandEvent &event) {
    if (!_view || !_model || !_validator) return;

    if (!_view->info || !_view->vinInput || !_view->brandInput || !_view->modelInput ||
        !_view->yearInput || !_view->colorInput || !_view->fuelTypeInput ||
        !_view->technicalStatusInput || !_view->mileageInput ||
        !_view->numberOfSeatsInput || !_view->engineCapacityInput ||
        !_view->handleBarsTypeInput || !_view->maxCargoWeightInput ||
        !_view->numberOfAxlesInput) {
        return;
    }

    std::string vin = _view->vinInput->GetValue().Upper().ToStdString();
    std::string brand = _view->brandInput->GetValue().Upper().ToStdString();
    std::string model = _view->modelInput->GetValue().Upper().ToStdString();
    std::string year = _view->yearInput->GetValue().ToStdString();
    std::string color = _view->colorInput->GetValue().Upper().ToStdString();
    std::string fuelType = _view->fuelTypeInput->GetValue().Upper().ToStdString();
    std::string status = _view->technicalStatusInput->GetValue().Upper().ToStdString();
    std::string mileage = _view->mileageInput->GetValue().ToStdString();
    std::string seats = _view->numberOfSeatsInput->GetValue().ToStdString();
    std::string engine = _view->engineCapacityInput->GetValue().ToStdString();
    std::string handle = _view->handleBarsTypeInput->GetValue().Upper().ToStdString();
    std::string cargo = _view->maxCargoWeightInput->GetValue().ToStdString();
    std::string axles = _view->numberOfAxlesInput->GetValue().ToStdString();
    
    _view->info->SetLabel("");

    if (_validator->checkEmpty(vin) || _validator->checkEmpty(brand) || 
        _validator->checkEmpty(model) || _validator->checkEmpty(year) ||
        _validator->checkEmpty(fuelType) || _validator->checkEmpty(status) ||
        _validator->checkEmpty(mileage)) {
        
        _view->info->SetLabel("Blad: Wszystkie pola musza byc wypelnione!");
        _view->info->SetForegroundColour(wxColour(248, 113, 113));
        _view->Layout();
        return;
    }

    try {
    int yearInt = std::stoi(year);
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    int currentYear = now->tm_year + 1900;

    if (yearInt < 1885 || yearInt > currentYear) {
        _view->info->SetLabel("Blad: Rok poza zakresem (1885 - " + std::to_string(currentYear) + ")!");
        _view->info->SetForegroundColour(wxColour(248, 113, 113));
        return; 
    }

    int mileageInt = std::stoi(mileage);
    int seatsInt   = seats.empty()  ? 0 : std::stoi(seats);
    int engineInt  = engine.empty() ? 0 : std::stoi(engine);
    int cargoInt   = cargo.empty()  ? 0 : std::stoi(cargo);
    int axlesInt   = axles.empty()  ? 0 : std::stoi(axles);
    if (!_model->addVehicle(vin, brand, model, year, color, fuelType, status, 
                            mileageInt, seatsInt, engineInt, handle, cargoInt, axlesInt)) {
        
        _view->info->SetLabel("Blad: Nie udalo sie dodac pojazdu!");
        _view->info->SetForegroundColour(wxColour(248, 113, 113));
    } else {
        _view->clearInputs();
        _view->updateUserData(
            _model->getCurrentUserFullName(),
            _model->isCurrentUserAdmin(),
            _model->getRentalHistory()
        );

        _view->info->SetLabel("Sukces: Pojazd zostal dodany!");
        _view->info->SetForegroundColour(wxColour(52, 211, 153));
    }

} catch (const std::exception& e) {
    _view->info->SetLabel("Blad: Nieprawidlowe dane liczbowe!");
    _view->info->SetForegroundColour(wxColour(248, 113, 113));
}
    _view->Layout();
}