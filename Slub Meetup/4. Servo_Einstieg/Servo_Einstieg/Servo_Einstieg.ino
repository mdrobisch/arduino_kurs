/* 
 * Mit der Pulsweitenmodulation die Motoren steuern
*/

// Eindinden der Servo-Bibliothek
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

    servo.write(90);
    delay(500);

    servo.write(180);
    delay(500);

    servo.write(90);
    delay(500);
}

