#include "../include/view/LoginView.hpp"
#include "../include/additionalScripts/Validator.hpp"
#include <wx/dcbuffer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>

LoginView::~LoginView() {}

LoginView::LoginView(wxWindow *window, Router *router, Validator *validator_ptr) : wxPanel(window), validator(validator_ptr) {
  SetBackgroundColour(wxColour(17, 24, 39));
  SetForegroundColour(wxColour(229, 231, 235));

  wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
  mainSizer->AddStretchSpacer(1);

  wxBoxSizer *formSizer = new wxBoxSizer(wxVERTICAL);

  wxStaticText *titleLabel =
      new wxStaticText(this, wxID_ANY, "Login", wxDefaultPosition,
                       wxDefaultSize, wxALIGN_CENTER);
  titleLabel->SetFont(
      wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  titleLabel->SetForegroundColour(wxColour(255, 255, 255));
  formSizer->Add(titleLabel, 0, wxALIGN_CENTER | wxBOTTOM, 4);

  wxStaticText *subLabel =
      new wxStaticText(this, wxID_ANY, "Enter your details to continue",
                       wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
  subLabel->SetFont(
      wxFont(9, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
  subLabel->SetForegroundColour(wxColour(107, 114, 128));
  formSizer->Add(subLabel, 0, wxALIGN_CENTER | wxBOTTOM, 24);

  errorRow = new wxBoxSizer(wxHORIZONTAL);
  if (!this->errors.empty()) {
    for (std::string errorMessage : this->errors) {
      wxStaticText *labelError = new wxStaticText(this, wxID_ANY, errorMessage);
      labelError->SetForegroundColour(wxColour(248, 113, 113));
      errorRow->Add(labelError, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
    }
  }
  formSizer->Add(errorRow, 0, wxEXPAND | wxBOTTOM, 10);

  wxBoxSizer *emailRow = new wxBoxSizer(wxHORIZONTAL);

  wxStaticText *labelEmail = new wxStaticText(this, wxID_ANY, "Email: ");
  labelEmail->SetFont(
      wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  labelEmail->SetForegroundColour(wxColour(156, 163, 175));

  email = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(50, 30));

  email->SetBackgroundColour(wxColour(31, 41, 55));
  email->SetForegroundColour(wxColour(243, 244, 246));
  email->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                        wxFONTWEIGHT_NORMAL));

  emailRow->Add(labelEmail, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 20);
  emailRow->Add(email, 1);
  formSizer->Add(emailRow, 0, wxEXPAND | wxBOTTOM, 12);

  wxBoxSizer *passwordRow = new wxBoxSizer(wxHORIZONTAL);

  wxStaticText *labelPassword = new wxStaticText(this, wxID_ANY, "Password: ");
  labelPassword->SetFont(
      wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  labelPassword->SetForegroundColour(wxColour(156, 163, 175));

  password = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition,
                            wxSize(50, 30), wxTE_PASSWORD);
  password->SetBackgroundColour(wxColour(31, 41, 55));
  password->SetForegroundColour(wxColour(243, 244, 246));
  password->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                           wxFONTWEIGHT_NORMAL));

  passwordRow->Add(labelPassword, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
  passwordRow->Add(password, 1);
  formSizer->Add(passwordRow, 0, wxEXPAND | wxBOTTOM, 24);

  wxBoxSizer *btnRow = new wxBoxSizer(wxHORIZONTAL);

  logInBtn =
      new wxButton(this, wxID_ANY, "Log In", wxDefaultPosition, wxSize(-1, 38));
  logInBtn->SetBackgroundColour(wxColour(99, 102, 241));
  logInBtn->SetForegroundColour(wxColour(255, 255, 255));
  logInBtn->SetFont(
      wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

  btnRow->Add(logInBtn, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
  registerBtn = new wxButton(this, wxID_ANY, "Register", wxDefaultPosition,
                             wxSize(-1, 38));
  registerBtn->SetBackgroundColour(wxColour(99, 102, 241));
  registerBtn->SetForegroundColour(wxColour(255, 255, 255));
  registerBtn->SetFont(
      wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

  btnRow->Add(registerBtn, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);

  formSizer->Add(btnRow, 0, wxALIGN_CENTER | wxBOTTOM, 10);

  mainSizer->Add(formSizer, 0, wxEXPAND | wxLEFT | wxRIGHT, 40);
  mainSizer->AddStretchSpacer(1);
  this->SetSizer(mainSizer);
}

void LoginView::setErrors(const std::vector<std::string> &errors) {
  this->errors = errors;
  errorRow->Clear(true);
  for (const auto &msg : errors) {
    wxStaticText *label = new wxStaticText(this, wxID_ANY, msg);
    label->SetForegroundColour(wxColour(248, 113, 113));
    label->SetFont(wxFont(9, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                          wxFONTWEIGHT_NORMAL));
    errorRow->Add(label, 0, wxALIGN_CENTER | wxBOTTOM, 5);
  }
  this->Layout();
  this->GetParent()->Layout();
}

std::vector<std::string> LoginView::getErrors() const { return this->errors; }

void LoginView::clearInputs() {
  if (validator) {
    validator->clearFields({email, password});
  }
  setErrors({}); // Also clear any displayed errors
}
