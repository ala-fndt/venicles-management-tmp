#ifndef VEHICLECAROUSELWIDGET_HPP
#define VEHICLECAROUSELWIDGET_HPP

#include <wx/wx.h>

class Database;
class Logger;
struct VehicleSummary;

// Enkapsuluje lewy panel (slider aut) i prawy panel (podsumowanie rezerwacji).
class VehicleCarouselWidget : public wxPanel {
private:
  Database *database;
  Logger *logger;

  wxPanel *detailPanel;
  wxStaticText *detailPlaceholder;
  wxStaticText *detailBrand;
  wxStaticText *detailYear;
  wxStaticText *detailColor;
  wxStaticText *reserveInfo;
  wxButton *reserveBtn;
  int selectedVehicleId;

  wxScrolledWindow *scrollList;
  wxBoxSizer *scrollSizer;

  void buildVehicleRows(const std::vector<VehicleSummary> &vehicles);

public:
  VehicleCarouselWidget(wxWindow *parent, Database *database, Logger *logger);
  void refreshVehicles();
};

#endif // !VEHICLECAROUSELWIDGET_HPP
