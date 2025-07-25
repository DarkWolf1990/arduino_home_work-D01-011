const int potPin = A0;        // Пин потенциометра
const int numLEDs = 5;        // Количество светодиодов
const int ledPins[] = {2, 3, 4, 5, 6}; // Пины светодиодов

void setup() {
  for (int i = 0; i < numLEDs; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  Serial.begin(9600); // Для отладки
}

void loop() {
  int potValue = analogRead(potPin); // Читаем значение от 0 до 1023
  int ledLevel = map(potValue, 0, 1023, 0, numLEDs); // Преобразуем в диапазон от 0 до numLEDs

  // Включаем нужное количество светодиодов
  for (int i = 0; i < numLEDs; i++) {
    if (i < ledLevel) {
      digitalWrite(ledPins[i], HIGH);
    } else {
      digitalWrite(ledPins[i], LOW);
    }
  }

}