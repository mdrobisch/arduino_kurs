/* 
 * Mit der Pulsweitenmodulation die Motoren steuern
*/

#include <Servo.h>

Servo servo;
int servoPin = 7;

// Variablen, welche die ADC-Werte speichern 
int sensorWertX = 0;        // ausgelesener Wert des Potentiometer X 
int ausgabeWertX = 0;        // berechneter Ausgabewert X

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
  
  
    /*
   * Das auslesen des Joysticks wird zunächst auskommentiert
    
  // Auslesen der Spannung am A0-Pin für X 
    sensorWertX = analogRead(A0);
    // Zuweisung/Aufspreizung des analogen Wertes von 0 .. 1023 auf einem Wert von 0 .. 65535
    ausgabeWertX = map(sensorWertX, 0, 1023, 0, 65535);  
    // Ausgabe des Rohwertes und des berechneten/transformierten Wertes über die serielle Schnittstelle
    Serial.print("Rohwert= " );
    Serial.print(sensorWertX);
    Serial.print(" Ausgabe= ");
    Serial.println(ausgabeWertX);

  */
    delay(100); // warten bis zum nächsten Aufruf
  
  
}

