unsigned long chek;
boolean flag = true;
int legVuhodFirst = 11;
int legVuhodSecond = 11;

void setup() {
  pinMode(7,OUTPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(legVuhodFirst,OUTPUT);
  pinMode(legVuhodSecond,OUTPUT);
  digitalWrite(6,LOW);
digitalWrite(legVuhodFirst , LOW);
digitalWrite(legVuhodSecond , LOW);

}

void loop() {

    if(flag){ 
      while(digitalRead(5) == LOW);
      while(digitalRead(4) == LOW);
      flag = false;
    }
    work();
}

void work(){
  while(true){
    //====================================1
 if(digitalRead(5) == LOW){
  delayMicroseconds(8300);// 0 до 10 задержка сигнала
  digitalWrite(legVuhodSecond, HIGH);
  delayMicroseconds(500);// длина импульса 1-2                                                                                          
  digitalWrite(legVuhodSecond, LOW);
   while(digitalRead(5) == LOW);
 }

 if(digitalRead(4) == LOW){
  delayMicroseconds(8300);// 0 до 10 задержка сигнала
  digitalWrite(legVuhodFirst, HIGH);
  delayMicroseconds(500);// длина импульса 1-2                                                                                          
  digitalWrite(legVuhodFirst, LOW);
   while(digitalRead(4) == LOW);
 }

}
}//проверять под напряжением


