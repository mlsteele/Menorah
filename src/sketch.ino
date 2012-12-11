// #include "RunPeriodically.h"
#include "SoftPWM.h"

const int candle_pins_len = 8;
int candle_pins[8] = {6, 12, 4, 5, 11, 9, 10, 7};
float candle_lums[8] = {0, 0, 0, 0, 0, 0, 0, 0};
// int candles_time_on[8] = {0, 0, 0, 0, 0, 0, 0, 0};
// int candles_time_last_t = 0;

void setup() {
  Serial.begin(9600);

  SoftPWMBegin();

  for (int i = 0; i < candle_pins_len; i++) {
    pinMode(candle_pins[i], OUTPUT);
    candle_lums[i] = frand();
    // candle_lums[i] = 1;
  }

  print_lums();
  // candles_time_last_t = millis();
}

void loop() {
  // Serial.println("loop");
  // delay(1);
  // runPeriodically(draw_candles, 50);
  draw_candles();
  fade_candles();
  // time_count_candles();
}

void draw_candles() {
  for (int i = 0; i < candle_pins_len; i++) {
    // digitalWrite(candle_pins[i], lum_map(frand()) < candle_lums[i]);

    SoftPWMSet(candle_pins[i], wiggle(lum_map(candle_lums[i]), 0.05) * 100);

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
    candle_lums[i] -= 0.0000001;
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
  return sqrt(lv);
}

float wiggle(float n, float var) {
  n += (((random() % 2) * 2) - 2) * var;
  n = max(0, min(n, 1));
  return n;
}

float frand() {
  return random() / 2147483647.;
}
