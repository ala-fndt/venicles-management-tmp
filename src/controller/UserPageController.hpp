#ifndef USER_PAGE_CONTROLLER_HPP
#define USER_PAGE_CONTROLLER_HPP

#include "UserPageView.hpp"
#include "UserPageModel.hpp"
#include "../../include/classes/Router.hpp"
#include "../../include/additionalScripts/Validator.hpp"

class UserPageController {
public:
    UserPageController(UserPageView *view, UserPageModel *model, Router *router, Validator *validator);

private:
    void OnBackButtonClick(wxCommandEvent &event);
    void OnAddVehicleClicked(wxCommandEvent &event);

    UserPageView *_view;
    UserPageModel *_model;
    Validator *_validator;
    Router *router;
};

#endif