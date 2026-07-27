#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>

// OLED I2C pins for ESP32
#define OLED_SDA_PIN 21
#define OLED_SCL_PIN 22

// OLED I2C address (7-bit)
// Common addresses: 0x3C or 0x3D
#define OLED_I2C_ADDRESS_7BIT 0x3C



U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled(U8G2_R0, U8X8_PIN_NONE);


uint32_t counter = 0;
unsigned long lastUpdateMs = 0;
static constexpr unsigned long UPDATE_INTERVAL_MS = 1000;


void drawScreen(uint32_t value) {
 oled.clearBuffer();
 oled.setFont(u8g2_font_6x12_tf);


 oled.drawStr(0, 16, "Hello from ESP32");


 char line2[32];
 snprintf(line2, sizeof(line2), "Counter: %lu", static_cast<unsigned long>(value));
 oled.drawStr(0, 34, line2);


 oled.sendBuffer();
}


void setup() {
 Wire.begin(OLED_SDA_PIN, OLED_SCL_PIN);


 // U8g2 expects 8-bit I2C address
 oled.setI2CAddress(OLED_I2C_ADDRESS_7BIT << 1);
 oled.begin();


 drawScreen(counter);
 lastUpdateMs = millis();
}


void loop() {
 unsigned long now = millis();
 if (now - lastUpdateMs >= UPDATE_INTERVAL_MS) {
   lastUpdateMs = now;
   counter++;
   drawScreen(counter);
 }
}



