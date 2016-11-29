/* 
 * LED mit Timer
*/

void timer_funktion(void);  // die Timer-Funktion wird vom Timer-Modul aufgerufen, wenn der Schwellwert des Zählers erreicht ist, hier zunächst nur die Definition
int led_zustand = 0;    // der Zustand der LED, 0 = aus, 1 = an 

ISR(TIMER1_COMPA_vect) {
  // hier wird der Interrupt ausgeführt, wir rufen hier unsere timer_funktion auf
  // dies regelt bei unserem Code die Timer-Bibliotek
  timer_funktion();
}

void init_timer1(unsigned long frequency)
{
  cli(); // disable interrupts
  
  TCCR1A = 0; // set TCCR1A register to 0
  TCCR1B = 0; // set TCCR1B register to 0
  TCNT1  = 0; // set counter value to 0
  
  OCR1A = frequency; // set compare match register
  
  TCCR1B |= (1 << CS12) | (1 << CS10); // Set CS12 and CS10 bits for 1:1024 prescaler

  TCCR1B |= (1 << WGM12); // turn on CTC mode
  TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
  
  sei(); // allow interrupts
}


// Die setup-Funktion wird einmalig nach "reset" oder power-up" ausgeführt 
void setup()
{   
  // Initialisiert den Pin 2 als Ausgang, der Ausgang steuert die LED
  pinMode(2, OUTPUT); 

  // Konfiguration des Timers  
  // der Quellcode sieht in der Simulation anders aus, da wir das STM-Board verwenden
  init_timer1(3000);
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
