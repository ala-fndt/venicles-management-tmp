#ifndef ROUTER_HPP
#define ROUTER_HPP

#include "../include/additionalScripts/Logger.hpp"
#include <unordered_map>
#include <wx/wx.h>

/**
 * @file Router.hpp
 * @brief Klasa do obsługi zmiany widokow aplikacji
 */
class Router {
private:
  std::unordered_map<std::string, wxWindow *> routes;
  std::string current;
  wxWindow *container;
  bool checkRouteExist(std::string name);

public:
  Logger *logger;
  Router(wxWindow *container, Logger *logger);
  ~Router();

  /**
   * @brief Metoda dodajaca widoki do pamieci Routera
   *
   * @param std::string nazwa strony (w pamieci routera)
   * @param wxWindow klasa strony okna
   *
   * @example
   *
   */
  void add(const std::string &name, wxWindow *window);

  /**
   * @brief Metoda usuwajaca widoki z pamieci Routera
   *
   * @param std::string nazwa strony (w pamieci routera)
   *
   * @example
   */
  void remove(std::string name);

  /**
   * @brief Metoda zmieniajaca widoki
   *
   * @param std::string nazwa strony (w pamieci routera)
   *
   * @example
   */
  void navigate(std::string name);

  /**
   * @brief Funckja logujaca strony znajdujace sie w pamieci routera
   */
  void showAllRoutes();

  /**
   * @brief Funckja szukajaca routingow w pamieci routera
   *
   * @param std::string nazwa strony
   *
   * @param bool isSilent ustawienie wyłączenia loggowania (włączamy tylko dla
   * Debug)
   */
  bool findRoute(const std::string &name, bool isSilent = false);
};

#endif // !ROUTER_HPP
