/* 
 * Extra Schaltung: Interrupt mit Pulldown
*/
int bLED = HIGH;

void interruptFunction() 
{
  bLED = !bLED;
}

// Die setup-Funktion wird einmalig nach "reset" oder power-up" ausgeführt 
void setup()
{   
  // Initialisiert den Pin 12 als Ausgang, der Asugang steuert die LED
  pinMode(12, OUTPUT); 
  // Initialisiert den Pin 2 als Ausgang, der den Status des Tasters überwacht  
  pinMode(2,INPUT_PULLUP);
  // Zum Verknüpfen der Interrupts wird die attachInterrupt Funktion verwendet
  // Dabei ist der erste Parameter die Interrupt-Nummer
  // Für STM32Duino gilt: Die Interrupt-Nummer ist gleich der Pinnummer
  // Der Parameter "RISING" bezieht sich auf die Art des Interrupts. 
  // Mit RISING oder FALLING wird die Änderung des Signals von LOW<->HIGH Pegel angegeben
  // Mit CHANGE wird auf beide Ereignisse ein Interrupt ausgelösst.
  attachInterrupt(2, interruptFunction, RISING);
}

// Die loop-Funktion wird ständig wiederholt durchlaufen
void loop() 
{   
  digitalWrite(12, bLED);   // Schaltet die LED aus (LOW Schaltzustand/Spannungslevel)
}
