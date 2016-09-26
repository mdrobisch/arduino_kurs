/* 
 * Lauflicht mit Timer
*/

// Funktionen bekannt machen
void timer_funktion(void);  // die Timer-Funktion wird vom Timer-Modul aufgerufen, wenn der Schwellwert des Zählers erreicht ist, hier zunächst nur die Definition
void led_setzen(int led);   // setzt die entsprechende LED und schaltet alle anderen aus

// Variablendefinitionen
int timerEreignis = 0;      // zeigt an das ein Timer Ereignis bearbeitet werden muss, 0 = kein Ereignis, 1 = Ereignis aufgetreten
int aktiveLed = 9;         // speichert die aktuell aktive LED mit ihrer Pin-Nummer


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
  // Initialisiert der LED Pins als Ausgang
  pinMode(9, OUTPUT); 
  pinMode(10, OUTPUT); 
  pinMode(11, OUTPUT); 
  pinMode(12, OUTPUT); 

  // Konfiguration des Timers  
  // der Quellcode sieht in der Simulation anders aus, da wir das STM-Board verwenden
  init_timer1();

  led_setzen(aktiveLed);
}

void led_setzen(int led)
{
  // schalte die aktive LED an, wenn aktiviert
  // schalte alle Anderen aus
  if(led == 9)
    digitalWrite(9, HIGH);  // Schaltet die LED ein (HIGH ist der Schaltzustand/Spannunglevel)
  else
    digitalWrite(9, LOW); // Schaltet die LED aus (LOW Schaltzustand/Spannungslevel)

  if(led == 10)
    digitalWrite(10, HIGH);  // Schaltet die LED ein (HIGH ist der Schaltzustand/Spannunglevel)
  else
    digitalWrite(10, LOW); // Schaltet die LED aus (LOW Schaltzustand/Spannungslevel)

  if(led == 11)
    digitalWrite(11, HIGH);  // Schaltet die LED ein (HIGH ist der Schaltzustand/Spannunglevel)
  else
    digitalWrite(11, LOW); // Schaltet die LED aus (LOW Schaltzustand/Spannungslevel)

  if(led == 12)
    digitalWrite(12, HIGH);  // Schaltet die LED ein (HIGH ist der Schaltzustand/Spannunglevel)
  else
    digitalWrite(12, LOW); // Schaltet die LED aus (LOW Schaltzustand/Spannungslevel)
    
}

// Die loop-Funktion wird ständig wiederholt durchlaufen
void loop() 
{   
  if(timerEreignis == 1)
  {
    led_setzen(aktiveLed);
    aktiveLed++;
    if(aktiveLed > 12)
      aktiveLed = 9;
    timerEreignis = 0;
  }
}

void timer_funktion(void) 
{
  timerEreignis = 1;
}
