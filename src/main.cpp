#include "../include/additionalScripts/Logger.hpp"
#include "../include/database/Database.hpp"
#include "../include/view/MainView.hpp"
#include <wx/wx.h>

class VenicleManagement : public wxApp {

public:
  virtual bool OnInit() override {

    Logger *logger = new Logger();

    Database *database = new Database(logger);
    database->initDatabase();

    MainView *mainView = new MainView(logger, database);

    SetTopWindow(mainView);
    mainView->Show(true);
    mainView->Raise();
    mainView->SetFocus();

    return true;
  }
};

wxIMPLEMENT_APP(VenicleManagement);
