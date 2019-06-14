/*
Arduino IDE 1.5.4
Паяльник на Arduino Pro Mini  v0.4

Alex link
http://www.youtube.com/c/AlexLink-Free
http://vk.com/linklife
http://www.facebook.com/groups/Arduno.life/
 // Пины еодключения индикаторов
 ANODES(CATHODES):
 D1 - a
 D2 - b
 D4 - c
 D6 - d
 D7 - e
 D5 - f
 D3 - g
 D0 - dp (digital point) Я НЕ подключал - резерв... индикатора :)))
 
      a1
   ********
   *      *
 f *      * b2
 5 *  g3  *
   ********
   *      *
 e *      * c4
 7 *  d6  *
   ******** # dp0
 
 CATHODES(ANODES):
 D16 - cathode 3
 D15 - cathode 2
 D12 - cathode 1
 */

// ------------------------------------------------------------------------------------------------
int indicator = 1; // 0 = Катод  1 = Анод  Выбрать под Ваш индикатор !!!!

byte  digits[] = {
  B00001001,B11101011,B00110001,B10100001,B11000011,B10000101,B00000101,B11101001,B00000001,B10000001};

int digit_common_pins[]={16,15,12};  // пины для разрядов сегментов(при изменении убедитесь что Ваш порт не используется)
int refresh_delay = 1;
int count_delay = 300; // COUNTING SECONDS IF count_delay = 1000
long actual_count_delay = 0;
long actual_refresh_delay = 0;
int increment = 0;   //Стартовое значение на сегментах
int max_digits =3;  //  Кол-во знакомест
int current_digit=max_digits-1;
int increment_max = pow(10,max_digits);
// -------------------------------------------------- не изменять, это для Сегментов -----------------------------------------------


//--------------------- переменные паяльника -----------------------------
int knopka = 3; //Пин кнопок


int tin = 0; // Пин Датчика температуры IN Analog через LM358N
int pinpwm = 11;// порт нагревательного элемента(через транзистор)PWM

int tempust = 300; // установленная температура
int tempmin = 200; // минимальная температура
int tempmax = 480; // максимальная температура
int tempreal = 250; // переменная датчика текущей температуры
int temppwmmin = 40; // минимальное значение PWM нагревателя  
int temppwmmax = 180; // максимальное значение PWM нагревателя
int temppwmreal = 0; // текущее значение PWM нагревателя
int airreal = 100; // стартовое значение PWM вентилятора(если нужно)

int temperror = -50; // разница температур(установленная - реальная)

int temprazn = 0; // переменная разницы температуры(установленная - текущая)


boolean flag = false;
long show_actual_value = 0;
int show_value = 2000;


void setup(){
  
 if(indicator == 0){   //Если вначале был выбран общий Катод
                    for(int i=0; i<10;i++){
                                           digits[i] = ~ digits[i];
                                           }
                   }
  
  pinMode(pinpwm,OUTPUT);     // Порт нагрузки(паяльника) настраиваем на выход
  analogWrite(pinpwm, temppwmreal);     //Вывод  шим в нагрузку паяльника (выводим 0 - старт с выключеным паяльником- пока не опредилим состояние температуры)
  
 
  // -------------------------------------------------- не изменять, это для Сегментов -----------------------------------------------
  DDRD = B11111111;
  for (int y=0;y<max_digits;y++)
          {
           pinMode(digit_common_pins[y],OUTPUT);
           digitalWrite(digit_common_pins[y], LOW);    
          }
  // -------------------------------------------------- не изменять, это для Сегментов -----------------------------------------------

}

void loop() {
    
  show(increment);   // Вывести значение переменной на экран(LED)
   
    
   if (tempreal < tempust ){   // Если температура паяльника ниже установленной температуры то:
      
            if ((tempust - tempreal) < 16 & (tempust - tempreal) > 6 ) // Проверяем разницу между у становленной температурой и текущей паяльника,
                                     // Если разница меньше 10 градусов то 
                             { 
                              temppwmreal = 99;  // Понижаем мощность нагрева (шим 0-255  мы делаем 99)  - таким образом мы убираем инерцию перегрева
                              }
             else  if ((tempust - tempreal) < 7 & (tempust - tempreal) > 3)
                                                                {              
                                                                  temppwmreal = 80;  // Понижаем мощность нагрева (шим 0-255  мы делаем 99)  - таким образом мы убираем инерцию перегрева
                                                                 }
                              
                         else if ((tempust - tempreal) < 4 )
                                                      {              
                                                       temppwmreal = 45;  // Понижаем мощность нагрева (шим 0-255  мы делаем 99)  - таким образом мы убираем инерцию перегрева
                                                       }  
                                                     
                                                     
                            else {
                                  temppwmreal = 230; // Иначе Подымаем мощность нагрева(шим 0-255  мы делаем 230) на максимум для быстрого нагрева до нужной температуры
                                 }
                        
                              
      analogWrite(pinpwm, temppwmreal);     //Вывод в шим порт (на транзистор) значение мощности
    }
 else { //Иначе (если температура паяльника равняется или выше установленной) 
            
            temppwmreal = 0;  // Выключаем мощность нагрева (шим 0-255  мы делаем 0)  - таким образом мы отключаем паяльник
            analogWrite(pinpwm, temppwmreal);   //Вывод в шим порт (на транзистор) значение мощности
          } 
 
  
  if(millis() - actual_count_delay > count_delay) // это для сегментов 

  {  
    actual_count_delay = millis();
     // Здесь мы пишем нашу прогу по считыванию состояния кнопок (это место в счетчк не будет тормозить вывод на сегменты)
   
    tempreal = analogRead(0);// считываем текущую температуру
    
    tempreal=map(tempreal,-50,700,0,500);   // нужно вычислить

     increment=tempreal;

     if(flag) {
       if(millis() - show_actual_value < show_value) {
        increment = tempust;
      } else {
        flag = false;
      }
     }
    
  //---------------------------------------------------------- Кнопки -------------------------------------------------------------------------  
          if (analogRead(knopka) == 0)  // Если нажата вниз кнопка то понизить температуру на 10
                               {
                               if( tempust <= tempmin || (tempust-10) <= tempmin )
                                                          {
                                                            tempust= tempmin;
                                                            increment = tempust;
                                                          }
                                       else { 
                                             tempust=tempust-10;
                                             increment = tempust;
                                             show(increment);   // Вывести значение переменной на экран(LED)
                                            flag = true;
                                            show_actual_value = millis();
                                              } 
                                 
                                 
                              
                               }
  
          else if (analogRead(knopka) > 500 && analogRead(knopka) < 524 )  // Если нажата вверх кнопка то повысить температуру на 10
                                       {
                                       tempust=tempust+10;
                                       if( tempust >=tempmax)
                                                          {
                                                            tempust= tempmax;
                                                          }
                                       increment = tempust;
                                       show(increment);   // Вывести значение переменной на экран(LED)
                                      flag = true;
                                      show_actual_value = millis();
                                       }
 
    
  }
}

void show(int value) { //------------------------------- подпрограмма для вывода на сегменты   - лучше не изменять ---------------------------------------------
  int digits_array[]={};  
  int y=0;
  boolean empty_most_significant = true; 
  

  
  if(millis() - actual_refresh_delay >= refresh_delay)
  {  

  for (int z=max_digits-1;z>=0;z--)
  {


    digits_array[z] = value / pow(10,z); //rounding down by converting from float to int
    
    if(digits_array[z] != 0 ) empty_most_significant = false;  // DON'T SHOW LEADING ZEROS
    
    value = value - digits_array[z] * pow(10,z);




 
   if(z==current_digit)
        {
         if(!empty_most_significant || z==0){ // DON'T SHOW LEADING ZEROS EXCEPT FOR THE LEAST SIGNIFICANT
            
                                            PORTD = digits[digits_array[z]];
                                            }
                                       else
                                            {
                                             if(indicator == 0){   //Если вначале был выбран общий Катод
                                                                PORTD = B00000000;  
                                                                }
                                                     else{
                                                           PORTD = B11111111;
                                                          }  
                                            }

       if(indicator == 0){ 
                         digitalWrite(digit_common_pins[z], LOW);
                         }
             else{
                  digitalWrite(digit_common_pins[z], HIGH);
                 }
      }
 else{
     
     if(indicator == 0){ 
                         digitalWrite(digit_common_pins[z], HIGH);
                         }
             else{
                  digitalWrite(digit_common_pins[z], LOW);
                 }
   }

}
  

      current_digit--;
      if(current_digit < 0) 
      {
        current_digit= max_digits; // NEED AN EXTRA REFRESH CYCLE TO CLEAR ALL DIGITS
      }
 
 actual_refresh_delay =  millis();     
 }

}


