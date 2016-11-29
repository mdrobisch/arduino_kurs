/* 
 * LED mit Timer
*/

void timer_funktion(void);  // die Timer-Funktion wird vom Timer-Modul aufgerufen, wenn der Schwellwert des Zählers erreicht ist, hier zunächst nur die Definition
int led_zustand = 0;    // der Zustand der LED, 0 = aus, 1 = an 

void init_timer1(unsigned long period_in_us)
{
  Timer1.setChannel1Mode(TIMER_OUTPUTCOMPARE);
  Timer1.setPeriod(period_in_us); // Periodendauer in Mikrosekunden
  Timer1.setCompare1(1);
  Timer1.attachCompare1Interrupt(timer_funktion);
  Timer1.resume();
}

// Die setup-Funktion wird einmalig nach "reset" oder power-up" ausgeführt 
void setup()
{   
  // Initialisiert den Pin 2 als Ausgang, der Ausgang steuert die LED
  pinMode(2, OUTPUT); 

  // Konfiguration des Timers  
  // der Quellcode sieht in der Simulation anders aus, da wir das STM-Board verwenden
  init_timer1(1000000);
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
