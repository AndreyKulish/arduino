//byte forInd[32];
byte forInd[8];
int analogLeg;

int forStamina = 25;
int forTime = 0;
int forAutoTime = 0;

void setup() {
  // put your setup code here, to run once:
  /*for(int i = 8; i < 32; i++){
    forInd[i] = 0;
  }*/
  
//  numberZero();

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,HIGH);
  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  readMyAnalogLeg();
  
  showItBitch(forStamina,5);
  showItBitch(forTime,7);
  showItBitch(forAutoTime,9);
}

void numberZero(){
  forInd[0] = 1;
  forInd[1] = 1;
  forInd[2] = 1;
  forInd[3] = 1;
  forInd[4] = 0;
  forInd[5] = 1;
  forInd[6] = 1;
  forInd[7] = 0;
}
void numberOne(){
  forInd[0] = 1;
  forInd[1] = 0;
  forInd[2] = 1;
  forInd[3] = 0;
  forInd[4] = 0;
  forInd[5] = 0;
  forInd[6] = 0;
  forInd[7] = 0;
}
void numberTwo(){
  forInd[0] = 0;
  forInd[1] = 0;
  forInd[2] = 1;
  forInd[3] = 1;
  forInd[4] = 1;
  forInd[5] = 1;
  forInd[6] = 1;
  forInd[7] = 0;
}
void numberThre(){
  forInd[0] = 1;
  forInd[1] = 0;
  forInd[2] = 1;
  forInd[3] = 1;
  forInd[4] = 1;
  forInd[5] = 1;
  forInd[6] = 0;
  forInd[7] = 0;
}
void numberFore(){
  forInd[0] = 1;
  forInd[1] = 1;
  forInd[2] = 1;
  forInd[3] = 0;
  forInd[4] = 1;
  forInd[5] = 0;
  forInd[6] = 0;
  forInd[7] = 0;
}
void numberFive(){
  forInd[0] = 1;
  forInd[1] = 1;
  forInd[2] = 0;
  forInd[3] = 1;
  forInd[4] = 1;
  forInd[5] = 1;
  forInd[6] = 0;
  forInd[7] = 0;
}
void numberSix(){
  forInd[0] = 1;
  forInd[1] = 1;
  forInd[2] = 0;
  forInd[3] = 1;
  forInd[4] = 1;
  forInd[5] = 1;
  forInd[6] = 1;
  forInd[7] = 0;
}
void numberSeven(){
  forInd[0] = 1;
  forInd[1] = 0;
  forInd[2] = 1;
  forInd[3] = 1;
  forInd[4] = 0;
  forInd[5] = 0;
  forInd[6] = 0;
  forInd[7] = 0;
}
void numberEight(){
  forInd[0] = 1;
  forInd[1] = 1;
  forInd[2] = 1;
  forInd[3] = 1;
  forInd[4] = 1;
  forInd[5] = 1;
  forInd[6] = 1;
  forInd[7] = 0;
}
void numberNine(){
  forInd[0] = 1;
  forInd[1] = 1;
  forInd[2] = 1;
  forInd[3] = 1;
  forInd[4] = 1;
  forInd[5] = 1;
  forInd[6] = 0;
  forInd[7] = 0;
}
void clearNumb(){
  forInd[0] = 0;
  forInd[1] = 0;
  forInd[2] = 0;
  forInd[3] = 0;
  forInd[4] = 0;
  forInd[5] = 0;
  forInd[6] = 0;
  forInd[7] = 0;
}
void dote(){
  forInd[7] = 1;
}

void showItBitch(int var, int leg){
  if(leg == 5){
      myCaseMasaFucka(var/10);
      showNumb(leg);
      myCaseMasaFucka(var%10);
      showNumb(leg + 1);
  }else{
    if(var < 10){
      myCaseMasaFucka(0);
      dote();
      showNumb(leg);
      myCaseMasaFucka(var);
      showNumb(leg + 1);
    }else 
    if(var > 9 && var < 99){
      myCaseMasaFucka(var/10);
      dote();
      showNumb(leg);
      myCaseMasaFucka(var%10);
      showNumb(leg + 1);
    }
  }
}

void showNumb(int legS){
  
  for(int i = 0; i < 8; i++){
      if(forInd[i] == 0){
        digitalWrite(3,HIGH);
      }
      digitalWrite(4, HIGH);
    
      digitalWrite(3,LOW);
      digitalWrite(4, LOW);
    }
    digitalWrite(2,HIGH);
    digitalWrite(2,LOW);
    
    digitalWrite(legS,LOW);
    delayMicroseconds(100);
    digitalWrite(legS,HIGH);
}

void readMyAnalogLeg(){
  
  analogLeg = 0;
  
  
  analogLeg = map(analogRead(4), 0, 1023, 0, 50);
  
  
  
  
 if (analogLeg < 40){
    delay(20);
    analogLeg = map(analogRead(4), 0, 1023, 0, 50);
    Serial.println("===========123");
    Serial.println(analogLeg);
    if(analogLeg < 5){
      while(analogLeg < 5)analogLeg = map(analogRead(4), 0, 1023, 0, 50);
      forTime-=1;
      Serial.println("forTime");
      Serial.println(forTime);
    }else
    if(analogLeg > 10 && analogLeg < 20){
      while(analogLeg > 10 && analogLeg < 20)analogLeg = map(analogRead(4), 0, 1023, 0, 50);
      forStamina+=5;
      Serial.println("forStamina");
      Serial.println(forStamina);
    }else
    if(analogLeg > 25 && analogLeg < 35){
      while(analogLeg > 25 && analogLeg < 35)analogLeg = map(analogRead(4), 0, 1023, 0, 50);
      forStamina-=5;
      Serial.println("forStamina");
      Serial.println(forStamina);
    }
    while(analogLeg < 40)analogLeg = map(analogRead(4), 0, 1023, 0, 50);
  }

  analogLeg = 0;

  
  analogLeg = map(analogRead(3), 0, 1023, 0, 50);
  
  
  if (analogLeg < 40){
    delay(20);
    analogLeg = map(analogRead(3), 0, 1023, 0, 50);
    Serial.println("===========456");
    Serial.println(analogLeg);
    if(analogLeg < 5){
      while(analogLeg < 5)analogLeg = map(analogRead(3), 0, 1023, 0, 50);
      forAutoTime+=1;
      Serial.println("forAutoTime");
      Serial.println(forAutoTime);
    }else
    if(analogLeg > 10 && analogLeg < 20){
      while(analogLeg > 10 && analogLeg < 20)analogLeg = map(analogRead(3), 0, 1023, 0, 50);
      forAutoTime-=1;
      Serial.println("forAutoTime");
      Serial.println(forAutoTime);
    }else
    if(analogLeg > 25 && analogLeg < 35){
      while(analogLeg > 25 && analogLeg < 35)analogLeg = map(analogRead(3), 0, 1023, 0, 50);
      forTime+=1;
      Serial.println("forTime");
      Serial.println(forTime);
    }
    while(analogLeg < 40)analogLeg = map(analogRead(3), 0, 1023, 0, 50);
  }
}

void myCaseMasaFucka(int numb){
  switch (numb) {
    case 1:
      numberOne();
      break;
    case 2:
      numberTwo();
      break;
    case 3:
      numberThre();
      break;
    case 4:
      numberFore();
      break;
    case 5:
      numberFive();
      break;
    case 6:
      numberSix();
      break;
    case 7:
      numberSeven();
      break;
    case 8:
      numberEight();
      break;
    case 9:
      numberNine();
      break;
    case 0:
      numberZero();
      break;
    default: 
    break;
  }
}
