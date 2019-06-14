boolean flag = false;
boolean isOkD3 = true;
long forStamina = 0;
long forTime = 0;
long forAutoTime = 0;
String res;
int timeDel = 8500;
int zaderjka = 2;
int timeDel8 = 0;
void setup() {
  pinMode(11,OUTPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(6,OUTPUT);
  pinMode(9,INPUT);
  digitalWrite(6,LOW);
  Serial.begin(9600);

}

void loop() {
  if(Serial.available()){ // если пришли данные то обновляем их
    res = Serial.readString(); // считываем данные все из порта от первого главного мк
    forStamina = res.substring(0,2).toInt();//записываем первых два числа в % силы работы
    forTime = res.substring(2,4).toInt(); // вторые два числа это время которое будет работать
    forAutoTime = res.substring(4,6).toInt();//автостарт, когда на 3 ноге высокое оно сработает через время которое тут указанно
    timeDel8 = map(forStamina, 50, 99, 6500, 1500);//выставляем мощность, или же задержку перед клацом
    if(forAutoTime != 0){// если автотайм у нас = 0 то мы пользуемся кнопкой
      flag = true;
    }else{
      flag = false;
    }
  }
  if(flag){
      work();// если автостарт у нас НЕ равен 0 
  }else{
    if(digitalRead(9) == LOW){// при нажатии кнопки
      
        if(forTime == 0){// и когда время работы (3 и 4) цифра равна нулю
          while(digitalRead(4) == HIGH);
            while(digitalRead(5) == HIGH);
            
            while(digitalRead(9) == LOW){// и пока у нас будет зажата кнопка, мы будем клацать большой ТРАНЗИСТОР
              if(digitalRead(4) == HIGH){
              delayMicroseconds(timeDel8);// 0 до 10 задержка сигнала
                digitalWrite(11,HIGH);
                  delayMicroseconds(500);// длина импульса 1-2
                digitalWrite(11,LOW);
               while(digitalRead(4) == HIGH);
             }
             if(digitalRead(5) == HIGH){
                delayMicroseconds(timeDel8);// 0 до 10 задержка сигнала
                digitalWrite(11,HIGH);
                  delayMicroseconds(500);// длина импульса 1-2
                digitalWrite(11,LOW);
               while(digitalRead(5) == HIGH);
             }
            }
        }else{// а если время указанно, то будем стрелять указанное время
          while(digitalRead(4) == HIGH);
            while(digitalRead(5) == HIGH);
            
          for (int cut = 0; cut < forTime/2; cut++){
            if(digitalRead(4) == HIGH){
              delayMicroseconds(timeDel8);// 0 до 10 задержка сигнала
                digitalWrite(11,HIGH);
                  delayMicroseconds(500);// длина импульса 1-2
                digitalWrite(11,LOW);
               while(digitalRead(4) == HIGH);
             }
             if(digitalRead(5) == HIGH){
                delayMicroseconds(timeDel8);// 0 до 10 задержка сигнала
                digitalWrite(11,HIGH);
                  delayMicroseconds(500);// длина импульса 1-2
                digitalWrite(11,LOW);
               while(digitalRead(5) == HIGH);
             }
          }
        }
      while(digitalRead(9) == LOW);// ждем пока кнопку отпустим
    }
  }
  
}


//метод который уже припаевает наши детали при помощи автостарта
void lightLed(){
  delay(forAutoTime*100);// задержка автостарта
// тут еще раз проверяем зажато или нет, что бы избавиться от случайного прикосновения
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
 // тут уже мы убедились и последнее приготовление
 while(digitalRead(5) == HIGH);
while(digitalRead(4) == HIGH);
  while(digitalRead(5) == HIGH);
  
  //тут открываем рабочий транзистор или симистор - хз
  for (int cut = 0; cut < forTime/2; cut++){
            if(digitalRead(4) == HIGH){
              delayMicroseconds(timeDel8);// 0 до 10 задержка сигнала
                digitalWrite(11,HIGH);
                  delayMicroseconds(500);// длина импульса 1-2
                digitalWrite(11,LOW);
               while(digitalRead(4) == HIGH);
             }
             if(digitalRead(5) == HIGH){
                delayMicroseconds(timeDel8);// 0 до 10 задержка сигнала
                digitalWrite(11,HIGH);
                  delayMicroseconds(500);// длина импульса 1-2
                digitalWrite(11,LOW);
               while(digitalRead(5) == HIGH);
             }
          }
  
  
  
  delay(20); 
  while(digitalRead(5) == HIGH);
  while(digitalRead(4) == HIGH);
  // тут мы ждем пока рассоединим сварку
  whaitOk();
}

//метод который считывает прикосновения сварки 
void work(){
  // по 5 раз проходимся хз для чего, но так лучше, ждем пока прикоснемся сваркой
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
//матод который ждет когда мы разоединим сварку и больше ничего 
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
