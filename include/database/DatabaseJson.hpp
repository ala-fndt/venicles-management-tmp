#ifndef DATABASE_HPP
#define DATABASE_HPP

#include "../additionalScripts/Logger.hpp"
#include "../nlohmann/json.hpp"
#include <fstream>
#include <vector>

/**
 * @file Database.hpp
 * @brief Klasa do obsługi prostych operacji na plikach JSON.
 */
class Database {
private:
  std::string filename;
  std::string const db_path = "src/database/";
  Logger logger;

public:
  Database(std::string filename);

  ~Database();

  /**
   * @brief Funckja zapisujaca dane do pliku podanego w konstruktorze
   *
   * @tparam T Typ obiektu do zapisania (musi być serializowalny do JSON).
   * @param obiekt Obiekt, który chcemy zapisać.
   *
   * @example
   * Database db("users.json");
   *
   * User u{3, "Kuba", 22};
   * db.writeInto(u);
   */
  template <typename T> void writeInto(T &obiekt) {
    nlohmann::json serialize = obiekt;

    std::ofstream file(this->db_path + this->filename);

    if (file.is_open()) {
      file << serialize.dump(4);
      file.close();

      this->logger.log(LogLevel::Info, "Dane dodane do pliku");
    } else {
      this->logger.log(LogLevel::Error, "Blad otwarcia pliku");
    }
  };

  /**
   * @brief Funckja pobierajca dane z pliku i konwertujaca go na typ T
   *
   * @param std::string sciezka/nazwa pliku
   *
   * @return obiekt podanej klasy
   *
   * @example
   * Database db("users.json");
   * std::string path = "src/database/users.json";
   *
   * std::vector<User> users = db.getFrom<std::vector<User>>(path);
   *
   * for (const auto& u : users) {
   *     std::cout << u.name << std::endl;
   * }
   */

  template <typename T> T getFrom(std::string &sciezka) {
    std::ifstream plik(sciezka);

    if (!plik.is_open()) {
      this->logger.log(LogLevel::Error, "Nie można otworzyć pliku " + sciezka);
    }

    nlohmann::json deserialize;
    plik >> deserialize;

    return deserialize.get<T>();
  }

  /**
   * @brief Funkcja aktualizujaca dane w json
   *
   * @param T nowy obiekt klasy
   * @param int id elementu który chcemy aktualizowac
   * @param std::string sciezka/nazwa pliku
   *
   * @return true/false
   *
   * @note ! klasa MUSI posiadać id !
   *
   * @example
   * Database db("users.json");
   * std::string path = "src/database/users.json";
   *
   * User updated{0, "Janek", 26}; // id zostanie nadpisane
   *
   * bool result = db.updateById(updated, 1, path);
   *
   * if (result) {
   *     std::cout << "Zaktualizowano!" << std::endl;
   * }
   */
  template <typename T>
  bool updateById(T &updatedData, int id, std::string &sciezka) {

    std::ifstream plik(sciezka);

    nlohmann::json data;

    if (!plik.is_open()) {
      this->logger.log(LogLevel::Error, "Nie można otworzyć pliku " + sciezka);
      return false;
    }

    try {
      plik >> data;

    } catch (const nlohmann::json::parse_error &e) {
      this->logger.log(LogLevel::Critical,
                       "Blad parsowania JSON: " + std::string(e.what()));
    }

    std::vector<T> parsed_data = data.get<std::vector<T>>();

    bool found = false;

    for (T &item : parsed_data) {
      if (item.id == id) {
        item = updatedData;
        item.id = id;
        found = true;
        break;
      }
    }

    if (!found) {
      this->logger.log(LogLevel::Warning,
                       "Nie znaleziono podanego id: " + std::to_string(id));
      return false;
    }

    std::ofstream plik_wyjs(sciezka);
    if (!plik_wyjs.is_open()) {
      this->logger.log(LogLevel::Error, "Nie można otworzyć pliku " + sciezka);
      return false;
    }

    nlohmann::json updatedJson = parsed_data;

    plik_wyjs << updatedJson.dump(4);

    return true;
  };

  /**
   * @brief Struktura mapująca klucz JSON na getter klasy.
   *
   * @tparam T Typ klasy, do której należy getter.
   * @tparam ReturnType Typ zwracany przez getter.
   *
   *  @example
   * FieldMap<User, std::string> mapName{
   *     &User::getName,
   *     "name"
   * };
   */

  // INFO: funckja wiazaca klucze json z getterami w podanej klasie
  template <typename T, typename ReturnType> struct FieldMap {
    ReturnType (T::*getter)() const;
    std::string jsonKey;
  };

  /** @brief Sprawdza, czy w danych JSON istnieje wartość równa target
   *        dla któregokolwiek z podanych kluczy.
   *
   * @tparam T Typ klasy powiązanej z FieldMap
   * @tparam Value Typ wartości porównywanej z danymi w JSON.
   * @tparam Maps Typy mapowań FieldMap (variadic template).
   *
   * @param jsonData Obiekt JSON, w którym wykonywane jest wyszukiwanie.
   * @param target Wartość, której szukamy w JSON.
   * @param maps Lista mapowań (FieldMap), określających które klucze sprawdzać.
   *
   * @return true jeśli którakolwiek wartość w JSON odpowiada target, false w
   * przeciwnym przypadku.
   *
   * @example
   * nlohmann::json userJson = {
   *     {"id", 1},
   *     {"name", "Jan"},
   *     {"age", 25}
   * };
   *
   * FieldMap<User, std::string> nameMap{&User::getName, "name"};
   * FieldMap<User, int> ageMap{&User::getAge, "age"};
   *
   * bool exists = db.checkDataExist(
   *     userJson,
   *     std::string("Jan"),
   *     nameMap,
   *     ageMap
   * );
   *
   * // exists == true
   */

  // INFO: funckja sprawdzająca
  template <typename T, typename Value, typename... Maps>
  bool checkDataExist(const nlohmann::json &jsonData, const Value &target,
                      Maps... maps) {
    return (
        (jsonData.contains(maps.jsonKey) && jsonData[maps.jsonKey] == target) ||
        ...);
  }
};

#endif // !DATABASE_HPP
