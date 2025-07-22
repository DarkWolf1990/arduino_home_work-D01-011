const int buttonPin = 2;
const int ledPin = 13;


void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);  // Включение внутреннего подтягивающего резистора
}

void loop() {
  int buttonState = digitalRead(buttonPin);
  digitalWrite(ledPin, !buttonState);  // Инвертируем, так как INPUT_PULLUP дает HIGH при отпущенной кнопке
}