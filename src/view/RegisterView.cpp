#include "../include/view/RegisterView.hpp"
#include "../include/classes/Router.hpp"
#include "../include/additionalScripts/Validator.hpp"

RegisterView::~RegisterView() {}

RegisterView::RegisterView(wxWindow *window, Router *router, Validator *validator_ptr)
    : wxPanel(window), router(router), validator(validator_ptr) {
  SetBackgroundColour(wxColour(17, 24, 39));
  SetForegroundColour(wxColour(229, 231, 235));
  wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
  mainSizer->AddStretchSpacer(1);

  wxBoxSizer *formSizer = new wxBoxSizer(wxVERTICAL);

  wxStaticText *titleLabel =
      new wxStaticText(this, wxID_ANY, "Registration", wxDefaultPosition,
                       wxDefaultSize, wxALIGN_CENTER);
  titleLabel->SetFont(
      wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  titleLabel->SetForegroundColour(wxColour(255, 255, 255));
  formSizer->Add(titleLabel, 0, wxALIGN_CENTER | wxBOTTOM, 4);

  wxStaticText *subLabel =
      new wxStaticText(this, wxID_ANY, "Fill out the form to create an account",
                       wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
  subLabel->SetFont(wxFont(9, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                           wxFONTWEIGHT_NORMAL));
  subLabel->SetForegroundColour(wxColour(107, 114, 128));
  formSizer->Add(subLabel, 0, wxALIGN_CENTER | wxBOTTOM, 24);

  errorRow = new wxBoxSizer(wxHORIZONTAL);
  formSizer->Add(errorRow, 0, wxEXPAND | wxBOTTOM, 10);

  // Wiersz: Imie
  wxBoxSizer *nameRow = new wxBoxSizer(wxHORIZONTAL);
  wxStaticText *labelName = new wxStaticText(this, wxID_ANY, "First Name: ");
  labelName->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                            wxFONTWEIGHT_BOLD));
  labelName->SetForegroundColour(wxColour(156, 163, 175));
  name = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(50, 30));
  name->SetBackgroundColour(wxColour(31, 41, 55));
  name->SetForegroundColour(wxColour(243, 244, 246));
  name->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                       wxFONTWEIGHT_NORMAL));
  nameRow->Add(labelName, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 20);
  nameRow->Add(name, 1);
  formSizer->Add(nameRow, 0, wxEXPAND | wxBOTTOM, 12);

  // Wiersz: Nazwisko
  wxBoxSizer *surnameRow = new wxBoxSizer(wxHORIZONTAL);
  wxStaticText *labelSurname = new wxStaticText(this, wxID_ANY, "Last Name: ");
  labelSurname->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                               wxFONTWEIGHT_BOLD));
  labelSurname->SetForegroundColour(wxColour(156, 163, 175));
  surname =
      new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(50, 30));
  surname->SetBackgroundColour(wxColour(31, 41, 55));
  surname->SetForegroundColour(wxColour(243, 244, 246));
  surname->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                          wxFONTWEIGHT_NORMAL));
  surnameRow->Add(labelSurname, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
  surnameRow->Add(surname, 1);
  formSizer->Add(surnameRow, 0, wxEXPAND | wxBOTTOM, 12);

  // Wiersz: Email
  wxBoxSizer *emailRow = new wxBoxSizer(wxHORIZONTAL);
  wxStaticText *labelEmail = new wxStaticText(this, wxID_ANY, "Email: ");
  labelEmail->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                             wxFONTWEIGHT_BOLD));
  labelEmail->SetForegroundColour(wxColour(156, 163, 175));
  email = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(50, 30));
  email->SetBackgroundColour(wxColour(31, 41, 55));
  email->SetForegroundColour(wxColour(243, 244, 246));
  email->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                        wxFONTWEIGHT_NORMAL));
  emailRow->Add(labelEmail, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 20);
  emailRow->Add(email, 1);
  formSizer->Add(emailRow, 0, wxEXPAND | wxBOTTOM, 12);

  // Wiersz: Haslo
  wxBoxSizer *passwordRow = new wxBoxSizer(wxHORIZONTAL);
  wxStaticText *labelPassword = new wxStaticText(this, wxID_ANY, "Password: ");
  labelPassword->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                                wxFONTWEIGHT_BOLD));
  labelPassword->SetForegroundColour(wxColour(156, 163, 175));
  password = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition,
                            wxSize(50, 30), wxTE_PASSWORD);
  password->SetBackgroundColour(wxColour(31, 41, 55));
  password->SetForegroundColour(wxColour(243, 244, 246));
  password->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                           wxFONTWEIGHT_NORMAL));
  passwordRow->Add(labelPassword, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 20);
  passwordRow->Add(password, 1);
  formSizer->Add(passwordRow, 0, wxEXPAND | wxBOTTOM, 12);

  // Wiersz: Potwierdz haslo
  wxBoxSizer *confirmRow = new wxBoxSizer(wxHORIZONTAL);
  wxStaticText *labelConfirm =
      new wxStaticText(this, wxID_ANY, "Confirm: ");
  labelConfirm->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                               wxFONTWEIGHT_BOLD));
  labelConfirm->SetForegroundColour(wxColour(156, 163, 175));
  confirmPassword = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition,
                                   wxSize(50, 30), wxTE_PASSWORD);
  confirmPassword->SetBackgroundColour(wxColour(31, 41, 55));
  confirmPassword->SetForegroundColour(wxColour(243, 244, 246));
  confirmPassword->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT,
                                  wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
  confirmRow->Add(labelConfirm, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
  confirmRow->Add(confirmPassword, 1);
  formSizer->Add(confirmRow, 0, wxEXPAND | wxBOTTOM, 24);

  // Przyciski
  wxBoxSizer *btnRow = new wxBoxSizer(wxHORIZONTAL);

  registerBtn = new wxButton(this, wxID_ANY, "Register", wxDefaultPosition,
                             wxSize(-1, 38));
  registerBtn->SetBackgroundColour(wxColour(99, 102, 241));
  registerBtn->SetForegroundColour(wxColour(255, 255, 255));
  registerBtn->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                              wxFONTWEIGHT_BOLD));

  backBtn = new wxButton(this, wxID_ANY, "Back", wxDefaultPosition,
                         wxSize(-1, 38));
  backBtn->SetBackgroundColour(wxColour(55, 65, 81));
  backBtn->SetForegroundColour(wxColour(255, 255, 255));
  backBtn->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                          wxFONTWEIGHT_BOLD));

  btnRow->Add(registerBtn, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
  btnRow->Add(backBtn, 0, wxALIGN_CENTER_VERTICAL);

  formSizer->Add(btnRow, 0, wxALIGN_CENTER | wxBOTTOM, 10);

  mainSizer->Add(formSizer, 0, wxEXPAND | wxLEFT | wxRIGHT, 40);
  mainSizer->AddStretchSpacer(1);
  this->SetSizer(mainSizer);
}

void RegisterView::setErrors(const std::vector<std::string> &errors) {
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

void RegisterView::clearInputs() {
  if (validator) {
    validator->clearFields({name, surname, email, password, confirmPassword});
  }
  setErrors({});
}

std::vector<std::string> RegisterView::getErrors() const {
  return this->errors;
}
