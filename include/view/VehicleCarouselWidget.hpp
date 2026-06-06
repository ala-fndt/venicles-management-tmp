#ifndef VEHICLECAROUSELWIDGET_HPP
#define VEHICLECAROUSELWIDGET_HPP

#include "../additionalScripts/Logger.hpp"
#include "../classes/IRefreshable.hpp"
#include "../database/Database.hpp"
#include "../model/VehicleSummary.hpp"
#include <string>
#include <vector>
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
  IRefreshable *listToRefresh;

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
};

#endif // !VEHICLECAROUSELWIDGET_HPP
