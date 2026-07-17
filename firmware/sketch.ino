#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


void setup() {
  pinMode(32, INPUT_PULLUP);
  pinMode(34, INPUT_PULLUP);
  pinMode(35, INPUT_PULLUP);
  pinMode(36, INPUT_PULLUP);
  pinMode(39, INPUT_PULLUP);

  pinMode(5, OUTPUT);

  Wire.begin();
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
  Serial.println(F("SSD1306 allocation failed"));
  for(;;);
  }
  delay(2000);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  // Display static text
  display.println("Scrolling Hello");
  display.display(); 
  delay(100);

}


int freq = 4;
unsigned long lastBeep = 0;


void beep() {
  int duty = 1000 / (freq * 2);
  if (millis() - lastBeep > duty * 2) {
  digitalWrite(5, LOW);
  lastBeep = millis();
  } else if (millis() - lastBeep > duty) {
  digitalWrite(5, HIGH);
  }
}


void loop() {
  beep();

    // Scroll in various directions, pausing in-between:
  display.clearDisplay();
  display.setCursor(0,10);
  display.println(freq);
  display.display(); 


  if (digitalRead(36) == LOW) {
    freq = 16;
  }

  if (digitalRead(39) == LOW) {
    freq = 8;
  }

  if (digitalRead(34) == LOW) {
    freq = 30;
  }

  if (digitalRead(35) == LOW) {
    freq = 2;
  }

  if (digitalRead(32) == LOW) {
    freq = 1;
  }


  Serial.println(digitalRead(34) == LOW);


}