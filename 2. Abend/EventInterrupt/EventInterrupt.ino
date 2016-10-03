/* 
 * Extra Schaltung: Interrupt mit Pulldown
*/
int helligkeit = 1;
int entprellen = 0;

void interruptFunction() 
{

  if(entprellen == 0)
  {
    helligkeit++;

    if(helligkeit > 3)  // ist die Helligkeit bereits auf Maximum (5) stezen wir die Helligkeit auf 0
      helligkeit = 0;
    entprellen = 3;
  }
}

// Die setup-Funktion wird einmalig nach "reset" oder power-up" ausgeführt 
void setup()
{   
  // Initialisiert den Pin 12 als Ausgang, der Asugang steuert die LED
  pinMode(12, OUTPUT); 
  // Initialisiert den Pin 2 als Ausgang, der den Status des Tasters überwacht  
  pinMode(2,INPUT);
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
  if(helligkeit > 0)      // Schaltet die LED nur ein, wenn die helligkeit > 0 ist
  {
     digitalWrite(12, HIGH); // Schaltet die LED ein (HIGH ist der Schaltzustand/Spannunglevel)  
  }  
  delay(helligkeit*1);      // Warte (delay) 1000ms = 1 Sekunde 
  digitalWrite(12, LOW);    // Schaltet die LED aus (LOW Schaltzustand/Spannungslevel)
  delay(20);                // Warte 20 Milli-Sekunde
  if(entprellen > 0)
  {
    entprellen = entprellen - 1;
  }
}
