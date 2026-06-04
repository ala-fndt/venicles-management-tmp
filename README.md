# Vehicle Management System

### Aplikacja desktopowa C++ (wxWidgets) do zarządzania flotą pojazdów, zbudowana w architekturze MVC.

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

## Przygotowanie środowiska

 - Linux: ```sudo pacman -Syu base-devel wxwidgets-gtk3 bear```
 - Windows (MSYS): ```pacman -Syu mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-wxwidgets3.2-msw```

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

## Problemy LSP/Błędy w edytorze

### Generacja pliku konfiguracji dla serwera jezykowego:

- Linux: `bear -- make`
- WIndows: `pip install compiledb && compiledb make` (pamietajcie o dodaniu compiledb do zmiennych środowiskowych)

