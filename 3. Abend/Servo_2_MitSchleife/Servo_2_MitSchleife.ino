/* 
 * Mit der Pulsweitenmodulation die Motoren steuern
*/

#include <Servo.h>

Servo servo;
int servoPin = 7;

// Die setup-Funktion wird einmalig nach "reset" oder power-up" ausgeführt 
void setup()
{   
    // Initialisierung des Servo-Pin über die Servo-Bibliothek
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

    servo.write(0);
    delay(1000); // warten bis zum nächsten Durchlauf der Loop-Schleife
}

