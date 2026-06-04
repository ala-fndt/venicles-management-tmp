#ifndef VEHICLECAROUSELWIDGET_HPP
#define VEHICLECAROUSELWIDGET_HPP

#include <wx/wx.h>

class Database;
class Logger;

// Enkapsuluje lewy panel (slider aut) i prawy panel (podsumowanie rezerwacji).
class VehicleCarouselWidget : public wxPanel {
public:
  VehicleCarouselWidget(wxWindow *parent, Database *database, Logger *logger);
};

#endif // !VEHICLECAROUSELWIDGET_HPP
