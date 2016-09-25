/* 
 * Extra Schaltung: Interrupt mit Pulldown
*/
int tasterEreigniss = 0;

void interruptFunction() 
{
  tasterEreigniss = 1;
}

// Die setup-Funktion wird einmalig nach "reset" oder power-up" ausgeführt 
void setup()
{   
  // Initialisiert den Pin 2 als Ausgang, der den Status des Tasters überwacht  
  pinMode(2,INPUT_PULLUP);
  // Zum Verknüpfen der Interrupts wird die attachInterrupt Funktion verwendet
  // Dabei ist der erste Parameter die Interrupt-Nummer
  // Für STM32Duino gilt: Die Interrupt-Nummer ist gleich der Pinnummer
  // Der Parameter "RISING" bezieht sich auf die Art des Interrupts. 
  // Mit RISING oder FALLING wird die Änderung des Signals von LOW<->HIGH Pegel angegeben
  // Mit CHANGE wird auf beide Ereignisse ein Interrupt ausgelösst.
  attachInterrupt(2, interruptFunction, RISING);

  // Init .....
  Serial1.begin(115200); 
  delay(500); // Kurz warten damit die IDE die Verbindung aufbauen kann
  Serial1.println("Hallo Welt!");
}

// Die loop-Funktion wird ständig wiederholt durchlaufen
void loop() 
{   
  if(tasterEreigniss == 1)
  {
    Serial1.println("Taste gedrueckt");
    delay(200); // warten zum entprellen
    tasterEreigniss = 0;
  }
}
