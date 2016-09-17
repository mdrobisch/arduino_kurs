/* 
 * Unser erstes Arduino Programm, die blinkende LED. 
*/

// Die setup-Funktion wird einmalig nach "reset" oder power-up" ausgeführt 
void setup()
{   
  // Initialisiert den Pin 2 als Ausgang, der Asugang steuert die LED
  pinMode(2, OUTPUT); 
}

// Die loop-Funktion wird ständig wiederholt durchlaufen
void loop() 
{   
  digitalWrite(2, HIGH);  // Schaltet die LED ein (HIGH ist der Schaltzustand/Spannunglevel)
  delay(1000);          // Warte (delay) 1000ms = 1 Sekunde 
  digitalWrite(2, LOW);   // Schaltet die LED aus (LOW Schaltzustand/Spannungslevel)
  delay(1000);               // Warte 1 Sekunde
}
