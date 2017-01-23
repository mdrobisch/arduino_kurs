/* 
 * Hausaufgabe: Schrittmotoransteuerung
*/

// Funktionen bekannt machen
void schrittstellung_setzen(void);  // die Timer-Funktion wird vom Timer-Modul aufgerufen, wenn der Schwellwert des Zählers erreicht ist, hier zunächst nur die Definition

// Variablendefinitionen
int timerEreignis = 0;      // zeigt an das ein Timer Ereignis bearbeitet werden muss, 0 = kein Ereignis, 1 = Ereignis aufgetreten
int schrittstellung = 0;         // speichert die aktuell aktive LED mit ihrer Pin-Nummer

void init_timer1(int periode_in_mikrosekunden)
{
  Timer1.setChannel1Mode(TIMER_OUTPUTCOMPARE);
  Timer1.setPeriod(periode_in_mikrosekunden); // Periodendauer in Mikrosekunden
  Timer1.setCompare1(5);
  Timer1.attachCompare1Interrupt(timer_funktion);
  Timer1.resume();
}

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
  init_timer1(periode_in_mikrosekunden);
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
