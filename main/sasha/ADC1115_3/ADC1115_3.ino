#include <Wire.h>
#include <Adafruit_ADS1015.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);

// Адрес микросхемы
// 0x48 - ADDR pin connected to GROUND (default)
// 0x49 - ADDR pin connected to VDD
// 0x4A - ADDR pin connected to SDA
// 0x4B - ADDR pin connected to SCL
Adafruit_ADS1115 ads(0x48);

// Настройка входного делителя, в зависимости от максимального входного напряжения
// Vin MAX ADS1115
// GAIN_TWOTHIRDS // 2/3x gain +/- 6.144V 1 bit = 0.1875 mV (default)
// GAIN_ONE // 1x gain +/- 4.096V 1 bit = 0.125 mV
// GAIN_TWO // 2x gain +/- 2.048V 1 bit = 0.0625 mV
// GAIN_FOUR // 4x gain +/- 1.024V 1 bit = 0.03125 mV
// GAIN_EIGHT // 8x gain +/- 0.512V 1 bit = 0.015625 mV
// GAIN_SIXTEEN // 16x gain +/- 0.256V 1 bit = 0.0078125 mV
#define xGAIN GAIN_TWOTHIRDS // делитель
#define x1BIT 0.1875 // значение 1 бита


int16_t ADCres; // переменная для чтения результата 16 бит
float Voltage = 0.0; // переменная для расчета напряжения
float Amper = 0.0; // переменная для расчета напряжения
char buffer[2];

void setup(void) {
    Serial.begin(9600);
    lcd.init();
    lcd.backlight();

// инициализация библиотеки ADS1115
    ads.begin();
    ads.setGain(xGAIN);
}


void loop(void) {
    ADCres = ads.readADC_SingleEnded(0); // читаем результат единичного преобразования
    Voltage = (ADCres * x1BIT) / 1000; // расчитываем напряжение

    ADCres = ads.readADC_SingleEnded(1); // читаем результат единичного преобразования
    Amper = (ADCres * x1BIT) / 1000; // расчитываем напряжение

    float one = setDataToMonitor(Voltage, Amper, 0);
    Serial.println(one);
    ADCres = ads.readADC_SingleEnded(2); // читаем результат единичного преобразования
    Voltage = (ADCres * x1BIT) / 1000; // расчитываем напряжение

    ADCres = ads.readADC_SingleEnded(3); // читаем результат единичного преобразования
    Amper = (ADCres * x1BIT) / 10; // расчитываем напряжение

    float sec = setDataToMonitor(Voltage, Amper, 1);
    Serial.println(sec);
    int B = (int) sec;
    int A = (int) one;
    int C = (int) ((B * 100) / A);
    lastVal((sec * 100) / one);

    delay(1000);
}

float setDataToMonitor(float vlt, float amp, int raw) {
    float pwr = vlt * amp;
    char buffer[4];
    String s = dtostrf(vlt, 3, 2, buffer);
    lcd.setCursor(0, raw);
    lcd.print(s);

    s = dtostrf(amp, 3, 2, buffer);
    lcd.setCursor(5, raw);
    lcd.print(s);

    s = dtostrf(pwr, 4, 2, buffer);
    lcd.setCursor(10, raw);
    lcd.print(s);
    return pwr;
}

void lastVal(float value) {

    dtostrf(value, 2, 0, buffer);
//value = 55.66;

    Serial.println(value);

    Serial.println(buffer[0]);

    Serial.println(buffer[1]);
    lcd.setCursor(15, 0);
    lcd.print(buffer[0]);
    lcd.setCursor(15, 1);
    lcd.print(buffer[1]);
}
