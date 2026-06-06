#ifndef VEHICLELISTPANEL_HPP
#define VEHICLELISTPANEL_HPP

#include "../additionalScripts/Logger.hpp"
#include "../database/Database.hpp"
#include "../include/classes/IRefreshable.hpp"
#include "../include/model/VehicleSummary.hpp"
#include <wx/scrolwin.h>
#include <wx/wx.h>

class VehicleListPanel : public wxPanel, public IRefreshable {
public:
  VehicleListPanel(wxWindow *parent, Database *database, Logger *logger);
  void refresh() override;

private:
  Database *m_database;
  Logger *m_logger;
  wxScrolledWindow *m_scrollArea;
  wxBoxSizer *m_listSizer;

  void populateList(const std::vector<VehicleSummary> &vehicles);
  void clearList();
};

#endif // !VEHICLELISTPANEL_HPP
