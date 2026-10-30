#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

// Pins
#define PIN_BUZZER      D7
#define PIN_LED         D8
#define PIN_OLED_SCL    D10
#define PIN_OLED_SDA    D9
#define PIN_BTN1        D5
#define PIN_BTN2        D4
#define PIN_BTN3        D3
#define PIN_ENC_BTN     D6
#define PIN_ENC_LEFT    D1
#define PIN_ENC_RIGHT   D2

// Display
#define SCREEN_WIDTH    128
#define SCREEN_HEIGHT   32
#define OLED_ADDR       0x3C

// Beep settings
#define BEEP_FREQ       2000
#define BEEP_MS         30

// Encoder transitions per detent (usually 4, some encoders use 2)
#define ENC_STEPS       4

// Bluetooth
#define BT_NAME         "Octoglow Macro Cloud"
#define BT_HOLD_MS      5000

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const uint8_t buttonPins[] = {PIN_BTN1, PIN_BTN2, PIN_BTN3, PIN_ENC_BTN};
const uint8_t buttonCount = sizeof(buttonPins) / sizeof(buttonPins[0]);
const uint8_t ENC_BTN_INDEX = 3;

bool lastState[4];
unsigned long lastChange[4];
const unsigned long debounceMs = 20;

uint8_t encPrev = 0;
int8_t encAcc = 0;
const int8_t encTable[16] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};

unsigned long encBtnPressedAt = 0;
bool bluetoothOn = false;

void beep() {
  tone(PIN_BUZZER, BEEP_FREQ, BEEP_MS);
}

void printCentered(const char* text, int16_t y) {
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
  display.setCursor((SCREEN_WIDTH - w) / 2, y);
  display.print(text);
}

void showLogo() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  printCentered("Octoglow", 8);
  display.display();
}

void showBluetoothMode() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  printCentered("Bluetooth", 0);
  printCentered("Mode", 16);
  display.display();
}

void startBluetooth() {
  BLEDevice::init(BT_NAME);
  BLEServer* server = BLEDevice::createServer();
  BLEAdvertising* advertising = BLEDevice::getAdvertising();
  advertising->setScanResponse(true);
  advertising->start();
  bluetoothOn = true;
  showBluetoothMode();
  tone(PIN_BUZZER, 2500, 300);
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

  Wire.begin(PIN_OLED_SDA, PIN_OLED_SCL);

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
        if (i == ENC_BTN_INDEX) {
          encBtnPressedAt = now;
        }
      } else if (i == ENC_BTN_INDEX) {
        encBtnPressedAt = 0;
      }
    }
  }

  // Long press on the encoder button starts Bluetooth
  if (!bluetoothOn && encBtnPressedAt != 0 && lastState[ENC_BTN_INDEX] == LOW &&
      now - encBtnPressedAt >= BT_HOLD_MS) {
    encBtnPressedAt = 0;
    startBluetooth();
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
