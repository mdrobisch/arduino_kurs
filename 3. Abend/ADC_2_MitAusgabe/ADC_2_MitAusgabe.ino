/* 
 * Mit dem ADC Spannungen messen
*/

// buttonEvent zeigt ein zu bearbeitendes Taster-Ereignis (zu bearbeitenden Interrupt) an
int buttonEvent = 0;

// Variablen, welche die ADC-Werte speichern 
int sensorWertX = 0;        // ausgelesener Wert des Potentiometer X 
int ausgabeWertX = 0;        // berechneter Ausgabewert X

// Die setup-Funktion wird einmalig nach "reset" oder power-up" ausgeführt 
void setup()
{   
  
    // Initialisierung der seriellen Schnittstelle (UART) mit einer BAUD-Rate von 9600(Bits pro Sekunde)  
    Serial1.begin(9600);
    // Ausgabe eines Begrüßungstextes
    delay(500);
    Serial1.println("Hallo Welt");
  
    // Initialisierung des A0-Analog-Eingang
    // Muss nur für den STM32 ausgeführt werden, deshalb hier auskommentiert
    pinMode(A0, INPUT_ANALOG); 
} 
// Die loop-Funktion wird ständig wiederholt durchlaufen
void loop()
{
  
    // Auslesen der Spannung am A0-Pin für X 
    sensorWertX = analogRead(A0);
    // Zuweisung/Aufspreizung des analogen Wertes von 0 .. 4095 auf einem Wert von 0 .. 65535
    ausgabeWertX = map(sensorWertX, 0, 4095, 0, 1000);  
    // Ausgabe des Rohwertes und des berechneten/transformierten Wertes über die serielle Schnittstelle
    Serial1.print("Rohwert= " );
    Serial1.print(sensorWertX);
    Serial1.print(" Ausgabe= ");
    Serial1.println(ausgabeWertX);

    delay(100); // warten bis zum nächsten Aufruf
  
  
}

