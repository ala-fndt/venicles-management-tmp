#ifndef VEHICLECAROUSELWIDGET_HPP
#define VEHICLECAROUSELWIDGET_HPP

#include <wx/wx.h>
#include <string>
#include <vector>

class Database;
class Logger;
struct VehicleSummary;

// Enkapsuluje lewy panel (slider aut) i prawy panel (podsumowanie rezerwacji).
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
  VehicleCarouselWidget(wxWindow *parent, Database *database, Logger *logger);
  void refreshVehicles();
};

#endif // !VEHICLECAROUSELWIDGET_HPP
