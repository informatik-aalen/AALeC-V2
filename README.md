# AALeC - AAlener Lern-Computer

## Beschreibung

AALeC ist der Aalener Lerncomputer. Er basiert auf einem ESP8266, welcher als
Wemos-D1-Mini-Modul eingesetzt wird.

Sensoren:
* DHT11-Umweltsensor für Temperatur und Luftfeuchte
* Dreh- /  Drückgeber
* Analoges Potentiometer

Aktoren / Ausgabeelemente:
* Drei Fullcolor-Leuchtdioden PL9823 (WS2812B-kompatibel)
* OLED-Display
* Lautsprecher
* LED einfach

Externe Anschlüsse:
* I2C (4-Pin-Header)
* Analogeingang (3,5mm-Klinke)

Die Programmierung kann in allen Sprachen erfolgen, die für den ESP8266
verfügbar sind. Für Arduino-Programmierung in C / C++ steht diese Bibliothek zur
Verfügung, die die Programmierung stark vereinfacht.

## GPIO-Belegung

 0  Drehgeber Taster \
 1  TX \
 2  WS2812-Kette \
 3  RX \
 4  SDA \
 5  SCL \
12  Drehgeber Spur 0 \
13  Drehgeber Spur 1 \
14  DHT11 \
15  Lautsprecher \
16  LED / Reset

## Installation

Laden Sie unter [https://github.com/informatik-aalen/AALeC-V2/releases](https://github.com/informatik-aalen/AALeC-V2/releases)
die .ZIP Datei der aktuellen Version der Bibliothek herunter. Benutzen Sie den
Menüpunkt **.ZIP Bibliothek hinzufügen...** unter dem Menü **Sketch** -> 
**Bibliothek einbinden** in der Arduino IDE um die Bibliothek einzubinden.

## Abhängigkeiten

Diese Bibliothek hängt von den folgenden Bibliotheken ab:
* Adafruit_Neopixel
* SimpleDHT
* ESP8266 and ESP32 Oled Driver for SSD1306 display

Installieren Sie diese Bibliotheken bitte über den Bibliotheksverwalter in der Arduino IDE.

## Autoren

* **Winfried Bantel** - *Idee und Codierung*
* **Peter Kolb** - *Schaltplan, Layout, CAD, Mechanik*
* **Sebastian Stigler** - *Codierung*

## Lizenz

Das Projekt wird unter der MIT-Lizenz publiziert.

## Nachbau und Vertrieb

Nachbau ist explizit erwünscht. Fertigung und Vertrieb der Platine sind unter
Angabe der Hochschule Aalen erlaubt.

Informationen zur Hardware finden Sie unter [https://github.com/informatik-aalen/AALeC-Hardware](https://github.com/informatik-aalen/AALeC-Hardware).
