#ifndef LOGIN_VIEW_HPP
#define LOGIN_VIEW_HPP
#include <wx/richtext/richtextctrl.h>
#include <wx/wx.h>

class Router;
class Validator;

class LoginView : public wxPanel {
private:
  Router *router;
  std::vector<std::string> errors;
  Validator *validator;

public:
  wxTextCtrl *email;
  wxTextCtrl *password;
  wxButton *logInBtn;
  wxButton *registerBtn;
  wxBoxSizer *errorRow;

  LoginView(wxWindow *window, Router *router, Validator *validator);
  virtual ~LoginView();

  void setErrors(const std::vector<std::string> &errors);
  std::vector<std::string> getErrors() const;

  wxString getEmailValue() const { return email->GetValue(); }
  wxString getPasswordValue() const { return password->GetValue(); }

  void clearInputs();
};

#endif // !LOGIN_VIEW_HPP
