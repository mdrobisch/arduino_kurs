/* 
 * Die LED blinkt mit der eingestellten Helligkeit 
*/

// Variable zur Speicherung des Pin Zustandes 
int buttonState = 0;         // Variable zum auslesen des Taster-Zustands
int buttonOldState = 0;
int helligkeit = 1;

// Die setup-Funktion wird einmalig nach "reset" oder power-up" ausgeführt 
void setup()
{   
  // Initialisiert den Pin 12 als Ausgang, der Ausgang steuert die LED
  pinMode(12, OUTPUT); 
    // Initialisiere den Pin 2 als Eingang, der den Zustand des Tasters überwacht
  pinMode(2, INPUT); 

}

// Die loop-Funktion wird ständig wiederholt durchlaufen
void loop() 
{   
  // Auslesen des Zustandes des Tasters in jedem Zyklus wird Polling genannt
  buttonState = digitalRead(2); 
  
  if(helligkeit > 0)      // Schaltet die LED nur ein, wenn die helligkeit > 0 ist
    digitalWrite(12, HIGH); // Schaltet die LED ein (HIGH ist der Schaltzustand/Spannunglevel)  
  
  delay(helligkeit*1);      // 
  digitalWrite(12, LOW);    // Schaltet die LED aus (LOW Schaltzustand/Spannungslevel)
  delay(20);                // Warte  1 Milisekunde

  if(buttonOldState == LOW)   // ein verändern der Helligkeit ist nur gewünscht, wenn der Zustand des Tasters vorher LOW war
  {
    if (buttonState == HIGH) { // wenn der Taster gedrückt wird erhöhen wir anschließend die Helligkeit

        helligkeit++;

        if(helligkeit > 3)  // ist die Helligkeit bereits auf Maximum (5) stezen wir die Helligkeit auf 0
          helligkeit = 0;
    }
  }
  buttonOldState = buttonState; // der "alte" Zustand ist nun der neue Zustand
}
