#ifndef VEHICLECAROUSELWIDGET_HPP
#define VEHICLECAROUSELWIDGET_HPP

#include <wx/wx.h>
#include <string>
#include <vector>
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
private:
  struct ActiveReservationInfo {
    bool isReserved = false;
    int userId = -1;
    std::string userFullName;
  };

  Database *database;
  Logger *logger;

  wxPanel *detailPanel;
  wxStaticText *detailPlaceholder;
  wxStaticText *detailBrand;
  wxStaticText *detailYear;
  wxStaticText *detailColor;
  wxStaticText *detailReservationStatus;
  wxStaticText *reserveInfo;
  wxButton *reserveBtn;
  wxButton *returnBtn;
  wxButton *takeBtn;
  int selectedVehicleId;

  wxScrolledWindow *scrollList;
  wxBoxSizer *scrollSizer;
  wxPanel *reservedPanel;
  wxScrolledWindow *reservedScrollList;
  wxBoxSizer *reservedListSizer;

  void buildVehicleRows(const std::vector<VehicleSummary> &vehicles);
  void refreshReservedList();
  ActiveReservationInfo getReservationInfo(int vehicleId) const;
  void populateDetailPanel(const VehicleSummary &vehicle);
  bool isVehicleReservedByAnotherUser(int vehicleId, int userId) const;
  void refreshActionButtons();

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
