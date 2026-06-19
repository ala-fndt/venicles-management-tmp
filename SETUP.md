# Vehicle Management System

### Aplikacja desktopowa C++ (wxWidgets) do zarządzania flotą pojazdów, zbudowana w architekturze MVC.

<br>

## Struktura projektu
```bash
root
├───include
│   ├───additionalScripts
│   ├───classes
│   ├───controller
│   ├───database
│   ├───model
│   ├───nlohmann
│   └───view
└───src
    ├───additionalScripts
    ├───classes
    ├───controller
    ├───database
    ├───model
    └───view
```

 - `src/` & `include/` – Kod źródłowy i nagłówki podzielone na model, view oraz controller.
 - `database/` – Logika zapisu i obsługi danych.
 - `nlohmann/` – Biblioteka do obsługi plików JSON. 
<br>

## Przygotowanie środowiska

#### Linux (Arch, Manjaro) with ```pacman```
 ```bash
 sudo pacman -Syu base-devel wxwidgets-gtk3 bear sqlite3
```
<br>

#### Linux (Ubuntu, Debian) with ```apt```
```bash 
sudo apt install -y build-essential libwxgtk3.2-dev bear sqlite3
```
<br>

#### Windows (MSYS2 UCRT)
```bash
pacman -Syu mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-wxwidgets3.2-msw mingw-w64-ucrt-x86_64-sqlite3
```
<br>

## Kompilacja i uruchomienie

### Korzystamy z pliku Makefile:
[makefile](Makefile)

### Kompilacja

```bash 
make main
```

### Uruchomienie

- Linux: `./main` 
- Windows (MSYS): `./main` lub `./main.exe`

<br>

## Problemy LSP/Błędy w edytorze

### Generacja pliku konfiguracji dla serwera jezykowego:

- Linux: `bear -- make`
- Windows: `pip install compiledb && compiledb make` (pamietajcie o dodaniu compiledb do zmiennych środowiskowych)

