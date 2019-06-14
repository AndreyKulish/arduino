boolean flag = false;
boolean isOkD3 = true;
long forStamina = 0;
long forTime = 0;
long forAutoTime = 0;
String res;
int timeDel = 8000;
int zaderjka = 2;
int timeDel8 = 0;
void setup() {
  pinMode(8,OUTPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(6,OUTPUT);
  pinMode(9,INPUT);
  digitalWrite(6,LOW);
  Serial.begin(9600);

}

void loop() {
  if(Serial.available()){
    res = Serial.readString();
    forStamina = res.substring(0,2).toInt();
    forTime = res.substring(2,4).toInt();
    forAutoTime = res.substring(4,6).toInt();
    timeDel8 = map(forStamina, 0, 99, 10000, 0);
    if(forAutoTime != 0){
      flag = true;
    }else{
      flag = false;
    }
  }
  if(flag){
      work();
  }else{
    if(digitalRead(9) == LOW){
      
        if(forTime == 0){
          while(digitalRead(4) == HIGH);
            while(digitalRead(5) == HIGH);
            
            while(digitalRead(9) == LOW){
              if(digitalRead(4) == HIGH){
              delayMicroseconds(timeDel8);// 0 до 10 задержка сигнала
                digitalWrite(8,HIGH);
                  delayMicroseconds(200);// длина импульса 1-2
                digitalWrite(8,LOW);
               while(digitalRead(4) == HIGH);
             }
             if(digitalRead(5) == HIGH){
                delayMicroseconds(timeDel8);// 0 до 10 задержка сигнала
                digitalWrite(8,HIGH);
                  delayMicroseconds(200);// длина импульса 1-2
                digitalWrite(8,LOW);
               while(digitalRead(5) == HIGH);
             }
            }
        }else{
          while(digitalRead(4) == HIGH);
            while(digitalRead(5) == HIGH);
            
          for (int cut = 0; cut < forTime/2; cut++){
            if(digitalRead(4) == HIGH){
              delayMicroseconds(timeDel8);// 0 до 10 задержка сигнала
                digitalWrite(8,HIGH);
                  delayMicroseconds(200);// длина импульса 1-2
                digitalWrite(8,LOW);
               while(digitalRead(4) == HIGH);
             }
             if(digitalRead(5) == HIGH){
                delayMicroseconds(timeDel8);// 0 до 10 задержка сигнала
                digitalWrite(8,HIGH);
                  delayMicroseconds(200);// длина импульса 1-2
                digitalWrite(8,LOW);
               while(digitalRead(5) == HIGH);
             }
          }
        }
      while(digitalRead(9) == LOW);
    }
  }
  
}


//метод который уже припаевает наши детали при помощи автостарта
void lightLed(){
  delay(forAutoTime*100);

if(digitalRead(5) == HIGH){
   while(digitalRead(5) == HIGH);
 }
 
 if(digitalRead(4) == HIGH){
   while(digitalRead(4) == HIGH);
 }
 
  if(digitalRead(5) == HIGH){
  delayMicroseconds(timeDel);// 0 до 10 задержка сигнала
   digitalWrite(6,HIGH);
  delayMicroseconds(100);// длина импульса 1-2                                                                                          
  digitalWrite(6,LOW);
   while(digitalRead(5) == HIGH);
 }

 if(digitalRead(4) == HIGH){
  delay(zaderjka);//задержка после щелчка
   if(!digitalRead(3) == HIGH){
    return;
   }
   while(digitalRead(4) == HIGH);
 }
 while(digitalRead(5) == HIGH);
while(digitalRead(4) == HIGH);
  while(digitalRead(5) == HIGH);
  
  
  for (int cut = 0; cut < forTime/2; cut++){
            if(digitalRead(4) == HIGH){
              delayMicroseconds(timeDel8);// 0 до 10 задержка сигнала
                digitalWrite(8,HIGH);
                  delayMicroseconds(200);// длина импульса 1-2
                digitalWrite(8,LOW);
               while(digitalRead(4) == HIGH);
             }
             if(digitalRead(5) == HIGH){
                delayMicroseconds(timeDel8);// 0 до 10 задержка сигнала
                digitalWrite(8,HIGH);
                  delayMicroseconds(200);// длина импульса 1-2
                digitalWrite(8,LOW);
               while(digitalRead(5) == HIGH);
             }
          }
  
  
  
  delay(20); 
  while(digitalRead(5) == HIGH);
  while(digitalRead(4) == HIGH);
  whaitOk();
}

//метод который считывает прикосновения сварки 
void work(){
  for( int i = 0; i < 5; i++){
    //====================================1
 if(digitalRead(5) == HIGH){
  delayMicroseconds(timeDel);// 0 до 10 задержка сигнала
   digitalWrite(6,HIGH);
  delayMicroseconds(100);// длина импульса 1-2                                                                                          
  digitalWrite(6,LOW);
   while(digitalRead(5) == HIGH);
 }

 if(digitalRead(4) == HIGH){
  delay(zaderjka);//задержка после щелчка
   if(digitalRead(3) == LOW){
    lightLed();
   }
   while(digitalRead(4) == HIGH);
 }
//====================================2
 for(int r = 0; r < 3;r++){
  while(digitalRead(5) == LOW);
 if(digitalRead(5) == HIGH){
   while(digitalRead(5) == HIGH);
 }
}
 if(digitalRead(4) == HIGH){
  delayMicroseconds(timeDel);// 0 до 10 задержка сигнала
   digitalWrite(6,HIGH);
  delayMicroseconds(100);// длина импульса 1-2
  digitalWrite(6,LOW);
   while(digitalRead(4) == HIGH);
 }
 //====================================3
 if(digitalRead(5) == HIGH){
  delay(zaderjka);//задержка после щелчка
  if(digitalRead(3) == HIGH){
      lightLed();
   }
   while(digitalRead(5) == HIGH);
 }

     for(int r = 0; r < r;i++){
      while(digitalRead(4) == LOW);
     if(digitalRead(4) == HIGH){
       while(digitalRead(4) == HIGH);
      }
    }
  }
}
//матод который ждет когда мы разоединим сварку
void whaitOk(){
    isOkD3 = true;
      while(isOkD3){
          //====================================1
       if(digitalRead(5) == HIGH){
        delayMicroseconds(timeDel);// 0 до 10 задержка сигнала
         digitalWrite(6,HIGH);
        delayMicroseconds(100);// длина импульса 1-2                                                                                          
        digitalWrite(6,LOW);
         while(digitalRead(5) == HIGH);
       }

       if(digitalRead(4) == HIGH){
        delay(zaderjka);//задержка после щелчка
         if(!digitalRead(3) == HIGH){
          isOkD3 = false;
         }
         while(digitalRead(4) == HIGH);
       }
      //====================================2
       for(int r = 0; r < 3;r++){
        while(digitalRead(5) == LOW);
         if(digitalRead(5) == HIGH){
           while(digitalRead(5) == HIGH);
         }
      }

       if(digitalRead(4) == HIGH){
        delayMicroseconds(timeDel);// 0 до 10 задержка сигнала
         digitalWrite(6,HIGH);
        delayMicroseconds(100);// длина импульса 1-2
        digitalWrite(6,LOW);
         while(digitalRead(4) == HIGH);
       }
       //====================================3
       if(digitalRead(5) == HIGH){
        delay(zaderjka);//задержка после щелчка
        if(!digitalRead(3) == HIGH){
            isOkD3 = false;
         }
         while(digitalRead(5) == HIGH);
       }

       for(int r = 0; r < 3;r++){
        while(digitalRead(4) == LOW);
         if(digitalRead(4) == HIGH){
           while(digitalRead(4) == HIGH);
         }
        }
    }
}
