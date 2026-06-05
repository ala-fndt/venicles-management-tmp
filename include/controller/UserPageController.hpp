#ifndef USER_PAGE_CONTROLLER_HPP
#define USER_PAGE_CONTROLLER_HPP

#include "../view/UserPageView.hpp"
#include "../model/UserPageModel.hpp"
#include "../classes/Router.hpp"
#include "../additionalScripts/Validator.hpp"
#include <wx/wx.h>

class UserPageController {
private:
    UserPageView* _view;
    UserPageModel* _model;
    Validator* _validator;
    Router* router;

public:
    UserPageController(UserPageView* view, UserPageModel* model, Router* router, Validator* validator);
    virtual ~UserPageController() = default;

    void OnBackButtonClick(wxCommandEvent& event);
    void OnAddVehicleClicked(wxCommandEvent& event);
};

#endif // !USER_PAGE_CONTROLLER_HPP