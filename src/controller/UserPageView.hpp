#ifndef USER_PAGE_VIEW_HPP
#define USER_PAGE_VIEW_HPP

#include <wx/wx.h>
#include <vector>
#include <string>
#include "../../include/additionalScripts/Validator.hpp"
#include "UserPageModel.hpp"

class UserPageView : public wxPanel {
public:
    UserPageView(wxWindow *window, Validator *validator, UserPageModel *model);
    void refresh();
    void clearInputs();

    wxButton *backButton;
    wxButton *addVehicleButton;
    wxStaticText *info;
    wxStaticText *labelTitle;
    
    // Pola formularza
    wxTextCtrl *vinInput;
    wxTextCtrl *brandInput;
    wxTextCtrl *modelInput;
    wxTextCtrl *yearInput;
    wxTextCtrl *colorInput;
    wxTextCtrl *fuelTypeInput;
    wxTextCtrl *technicalStatusInput;
    wxTextCtrl *mileageInput;
    wxTextCtrl *numberOfSeatsInput;
    wxTextCtrl *engineCapacityInput;
    wxTextCtrl *handleBarsTypeInput;
    wxTextCtrl *maxCargoWeightInput;
    wxTextCtrl *numberOfAxlesInput;

    wxPanel *adminPanel;
    wxPanel *historyPanel;
    wxBoxSizer *historyListSizer;

    bool isAdmin;

private:
    Validator *_validator;
    UserPageModel *_model;
};

#endif