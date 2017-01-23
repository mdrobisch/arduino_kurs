/* 
 * Hallo Welt
*/

// Die setup-Funktion wird einmalig nach "reset" oder power-up" ausgeführt 
void setup()
{   
  // Init .....
  Serial1.begin(9600); 
  delay(500); // Kurz warten damit die Verbindung aufgebaut ist
  Serial1.println("Hallo Welt!");
}

// Die loop-Funktion wird ständig wiederholt durchlaufen
void loop() 
{   

  Serial1.println("Taste gedrueckt");
  delay(200); // warten zum entprellen
}
