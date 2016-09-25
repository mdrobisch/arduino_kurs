/* 
 * Mit dem ADC Spannungen messen
*/

// buttonEvent zeigt ein zu bearbeitendes Taster-Ereignis (zu bearbeitenden Interrupt) an
int buttonEvent = 0;

// Variablen, welche die ADC-Werte speichern 
int sensorWertX = 0;        // ausgelesener Wert des Potentiometer X 
int ausgabeWertX = 0;        // berechneter Ausgabewert X

void tastenDruck() {
    // Setzen des Taster-Ereignisses
  buttonEvent = 1;
    // in Interrupt-Funktionen sollten keine längeren oder rechenintensiven Befehle ausgeführt werden
    // deshalb wird die Serial.println hier nicht direkt aufgerufen.
}

// Die setup-Funktion wird einmalig nach "reset" oder power-up" ausgeführt 
void setup()
{   
    // Initialisiere den Pin 2 als Eingang, der den Taster überwacht
  // Mithilfe der INPUT_PULLUP wird der interne Pullup-Widerstand (ca. 10kOhm) aktiviert, damit wird ein externer Widerstand eingespart
    pinMode(2, INPUT_PULLUP); 
    // Zum Verknüpfen der Interrupts wird die attachInterrupt Funktion verwendet
    // Dabei ist der erste Parameter die Interrupt-Nummer
    // Für Arduino UNO gilt: Pin 2 => Intterupt 0, Pin 3 => Interrupt 1
    // Für andere Boards sind andere Pin-Interrupt-Zuweisungen vorhanden
    // Siehe hierfür: https://www.arduino.cc/en/Reference/AttachInterrupt 
    // Der Parameter "FALLING" bezieht sich auf die fallende Flanke. Durch den Pullup ist diese invertiert
    attachInterrupt(0, tastenDruck, FALLING); 

    // Initialisierung des ADC Pins
    // diese kann für die Pins A0 ... A5 weggelassen werden
    // die STM32Duino Board verfügen aber meist über deutlich mehr ADC-Eingänge
    // für andere ADC-Pins wird der pinMode auf INPUT_ANALOG gesetzt
    // pinMode(A0, INPUT_ANALOG); // set up pin for analog input


  
    // Initialisierung der seriellen Schnittstelle (UART) mit einer BAUD-Rate von 9600(Bits pro Sekunde)  
    Serial1.begin(115200);
    // Ausgabe eines Begrüßungstextes
    delay(500);
    Serial1.println("Hallo Welt");
  
    // Initialisierung des A0-Analog-Eingang
  // Muss nur für den STM32 ausgeführt werden, deshalb hier auskommentiert
    // pinMode(A0, INPUT_ANALOG); 
} 
// Die loop-Funktion wird ständig wiederholt durchlaufen
void loop()
{
    // Auf das Taster-Event reagieren, falls dieses gesetzt wurde
    if(buttonEvent == 1)
    {
      Serial1.println("Push the button!");
      delay(100); // warte 100 millisekunden bis das Ereignis erneut ausgelöst werden kann
        buttonEvent = 0;
    }
  
    // Auslesen der Spannung am A0-Pin für X 
    sensorWertX = analogRead(A0);
    // Zuweisung/Aufspreizung des analogen Wertes von 0 .. 1023 auf einem Wert von 0 .. 65535
    ausgabeWertX = map(sensorWertX, 0, 4095, 0, 1000);  
    // Ausgabe des Rohwertes und des berechneten/transformierten Wertes über die serielle Schnittstelle
    Serial1.print("Rohwert= " );
    Serial1.print(sensorWertX);
    Serial1.print(" Ausgabe= ");
    Serial1.println(ausgabeWertX);

    delay(100); // warten bis zum nächsten Aufruf
  
  
}

