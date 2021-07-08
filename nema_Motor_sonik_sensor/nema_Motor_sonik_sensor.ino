#define button 12
const int ena = 13; //habilita o motor
const int dir = 8; //determina a direção
const int pul = 9; //executa um passo
const int intervalo =350;   //intervalo entre as 
   // mudanças de estado do pulso
//boolean pulso = LOW; //estado do pulso

void setup()
{ Serial.begin(9600);
pinMode(ena, OUTPUT);
pinMode(dir, OUTPUT);
pinMode(pul, OUTPUT);
digitalWrite(ena,LOW); //habilita em low invertida 
digitalWrite(dir,HIGH);
// low CW / high CCW 
digitalWrite(pul,LOW); //borda de descida
}
 
void loop()
{//pulso = !pulso; //inverte o estado da variável
int buttonCase=digitalRead(button);
Serial.print(buttonCase);
if(buttonCase==0){
  digitalWrite(pul,HIGH); //atribui o novo estado à porta
delayMicroseconds(intervalo);
}
else{
  digitalWrite(pul,LOW);

}


}
