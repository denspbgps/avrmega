#include <iarduino_OLED_txt.h>
#include <iarduino_OLED_txt.h>                                         // Подключаем библиотеку iarduino_OLED_txt.
iarduino_OLED_txt myOLED(0x3C);
extern uint8_t SmallFontRus[];  


// приём двух float чисел через сериал
// десятичный разделитель - . (точка)
// разделитель - ; (семиколон)
// пример посылки: 5.326;-3.589
void setup() {
  Serial.begin(9600);
  Serial.setTimeout(50);    // таймаут шоб не ждать (по умолч. секунда)
  pinMode(49, OUTPUT);  //настройка выхода pin 49
  pinMode(47, OUTPUT);  //настройка выхода pin 47
  pinMode(48, OUTPUT);  //настройка выхода pin 48
  pinMode(14,OUTPUT);  //настройка выхода pin 14
  pinMode(13,OUTPUT);  //настройка выхода pin 13
    myOLED.begin();                                                    // Инициируем работу с дисплеем.
    myOLED.setFont(SmallFontRus);
    myOLED.clrScr();

  
}
void loop() {

   digitalWrite(47, HIGH);
   digitalWrite(48, LOW);
    delay (500);
   digitalWrite(47, LOW);
    digitalWrite(48, HIGH);
    delay (500);
     
  
  if (Serial.available() > 0) {
    String bufString = Serial.readString();       // читаем как строку
    byte dividerIndex = bufString.indexOf(';');   // ищем индекс разделителя
    String buf_1 = bufString.substring(0, dividerIndex);    // создаём строку с первым числом
    String buf_2 = bufString.substring(dividerIndex + 1);   // создаём строку со вторым числом
    float val_1 = buf_1.toFloat();    // преобразуем во флоат
    float val_2 = buf_2.toFloat();    // ...
    myOLED.clrScr();
    Serial.print("PWM(1)= ");
    myOLED.print("PWM(1)= ", 0, 0);// вывод на олед дисплей PWM_1
    Serial.println(val_1);  // проверка
    myOLED.print(val_1, 44, 0);  вывод значения PWM
    Serial.print("PWM(2)= ");
    Serial.println(val_2);  // ...
    //Serial.println(val_1, 5);  // вывод с 5 знаками после запятой
    //Serial.println(val_2, 7);  // вывод с 7 знаками
    analogWrite(14,val_1 );
    analogWrite(13,val_2 );
  }
}
