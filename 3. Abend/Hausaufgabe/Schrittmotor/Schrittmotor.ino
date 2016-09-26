/* 
 * Lauflicht mit Timer
*/

// Funktionen bekannt machen
void timer_funktion(void);  // die Timer-Funktion wird vom Timer-Modul aufgerufen, wenn der Schwellwert des Zählers erreicht ist, hier zunächst nur die Definition
void led_setzen(int led);   // setzt die entsprechende LED und schaltet alle anderen aus

// Variablendefinitionen
int timerEreignis = 0;      // zeigt an das ein Timer Ereignis bearbeitet werden muss, 0 = kein Ereignis, 1 = Ereignis aufgetreten
int schrittstellung = 0;         // speichert die aktuell aktive LED mit ihrer Pin-Nummer


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
  Timer1.setPeriod(50000); // Periodendauer in Mikrosekunden
  Timer1.setCompare1(5);
  Timer1.attachCompare1Interrupt(timer_funktion);
  Timer1.resume();
}

#endif

// Die setup-Funktion wird einmalig nach "reset" oder power-up" ausgeführt 
void setup()
{   
  // Initialisiert der LED Pins als Ausgang
  pinMode(8, OUTPUT); 
  pinMode(9, OUTPUT); 
  pinMode(10, OUTPUT); 
  pinMode(11, OUTPUT); 

  // Konfiguration des Timers  
  // der Quellcode sieht in der Simulation anders aus, da wir das STM-Board verwenden
  init_timer1();
}

void schrittstellung_setzen(int stellung)
{
  // schrittstellungen siehe http://www.elektronx.de/wp-content/uploads/2013/11/Stepper_sequence.jpg
  switch(stellung)
  {
    case 0:
      digitalWrite(11, LOW);  // 1001
      digitalWrite(8, HIGH);  // 1000
      break;
    case 1:
      digitalWrite(9, HIGH);  // 1100
      break;
    case 2:
      digitalWrite(8, LOW);   // 1100
      break;
    case 3:
      digitalWrite(10, HIGH); // 0110
      break;
    case 4:
      digitalWrite(9, LOW);   // 0010
      break;
    case 5:
      digitalWrite(11, HIGH); // 0011
      break;
    case 6:
      digitalWrite(10, LOW);  // 0001
      break;
    case 7:
      digitalWrite(8, HIGH);   // 1001
      break;

  }    
}

// Die loop-Funktion wird ständig wiederholt durchlaufen
void loop() 
{   
  if(timerEreignis == 1)
  {
    schrittstellung_setzen(schrittstellung);
    schrittstellung++;
    if(schrittstellung > 7)
      schrittstellung = 0;
    timerEreignis = 0;
  }
}

void timer_funktion(void) 
{
  timerEreignis = 1;
}
