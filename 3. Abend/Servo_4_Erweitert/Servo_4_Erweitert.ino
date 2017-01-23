/* 
 * Mit der Pulsweitenmodulation die Motoren steuern
*/

#include <Servo.h>

Servo servo;
int servoPin = 7;

// Die setup-Funktion wird einmalig nach "reset" oder power-up" ausgeführt 
void setup()
{   
    // Initialisierung der seriellen Schnittstelle (UART) mit einer BAUD-Rate von 9600(Bits pro Sekunde)  
    Serial1.begin(9600);
    // Ausgabe eines Begrüßungstextes
    Serial1.println("Hallo Welt");
  
    servo.attach(servoPin);
  
} 
// Die loop-Funktion wird ständig wiederholt durchlaufen
void loop()
{
  // Ausgangsposition anfahren (Wert von 0 bis 180 Grad)
    servo.write(0);
    delay(500);
  
    for (int stellung = 0 ; stellung <= 180; stellung += 10) {
      // Schreibt die Stellung in den PWM-Pin (Wert von 0 bis 180 Grad):
      servo.write(stellung);
      // Warten bis zur nächsten Änderung der Stellung
      delay(500);
      Serial1.println("Tick");
    }  

    for (int stellung = 180 ; stellung >= 0; stellung -= 10) {
      // Schreibt die Stellung in den PWM-Pin (Wert von 0 bis 180 Grad):
      servo.write(stellung);
      // Warten bis zur nächsten Änderung der Stellung
      delay(500);
      Serial1.println("Tick");
    }  
  
    delay(100); // warten bis zum nächsten Aufruf
}

