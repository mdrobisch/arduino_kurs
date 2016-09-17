/* 
 * Die LED blinkt, wenn der Taster gedrückt ist 
*/

// Variable zur Speicherung des Pin Zustandes 
int buttonState = 0;         // variable for reading the pushbutton status 

// Die setup-Funktion wird einmalig nach "reset" oder power-up" ausgeführt 
void setup()
{   
  // Initialisiert den PB1-Pin als Ausgang, der Asugang steuert die LED
  pinMode(2, OUTPUT); 
  pinMode(12, INPUT); 

}

// Die loop-Funktion wird ständig wiederholt durchlaufen
void loop() 
{   
  // Auslesen des Zustandes des Schalters:   
  buttonState = digitalRead(12); 

  if (buttonState == HIGH) { 
    digitalWrite(2, HIGH);  // Schaltet die LED ein (HIGH ist der Schaltzustand/Spannunglevel)
    delay(500);         // Warte (delay) 1000ms = 1 Sekunde 
    digitalWrite(2, LOW);   // Schaltet die LED aus (LOW Schaltzustand/Spannungslevel)
    delay(500);               // Warte 1 Sekunde
  } else {
    digitalWrite(2, LOW);   // Schaltet die LED aus (LOW Schaltzustand/Spannungslevel)
  }
}
