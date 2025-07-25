/*
Задача
На занятии мы делали бегущий светодиод,
для этого мы создавали последовательность,
в которой указывали битность светодиодов.
Сделайте так, чтобы индикация была разной, например:
горят четыре любых светодиода, горят пять любых светодиодов.
Можно создать последовательность сложнее,
и добиться многоуровневой индикации.
Можно выполнять задание с семисегментным индикатором.
* */
const int dataPin = 12;
const int latchPin = 8;
const int clockPin = 10;

byte digitToSegment[] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111  // 9
  };

void setup() {
    pinMode(dataPin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    randomSeed(analogRead(0));
}

void loop() {
    // 1. Случайная комбинация 4 светодиодов и цифра
    showRandomLeds(4, 0);
    delay(800);

    // 2. Бегущий огонёк + счётчик от 0 до 9
    for (int i = 0; i < 8; i++) {
        byte ledPattern = 1 << i;
        showOnDisplays(i % 10, ledPattern);
        delay(200);
    }

    // 3. Волна и цифра 8
    waveEffect(150, 8);
}

// Показывает цифру на индикаторе и паттерн на светодиодах
void showOnDisplays(int digit, byte ledPattern) {
    byte segmentData = digitToSegment[digit % 10];
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, segmentData); // сначала 7-сегмент
    shiftOut(dataPin, clockPin, MSBFIRST, ledPattern);  // потом светодиоды
    digitalWrite(latchPin, HIGH);
}

// Включить N случайных светодиодов и цифру
void showRandomLeds(int count, int digit) {
    byte pattern = 0;
    int setBits = 0;
    while (setBits < count) {
        int pos = random(0, 8);
        if (bitRead(pattern, pos) == 0) {
            bitSet(pattern, pos);
            setBits++;
        }
    }
    showOnDisplays(digit, pattern);
}

// Волна от краёв к центру с цифрой
void waveEffect(int delayMs, int digit) {
    for (int i = 0; i < 4; i++) {
        byte pattern = 0;
        bitSet(pattern, i);
        bitSet(pattern, 7 - i);
        showOnDisplays(digit, pattern);
        delay(delayMs);
    }
    showOnDisplays(digit, 0); // очистка
}
