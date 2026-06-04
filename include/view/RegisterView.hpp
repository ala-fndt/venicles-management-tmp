#ifndef REGISTER_VIEW_HPP
#define REGISTER_VIEW_HPP

#include <wx/wx.h>
class Validator;

class Router;

class RegisterView : public wxPanel {
private:
  Router *router;
  std::vector<std::string> errors;
  Validator *validator;

public:
  wxTextCtrl *name;
  wxTextCtrl *surname;
  wxTextCtrl *email;
  wxTextCtrl *password;
  wxTextCtrl *confirmPassword;
  wxButton *registerBtn;
  wxButton *backBtn;
  wxBoxSizer *errorRow;

  RegisterView(wxWindow *window, Router *router, Validator *validator);
  virtual ~RegisterView();

  void setErrors(const std::vector<std::string> &errors);
  std::vector<std::string> getErrors() const;

  wxString getNameValue() const { return name->GetValue(); }
  wxString getSurnameValue() const { return surname->GetValue(); }
  wxString getEmailValue() const { return email->GetValue(); }
  wxString getPasswordValue() const { return password->GetValue(); }
  wxString getConfirmPasswordValue() const { return confirmPassword->GetValue(); }
  
  void clearInputs();
};

#endif // !REGISTER_VIEW_HPP
