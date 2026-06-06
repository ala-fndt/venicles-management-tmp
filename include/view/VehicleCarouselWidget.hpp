#ifndef VEHICLECAROUSELWIDGET_HPP
#define VEHICLECAROUSELWIDGET_HPP

#include "../additionalScripts/Logger.hpp"
#include "../database/Database.hpp"
#include "../include/classes/IRefreshable.hpp"
#include "../include/model/VehicleSummary.hpp"

class Database;
class Logger;
struct VehicleSummary;
#include <memory>
#include <wx/scrolwin.h>
#include <wx/wx.h>

class VehicleCarouselWidget : public wxPanel {
public:
  void refreshVehicles();
  VehicleCarouselWidget(wxWindow *parent, Database *database, Logger *logger,
                        IRefreshable *listToRefresh = nullptr);

private:
  Database *m_database;
  Logger *m_logger;
  IRefreshable *m_listToRefresh;

  wxScrolledWindow *m_scrollList;
  wxBoxSizer *m_scrollSizer;
  wxPanel *m_detailPanel;
  wxStaticText *m_detailPlaceholder;
  wxStaticText *m_detailBrand;
  wxStaticText *m_detailYear;
  wxStaticText *m_detailColor;
  wxButton *m_reserveBtn;

  std::shared_ptr<VehicleSummary> m_selected;

  void rebuildList();
};

#endif // !VEHICLECAROUSELWIDGET_HPP
