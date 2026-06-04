#ifndef VEHICLELISTPANEL_HPP
#define VEHICLELISTPANEL_HPP

#include "../include/model/HomeModel.hpp"
#include <wx/wx.h>

class VehicleListPanel : public wxPanel {
public:
  VehicleListPanel(wxWindow *parent, const std::vector<VehicleSummary> &vehicles);
};

#endif // !VEHICLELISTPANEL_HPP
