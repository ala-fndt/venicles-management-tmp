#ifndef USER_PAGE_VIEW_HPP
#define USER_PAGE_VIEW_HPP

#include "../include/classes/IRefreshable.hpp"
#include <wx/wx.h>
#include "../include/additionalScripts/Validator.hpp"
#include "../include/model/VehicleSummary.hpp"

class UserPageModel;

class UserPageView : public wxPanel, public IRefreshable {
private:
  UserPageModel *_model;
public:
  std::string userName;
  Validator *validator;
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

  wxButton *addVehicleButton;

  wxPanel *historyPanel;
  wxBoxSizer *historyListSizer;

  UserPageView(wxWindow *window, Validator *validator, UserPageModel *model);

  void refresh() override;
  void clearInputs();
};

#endif // !USER_PAGE_VIEW_HPP
