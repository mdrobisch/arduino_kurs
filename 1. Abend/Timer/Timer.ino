/* 
 * LED mit Timer
*/

void timer_funktion(void);  // die Timer-Funktion wird vom Timer-Modul aufgerufen, wenn der Schwellwert des Zählers erreicht ist, hier zunächst nur die Definition
int led_zustand = 0;    // der Zustand der LED, 0 = aus, 1 = an 

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
  Timer1.setPeriod(1000000); // Periodendauer in Millisekunden
  Timer1.setCompare1(1);
  Timer1.attachCompare1Interrupt(timer_funktion);
  Timer1.resume();
}

#endif

// Die setup-Funktion wird einmalig nach "reset" oder power-up" ausgeführt 
void setup()
{   
  // Initialisiert den Pin 2 als Ausgang, der Ausgang steuert die LED
  pinMode(2, OUTPUT); 

  // Konfiguration des Timers  
  // der Quellcode sieht in der Simulation anders aus, da wir das STM-Board verwenden
  init_timer1();
}

// Die loop-Funktion wird ständig wiederholt durchlaufen
void loop() 
{   
  // In diesem Beispiel kann die Schleifenfunktion leer bleiben, da alles in der Timer-Funktion abgearbeitet wird

}

void timer_funktion(void) 
{
  if(led_zustand == 0)
  {
    digitalWrite(2, HIGH);  // Schaltet die LED ein (HIGH ist der Schaltzustand/Spannunglevel)
    led_zustand = 1;
  }
  else
  {
    digitalWrite(2, LOW); // Schaltet die LED aus (LOW Schaltzustand/Spannungslevel)
    led_zustand = 0;
  }
}
