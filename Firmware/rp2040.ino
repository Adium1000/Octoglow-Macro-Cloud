#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Pins
#define PIN_BUZZER      28
#define PIN_LED         27
#define PIN_OLED_SCL    26
#define PIN_OLED_SDA    15
#define PIN_BTN1        1
#define PIN_BTN2        2
#define PIN_BTN3        3
#define PIN_ENC_BTN     0
#define PIN_ENC_LEFT    5
#define PIN_ENC_RIGHT   4

// Display
#define SCREEN_WIDTH    128
#define SCREEN_HEIGHT   32
#define OLED_ADDR       0x3C

// Beep settings
#define BEEP_FREQ       2000
#define BEEP_MS         30

// Encoder transitions per detent (usually 4, some encoders use 2)
#define ENC_STEPS       4

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire1, -1);

const uint8_t buttonPins[] = {PIN_BTN1, PIN_BTN2, PIN_BTN3, PIN_ENC_BTN};
const uint8_t buttonCount = sizeof(buttonPins) / sizeof(buttonPins[0]);

bool lastState[4];
unsigned long lastChange[4];
const unsigned long debounceMs = 20;

uint8_t encPrev = 0;
int8_t encAcc = 0;
const int8_t encTable[16] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};

void beep() {
  tone(PIN_BUZZER, BEEP_FREQ, BEEP_MS);
}

void showLogo() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds("Octoglow", 0, 0, &x1, &y1, &w, &h);
  display.setCursor((SCREEN_WIDTH - w) / 2, (SCREEN_HEIGHT - h) / 2);
  display.print("Octoglow");
  display.display();
}

void setup() {
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, HIGH);

  for (uint8_t i = 0; i < buttonCount; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
    lastState[i] = digitalRead(buttonPins[i]);
    lastChange[i] = 0;
  }
  pinMode(PIN_ENC_LEFT, INPUT_PULLUP);
  pinMode(PIN_ENC_RIGHT, INPUT_PULLUP);
  encPrev = (digitalRead(PIN_ENC_LEFT) << 1) | digitalRead(PIN_ENC_RIGHT);

  Wire1.setSDA(PIN_OLED_SDA);
  Wire1.setSCL(PIN_OLED_SCL);
  Wire1.begin();

  if (display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    showLogo();
  }
}

void loop() {
  unsigned long now = millis();

  for (uint8_t i = 0; i < buttonCount; i++) {
    bool state = digitalRead(buttonPins[i]);
    if (state != lastState[i] && now - lastChange[i] > debounceMs) {
      lastChange[i] = now;
      lastState[i] = state;
      if (state == LOW) {
        beep();
      }
    }
  }

  uint8_t encNow = (digitalRead(PIN_ENC_LEFT) << 1) | digitalRead(PIN_ENC_RIGHT);
  if (encNow != encPrev) {
    encAcc += encTable[(encPrev << 2) | encNow];
    encPrev = encNow;
    if (encAcc >= ENC_STEPS || encAcc <= -ENC_STEPS) {
      encAcc = 0;
      beep();
    }
  }
}
