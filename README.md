# ZAMP

Symulator ruchu robota mobilnego napisany w C++. Program wczytuje konfigurację sceny z pliku XML oraz skrypt poleceń, a następnie animuje obiekt (np. postać humanoidalną) poprzez wykonywanie kolejnych instrukcji ruchu.

## Opis

Projekt oparty jest na architekturze wtyczkowej (plugin). Każde polecenie (np. `Move`, `Rotate`, `Set`, `Pause`) jest zaimplementowane jako osobna wtyczka (`*.so`) ładowana dynamicznie w czasie działania programu. Interpreter poleceń obsługuje zarówno akcje sekwencyjne, jak i równoległe (`Begin_Parallel_Actions` / `End_Parallel_Actions`).

### Obsługiwane polecenia

| Polecenie | Opis                                          |
| --------- | --------------------------------------------- |
| `Move`    | Przemieszcza obiekt o zadaną odległość        |
| `Rotate`  | Obraca obiekt wokół wybranej osi o zadany kąt |
| `Set`     | Ustawia pozycję i orientację obiektu          |
| `Pause`   | Wstrzymuje wykonanie na określony czas        |

## Struktura projektu

```
src/        - kod źródłowy programu głównego
inc/        - pliki nagłówkowe (interfejsy abstrakcyjne)
plugin/     - wtyczki implementujące poszczególne polecenia
config/     - pliki konfiguracyjne sceny (XML)
```

## Budowanie

```bash
mkdir build && cd build
cmake ..
make
```

## Uruchomienie

```bash
./program <plik_polecen> <plik_konfiguracji.xml>
```

Przykład:

```bash
./program opis_dzialan.txt config/config.xml
```
