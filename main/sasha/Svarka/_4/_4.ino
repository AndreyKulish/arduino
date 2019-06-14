boolean flag = true;

void setup() {
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(6,OUTPUT);
  digitalWrite(6,LOW);

}

void loop() {
  for ( int x = 0; x < 100; x++){
    work();
  }

  delay(5000);// если нужно убрать паузу, удали это
}

void work(){
  for( int i = 0; i < 5; i++){
 if(digitalRead(5) == HIGH){
  delay(7);// 0 до 10 задержка сигнала
   digitalWrite(6,HIGH);
  delayMicroseconds(100);// длина импульса 1-2
  digitalWrite(6,LOW);
   while(digitalRead(5) == HIGH);
 }

 //if(digitalRead(4) == HIGH){
  //delay(7);// 0 до 10 задержка сигнала
  // digitalWrite(6,HIGH);
 // delayMicroseconds(100);// длина импульса 1-2
  //digitalWrite(6,LOW);
  // while(digitalRead(4) == HIGH);
// }
}
}

