#include <SPI.h>

// Definition des Chip-Select-Pins zur Kommunikation über dei SPI-Schnittstelle des MAX7219/MAX7221
// Wir verwenden Pin 10
#define CS_PIN    10

// Variable zum setzen der Helligkeit
int helligkeit = 0;

void maxTransfer(uint8_t address, uint8_t value) {

  // Mit dem MAX7219 wird über die SPI-Schnittstelle komuniziert
  // Den Verlauf der Kommunikation ist im Datenblatt (siehe Ordner) Abbildung 1 dargestellt
  // Die Einstellungen werden im LED-Treiber in Registern gespeichert
  // Es müssen jeweils 2 Bytes übertragen werden um diese zu ändern
  // Ein Adressbyte und ein Datenbyte (siehe Tabelle 1 im Datenblatt)

  // Der CS-Pin von HIGH zu LOW signalisiert den Start der Übertragung
  digitalWrite(CS_PIN, LOW);
  
  // Senden des 1. Bytes. Die Adresse des Registers 
  SPI.transfer(address);

  // Senden des 2. Bytes. Der Wert, der in das Register geschrieben werden soll
  SPI.transfer(value);

  // Der CS-PIN von LOW zu HIGH signalisiert das Ende des Schreibvorgangs
  digitalWrite(CS_PIN, HIGH);
}

void setup() {
  
  // den CS-PIN (Chip-Select benötigen wir zum Start/Stop der Kommunikation)
  pinMode(CS_PIN, OUTPUT);

  // Initialisieren der SPI-Schnittstelle (Standardeinstellungen)
  SPI.begin();  
  
  // Setzen der Dekodierung auf Matrix-Ansteuerung 
  maxTransfer(0x09, 0x00);  
  // Setzen der Leuchtintensität
  maxTransfer(0x0A, 0x00);
  // Setzen der Zeilen (8 Zeilen)
  maxTransfer(0x0B, 0x07);
  // Aktivierung der Anzeige
  maxTransfer(0x0C, 0x01);
   
}

void loop() {

  // Wir verwenden die binäre Zahlendarstellung in C
  // ein Byte enstspricht einer Zeile
  // jedes Bit stellt eine LED einer Zeile dar (0 = AUS, 1 = AN)
  // wir müssen für jede Zeile (1-8) die LED einschalten
  // dafür benutzen wir die maxTransfer-Funktion mit den Parametern Adresse des Registers und Wert
  // ein Register kann als beschreibbare Variable gesehen werden
  // die Details zu den Registern finden sich im Datenblatt im Ordner "Datenblaetter"  
  maxTransfer(0x01, 0b00000000);
  maxTransfer(0x02, 0b01101100);
  maxTransfer(0x03, 0b10010010);
  maxTransfer(0x04, 0b10000010);
  maxTransfer(0x05, 0b01000100);
  maxTransfer(0x06, 0b00101000);
  maxTransfer(0x07, 0b00010000);
  maxTransfer(0x08, 0b00000000);

  // Zusätzlich können wir die Helligkeit einstellen
  maxTransfer(0x0A, helligkeit);

  // warten
  delay(1500);
 
}
