# 🚗 Vehicle Management System

> Desktopowa aplikacja do zarządzania flotą pojazdów, napisana w C++ z użyciem wxWidgets i SQLite, zbudowana w architekturze MVC.

---

## O projekcie

Vehicle Management System to aplikacja desktopowa przeznaczona do zarządzania flotą różnorodnych pojazdów — samochodów osobowych, motocykli oraz ciężarówek. System oferuje wieloużytkownikowe środowisko z podziałem ról (użytkownik / administrator), persystencję danych w lokalnej bazie SQLite oraz przejrzysty interfejs graficzny.

Projekt realizuje pełny cykl zarządzania pojazdem: od rejestracji w systemie, przez śledzenie stanu technicznego i przebiegu, aż po przypisywanie pojazdów do konkretnych użytkowników.

---

## Funkcjonalności

### 🔐 Uwierzytelnianie i sesja
- Rejestracja nowego konta (imię, nazwisko, e-mail, hasło)
- Logowanie z walidacją danych wejściowych
- Sesja użytkownika oparta na singletonie (`Session`)
- Wylogowanie z powrotem do ekranu logowania

### 🏠 Strona główna
- Przeglądanie floty pojazdów w formie karuzeli (`VehicleCarouselWidget`)
- Szybki podgląd marki, modelu, roku i koloru każdego pojazdu
- Nawigacja do profilu użytkownika
- Przycisk wylogowania

### 👤 Profil użytkownika
- Wyświetlanie danych konta (imię, nazwisko, e-mail)
- Widok przypisanych pojazdów
- Możliwość edycji danych

### 🚘 Zarządzanie pojazdami
Każdy pojazd przechowuje następujące dane:

| Pole | Opis |
|---|---|
| Marka | np. Toyota, BMW |
| Model | konkretna wersja |
| Rok produkcji | rocznik pojazdu |
| Kolor | kolor nadwozia |
| Numer rejestracyjny | tablica |
| VIN | unikalny numer identyfikacyjny |
| Rodzaj paliwa | benzyna, diesel, elektryczny… |
| Stan techniczny | aktualny status pojazdu |
| Przebieg | w kilometrach |

Obsługiwane typy pojazdów:
- **Samochód osobowy** (`PersonalVehicle`)
- **Motocykl** (`Motorcycle`)
- **Ciężarówka** (`Truck`)

<details>
<summary>📸 Zrzuty ekranu — lista pojazdów</summary>

> *(dodaj zrzuty ekranu)*

</details>

### 🗄️ Baza danych
- Lokalna baza SQLite inicjalizowana przy starcie aplikacji
- Alternatywny zapis danych w formacie JSON (`DatabaseJson`)
- Logowanie zdarzeń systemowych przez klasę `Logger`

---

## Architektura

Projekt stosuje wzorzec **MVC (Model–View–Controller)**:

```
src/
├── classes/        — encje domenowe (Vehicle, User, Session, Router…)
├── model/          — logika dostępu do danych
├── view/           — komponenty UI (wxWidgets)
├── controller/     — obsługa zdarzeń i nawigacja
├── database/       — warstwa bazy danych (SQLite + JSON)
└── additionalScripts/ — narzędzia pomocnicze (Logger, Validator)
```

Nawigacja między widokami odbywa się przez klasę `Router`, a stan zalogowanego użytkownika jest przechowywany w singletonie `Session`.

---

## Planowane funkcjonalności

- [ ] Miejsce i godzina dowozu / odbioru pojazdu
- [ ] Lista zadań (to-do) dla dostawców z pojazdami
- [ ] Oznaczanie pojazdu jako dostarczony
- [ ] Panel koordynatora — przydzielanie przejazdów pracownikom

---

## Instalacja i uruchomienie

Instrukcja przygotowania środowiska oraz kompilacji projektu dostępna jest w pliku [SETUP.md](other/SETUP.md).

---

## Technologie

- **C++20**
- **wxWidgets** — GUI
- **SQLite3** — baza danych
- **nlohmann/json** — obsługa JSON
- **Make** — system budowania
