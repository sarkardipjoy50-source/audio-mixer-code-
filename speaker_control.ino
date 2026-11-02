#include <Wire.h>

// বাটন পিন ডিফাইন
const int customModeBtn = 2; // কাস্টম সেটিং বাটন
const int defaultModeBtn = 3; // ডিফোল্ট সেটিং (রিসেট) বাটন

// PT2314 I2C এড্রেস
#define PT2314_ADDR 0x44

void setup() {
  Wire.begin();
  pinMode(customModeBtn, INPUT_PULLUP);
  pinMode(defaultModeBtn, INPUT_PULLUP);

  // শুরুতে ডিফোল্ট সেটিং লোড হবে
  setAudioDefault();
}

void loop() {
  // যদি কাস্টম বাটন প্রেস করা হয়
  if (digitalRead(customModeBtn) == LOW) {
    setAudioCustom();
    delay(300); // Debounce delay
  }

  // যদি ডিফোল্ট/রিসেট বাটন প্রেস করা হয়
  if (digitalRead(defaultModeBtn) == LOW) {
    setAudioDefault();
    delay(300); 
  }
}

// ----------------- ১. ডিফোল্ট সেটিং -----------------
void setAudioDefault() {
  Wire.beginTransmission(PT2314_ADDR);
  
  // Volume: Mid (Default)
  Wire.write(0x00 | 20); 
  // Bass: Flat (0 dB)
  Wire.write(0x60 | 7); 
  // Treble: Flat (0 dB)
  Wire.write(0x70 | 7); 
  
  Wire.endTransmission();
}

// ----------------- ২. কাস্টমাইজড সেটিং -----------------
void setAudioCustom() {
  Wire.beginTransmission(PT2314_ADDR);
  
  // Volume: High
  Wire.write(0x00 | 10); 
  // Bass: Boosted (+8 dB)
  Wire.write(0x60 | 12); 
  // Treble: Boosted (+6 dB)
  Wire.write(0x70 | 10); 
  
  Wire.endTransmission();
}
