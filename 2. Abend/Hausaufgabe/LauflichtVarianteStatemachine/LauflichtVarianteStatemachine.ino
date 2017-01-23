/* 
 * Lauflicht mit Timer
 * Variante mit Statemachine
*/

// Funktionen bekannt machen
void timer_funktion(void);  // die Timer-Funktion wird vom Timer-Modul aufgerufen, wenn der Schwellwert des Zählers erreicht ist, hier zunächst nur die Definition

// #define können als Standhalter verwendet werden, ZUSTAND_... werden während des Kompilierens mit den Werten dahinter ersetzt
// So können Zustände sehr einfach mit entsprechenden Namen verwendet werden.
// #define sollten nur mit Großbuchstaben geschrieben werden
// die IDs der Zustände sind willkührlich, sie sollten jedoch eindeutig sein
// als praktisch hat sich erwiesen Zwischenräume zu lassen, diese können später mit neuen Zuständen belegt werden 
#define ZUSTAND_START   0
#define ZUSTAND_LED1   10
#define ZUSTAND_LED2   20
#define ZUSTAND_LED3   30
#define ZUSTAND_LED4   40

// Variablendefinitionen
int timerEreignis = 0;      // zeigt an das ein Timer Ereignis bearbeitet werden muss, 0 = kein Ereignis, 1 = Ereignis aufgetreten
int ledZustand = ZUSTAND_LED1;         // speichert den aktuell Zustand des Zustandsautomaten


// hier müssen wir das entsprechende Board auswählen
// das entsprechende Board wir mit einem #define Aufruf definiert
// das andere Board muss auskommentiert werden, hier kompilieren wir für den STM32Duino

//#define ARDUINO_UNO
#define STM32DUINO

// Wenn für den Arduino Uno kompiliert werden soll, sieht die Timer-Funktion wie folgt aus
// Für den Arduino Uno benötigen wir zusätzlich die Interrupt-Funktion ISR(...)
#ifdef ARDUINO_UNO

ISR(TIMER1_COMPA_vect) {
  // hier wird der Interrupt ausgeführt, wir rufen hier unsere timer_funktion auf
  // dies regelt bei unserem Code die Timer-Bibliotek
  timer_funktion();
}

void init_timer1()
{
  cli(); // disable interrupts
  
  TCCR1A = 0; // set TCCR1A register to 0
  TCCR1B = 0; // set TCCR1B register to 0
  TCNT1  = 0; // set counter value to 0
  
  OCR1A = 3000; // set compare match register
  
  TCCR1B |= (1 << CS12) | (1 << CS10); // Set CS12 and CS10 bits for 1:1024 prescaler

  TCCR1B |= (1 << WGM12); // turn on CTC mode
  TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
  
  sei(); // allow interrupts
}

#endif

// Wenn für den STM32Duino kompiliert werden soll, sieht die Timer-Funktion wie folgt aus
#ifdef STM32DUINO

void init_timer1()
{
  Timer1.setChannel1Mode(TIMER_OUTPUTCOMPARE);
  Timer1.setPeriod(1000000); // Periodendauer in Mikrosekunden
  Timer1.setCompare1(1);
  Timer1.attachCompare1Interrupt(timer_funktion);
  Timer1.resume();
}

#endif

// Die setup-Funktion wird einmalig nach "reset" oder power-up" ausgeführt 
void setup()
{   
  // Initialisiert den Pin 9,10,11,12 als Ausgang, die Ausgänge steuern die LEDs
  pinMode(9, OUTPUT); 
  pinMode(10, OUTPUT); 
  pinMode(11, OUTPUT); 
  pinMode(12, OUTPUT); 

  // Konfiguration des Timers  
  // der Quellcode sieht in der Simulation anders aus, da wir das STM-Board verwenden
  init_timer1();

}

// Die loop-Funktion wird ständig wiederholt durchlaufen
void loop() 
{ 

  // Es können mehrere Zustandautomaten für unterschiedliche Aufgaben hintereinander bearbeitet werden
  // hier wird ein kontinuierlicher Zustandsautomat und ein eeventgesteuerter Zustandsautomat realisiert

  
  // Der kontinuierliche Zustandsautomat wird ständig durchlaufen (in jedem Durchlauf / loop)
  switch(ledZustand)
  {
      case ZUSTAND_START:
          // schalte alle LEDs aus
          digitalWrite(9, LOW);  // Schaltet die LED aus (LOW Schaltzustand/Spannungslevel)
          digitalWrite(10, LOW);  // Schaltet die LED aus (LOW Schaltzustand/Spannungslevel)
          digitalWrite(11, LOW);  // Schaltet die LED aus (LOW Schaltzustand/Spannungslevel)
          digitalWrite(12, LOW);  // Schaltet die LED aus (LOW Schaltzustand/Spannungslevel)
          break;
      default:
          // alle anderen Zustände werden Ereignissgetsuert behandelt
          break;
  }
  
  // ... oder Ereignisgestuert angestoßen werden
  // d.h. nur einmal falls das Ereignis autritt
  if(timerEreignis == 1)
  {
    // switch führt jeweils einen Zustand (case) des ledZustandes aus
    switch(ledZustand)
    {
      case ZUSTAND_LED1:
        digitalWrite(9, HIGH);
        digitalWrite(11, HIGH);  
        digitalWrite(10, HIGH);  
        digitalWrite(12, LOW); 
        ledZustand = ZUSTAND_LED2; // der neue Zustand ist nun ZUSTAND_LED2
        break;
      case ZUSTAND_LED2:
        digitalWrite(9, LOW);  
        digitalWrite(10, HIGH);  
        ledZustand = ZUSTAND_LED3; // der neue Zustand ist nun ZUSTAND_LED3
        break;        
      case ZUSTAND_LED3:
        digitalWrite(10, LOW);  
        digitalWrite(11, HIGH);  
        ledZustand = ZUSTAND_LED4; // der neue Zustand ist nun ZUSTAND_LED4
        break;        
      case ZUSTAND_LED4:
        digitalWrite(11, LOW);  
        digitalWrite(12, HIGH);
        ledZustand = ZUSTAND_LED1; // der neue Zustand ist nun ZUSTAND_LED1
        break;        
      default: // Was machen wir für alle anderen Zustände (default)?
        // Fehlerabfang
        ledZustand = ZUSTAND_LED1;
        break;        
    }
    // zurücksetzen des Ereignisses
    // WICHTIG: dies darf erst nach der Bearbeitung des Ereignisses geschehen
    timerEreignis = 0;

  }
}


void timer_funktion(void) 
{
  // wird wollen so kur wie möglich in den timer (interrupt)-Funktionen bleiben
  // deshalb setzen wir nur das Event
  timerEreignis = 1;
}
