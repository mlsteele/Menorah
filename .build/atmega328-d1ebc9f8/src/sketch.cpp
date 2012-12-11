#include <Arduino.h>
void setup();
void loop();
void draw_candles();
void fade_candles();
void print_lums();
float lum_map(float lv);
float frand();
#line 1 "src/sketch.ino"
const int candle_pins_len = 8;
int candle_pins[8] = {6, 12, 4, 5, 11, 9, 10, 7};
float candle_lums[8] = {0, 0, 0, 0, 0, 0, 0, 0};
// int candles_time_on[8] = {0, 0, 0, 0, 0, 0, 0, 0};
// int candles_time_last_t = 0;

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < candle_pins_len; i++) {
    pinMode(candle_pins[i], OUTPUT);
    candle_lums[i] = frand();
    // candle_lums[i] = 1;
  }

  print_lums();
  // candles_time_last_t = millis();
}

void loop() {
  draw_candles();
  fade_candles();
  delay(10);
  // time_count_candles();
}

void draw_candles() {
  for (int i = 0; i < candle_pins_len; i++) {
    digitalWrite(candle_pins[i], lum_map(frand()) < candle_lums[i]);

    // analogWrite(candle_pins[i], candle_lums[i] * 128);

    // if (candles_time_on[i] > 1000 * candle_lums[i]) {
    //   candles_time_on[i] = 0;
    //   digitalWrite(candle_pins[i], !digitalRead(candle_pins[i]));
    // }
  }
}

// void time_count_candles() {
//   int step = millis() - candles_time_last_t;
//   candles_time_last_t = millis();
//   for (int i = 0; i < candle_pins_len; i++) {
//     candles_time_on[i] += step;
//   }
// }

void fade_candles() {
  for (int i = 0; i < candle_pins_len; i++) {
    candle_lums[i] -= 0.0001;
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
