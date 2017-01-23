/* 
 * Mit dem ADC Spannungen messen
*/

// Variablen, welche die ADC-Werte speichern 
int sensorWertX = 0;        // ausgelesener Wert des Potentiometer X 

// Die setup-Funktion wird einmalig nach "reset" oder power-up" ausgeführt 
void setup()
{   
    // Initialisierung des A0-Analog-Eingang
    // Muss nur für den STM32 ausgeführt werden, deshalb hier auskommentiert
    pinMode(A0, INPUT_ANALOG); 
} 
// Die loop-Funktion wird ständig wiederholt durchlaufen
void loop()
{
    // Auslesen der Spannung am A0-Pin für X 
    sensorWertX = analogRead(A0);

    // Ausgabe des Rohwertes und des berechneten/transformierten Wertes über die serielle Schnittstelle
    delay(100); // warten bis zum nächsten Aufruf

}

