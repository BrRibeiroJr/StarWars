//Bibliotecas
#include <TimerOne.h>
#include <LiquidCrystal.h>

//Declaração de variáveis
int analogPin = A0;     // Potenciômetro
//int ledPin = 13;     
int Triac = 3;
int sensorValue = 0;  // variable to store the value coming from the sensor
int pot = 0;
long tempo ;


// Inicializar os pinos do display LCD 16x2
LiquidCrystal lcd(13,12,11,10,9,8);


void setup() {
  //pinMode(ledPin, OUTPUT);
  pinMode(Triac, OUTPUT);
  Timer1.initialize();
  attachInterrupt(2, zero_crosss_int, RISING);     // Interrupção detecta a passagem por 0, quando passa de nível baixo para aLto
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
}



void zero_crosss_int()                             // Função que detecta a passagem por 0
{
   Timer1.attachInterrupt(gateTRIAC, tempo);  //associa a funcao gateTRIAC com Interrupcao do TIMER1
   Timer1.start();                           // inicia contagem TIMER1
}


void gateTRIAC ()
{                                       // trata interrupcao do TIMER1 gerando pulso no gate do TRIAC
digitalWrite(Triac, HIGH);    // dispara o Triac
delayMicroseconds(5);         // aguarda 5 microsegundos para garantir disparo do TRIAC
digitalWrite(Triac, LOW);     // desabibilta gate do TRIAC
Timer1.stop();

}


void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(analogPin);
  int pot = map(sensorValue,0,1023,0,100);
  tempo = map(pot,0,100,8100,100);
  lcd.setCursor(6,0);
  lcd.print("DIMMER");
  lcd.setCursor(7,1);
  lcd.print(pot);
  lcd.setCursor(11,1);
  lcd.print("%");
  
}

