#define dir 8
#define pul 9
#define buttonDown 12
#define ena 13
//9=>pul
int x=900; // x=600

void setup() {                
  pinMode(dir, OUTPUT);      
  pinMode(pul, OUTPUT); 
  digitalWrite(dir,LOW);
  digitalWrite(pul, LOW);
}
void loop() {
  for(int j=0; j<1500; j++) {
    int buttonCase=digitalRead(buttonDown);
  for(int i=0; i<150; i++) {//  for(int i=0; i<6; i++) {
if(buttonCase==0){
  digitalWrite(pul,HIGH);
  delayMicroseconds(x);        
  digitalWrite(pul, LOW); 
 // delayMicroseconds(x);
}
  }
  
  if(x>100) x-=2;
  if  (buttonCase==1){
    digitalWrite(dir,HIGH);
     digitalWrite(pul,HIGH);
  delayMicroseconds(x);        
  digitalWrite(pul, LOW); 
   
  }

} 
}
