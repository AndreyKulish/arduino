boolean flag = true;

void setup() {
  pinMode(7,OUTPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(6,OUTPUT);
  digitalWrite(6,LOW);

}

void loop() {
  for ( int x = 0; x < 100; x++){
    work();
  }

  //delay(5000);// если нужно убрать паузу, удали это
}

void work(){
  for( int i = 0; i < 5; i++){
    //====================================1
 if(digitalRead(5) == HIGH){
  delayMicroseconds(7600);// 0 до 10 задержка сигнала
   digitalWrite(6,HIGH);
  delayMicroseconds(100);// длина импульса 1-2                                                                                          
  digitalWrite(6,LOW);
   while(digitalRead(5) == HIGH);
 }

 if(digitalRead(4) == HIGH){
  delayMicroseconds(1500);//задержка после щелчка
   if(digitalRead(3) == HIGH){
      digitalWrite(7, HIGH);
   }else{
    digitalWrite(7, LOW);
   }
   while(digitalRead(4) == HIGH);
 }
//====================================2

for(int i = 0; i < 3;i++){
  while(digitalRead(5) == LOW);
 if(digitalRead(5) == HIGH){
   while(digitalRead(5) == HIGH);
 }
}

 if(digitalRead(4) == HIGH){
  delayMicroseconds(7600);// 0 до 10 задержка сигнала
   digitalWrite(6,HIGH);
  delayMicroseconds(100);// длина импульса 1-2
  digitalWrite(6,LOW);
   while(digitalRead(4) == HIGH);
 }
 //====================================3
 if(digitalRead(5) == HIGH){
  delayMicroseconds(1500);//задержка после щелчка
  if(digitalRead(3) == HIGH){
      digitalWrite(7, HIGH);
   }else{
    digitalWrite(7, LOW);
   }
   while(digitalRead(5) == HIGH);
 }
for(int i = 0; i < 3;i++){
  while(digitalRead(4) == LOW);
 if(digitalRead(4) == HIGH){
   while(digitalRead(4) == HIGH);
 }
}
}
}
