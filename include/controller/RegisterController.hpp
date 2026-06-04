#ifndef REGISTER_CONTROLLER_HPP
#define REGISTER_CONTROLLER_HPP

#include "../additionalScripts/Logger.hpp"
#include "../additionalScripts/Validator.hpp"
#include "../classes/Router.hpp"
#include "../model/RegisterModel.hpp"
#include "../view/RegisterView.hpp"

class RegisterController {
private:
  RegisterModel *_model;
  RegisterView *_view;
  Router *router;
  Logger *logger;
  Validator *validator;

public:
  RegisterController(RegisterModel *model, RegisterView *view, Router *router,
                     Logger *logger, Validator *validator);

  ~RegisterController();

  void OnRegisterClicked(wxCommandEvent &event);
  void OnBackClicked(wxCommandEvent &event);
};

#endif // !REGISTER_CONTROLLER_HPP
