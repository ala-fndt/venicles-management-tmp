#ifndef USER_PAGE_VIEW_HPP
#define USER_PAGE_VIEW_HPP

#include "../classes/IRefreshable.hpp"
#include <wx/wx.h>
#include "../additionalScripts/Validator.hpp"
#include "../model/VehicleSummary.hpp"

class UserPageModel;

class UserPageView : public wxPanel, public IRefreshable {
private:
  UserPageModel *_model;
  Validator *_validator;
public:
  std::string userName;
  bool isAdmin;

  wxStaticText *info;
  wxButton *backButton;

  wxStaticText *labelTitle;
  wxPanel *adminPanel;

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
  

  wxButton *addVehicleButton;

  wxPanel *historyPanel;
  wxBoxSizer *historyListSizer;

  UserPageView(wxWindow *window, Validator *validator, UserPageModel *model);

  void refresh() override;
  void clearInputs();
};

#endif // !USER_PAGE_VIEW_HPP
