#include <Arduino.h>
void setup();
void loop();
void update_candles();
void fade_candles();
void print_lums();
float lum_map(float lv);
float frand();
#line 1 "src/sketch.ino"
const int candle_pins_len = 8;
int candle_pins[8] = {6, 12, 4, 5, 11, 9, 10, 7};
float candle_lums[8] = {0, 0, 0, 0, 0, 0, 0, 0};

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < candle_pins_len; i++) {
    pinMode(candle_pins[i], OUTPUT);
    candle_lums[i] = frand();
  }

  print_lums();
}

void loop() {
  update_candles();
  fade_candles();
}

void update_candles() {
  for (int i = 0; i < candle_pins_len; i++) {
    digitalWrite(candle_pins[i], lum_map(frand()) < candle_lums[i]);
    // analogWrite(candle_pins[i], candle_lums[i] * 128);
  }
}

void fade_candles() {
  for (int i = 0; i < candle_pins_len; i++) {
    candle_lums[i] -= 0.00001;
    candle_lums[i] = fmax(0, candle_lums[i]);
  }
}

void print_lums() {
  Serial.println("lums ->");
  for (int i = 0; i < candle_pins_len; i++) {
    Serial.println(candle_lums[i]);
  }
}

float lum_map(float lv) {
  // return lv * lv * lv;
  return lv;
}

float frand() {
  return random() / 2147483647.;
}
