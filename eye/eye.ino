//Designed by SyncTech Electronic
//Version 1.00 | 1403/06/19
//Website : Sync-tech.ir

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_GC9A01A.h>
#include "FS.h"
#include "SPIFFS.h"

#define TFT_SCK   4
#define TFT_MOSI  6
#define TFT_MISO  -1
#define TFT_CS    7
#define TFT_DC    10
#define TFT_RST   9
#define TFT_BL    -1

#define SRC_W 120
#define SRC_H 120
#define DST_W 240
#define DST_H 240

#define FRAME_COUNT 51
#define FRAME_SIZE (SRC_W * SRC_H * 2) // RGB565

const uint16_t pauseTimeMs = 3000;
const uint16_t normalDelayMs = 33;

Adafruit_GC9A01A tft(TFT_CS, TFT_DC, TFT_RST);
uint16_t frameBuf[SRC_W * SRC_H];
File animFile;

bool isInList(uint8_t frame, const uint8_t *list, size_t listSize) {
  for (size_t i = 0; i < listSize; i++) {
    if (frame == list[i]) return true;
  }
  return false;
}

void playSequence(uint8_t start, uint8_t end, uint8_t repeatCount,
                  const uint8_t *pauseList, size_t pauseCount,
                  const uint8_t *skipList = nullptr, size_t skipCount = 0) {
  for (uint8_t rep = 0; rep < repeatCount; rep++) {
    for (uint8_t frame = start; frame < end; frame++) {
      
      if (skipList && isInList(frame, skipList, skipCount)) {
        Serial.printf("Frame %d - نادیده گرفته شد\n", frame);
        continue;
      }

      animFile.seek(frame * FRAME_SIZE);
      animFile.read((uint8_t*)frameBuf, FRAME_SIZE);

      for (int y = 0; y < DST_H; y++) {
        int srcY = y >> 1;
        uint16_t lineBuf[DST_W];
        for (int x = 0; x < DST_W; x++) {
          int srcX = x >> 1;
          lineBuf[x] = frameBuf[srcY * SRC_W + srcX];
        }
        tft.drawRGBBitmap(0, y, lineBuf, DST_W, 1);
      }

      if (isInList(frame, pauseList, pauseCount)) {
        Serial.printf("Frame %d - مکث %d میلی‌ثانیه\n", frame, pauseTimeMs);
        delay(pauseTimeMs);
      } else {
        Serial.printf("Frame %d - پخش عادی\n", frame);
        delay(normalDelayMs);
      }
    }
  }
}

void setup() {
  Serial.begin(115200);
  if (!SPIFFS.begin(true)) {
    Serial.println("خطا در mount شدن SPIFFS");
    while (true);
  }

  SPI.begin(TFT_SCK, TFT_MISO, TFT_MOSI);
  tft.begin();
  tft.setRotation(0);

  #if TFT_BL >= 0
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);
  #endif

  animFile = SPIFFS.open("/all_frames_crop120.bin", "r");
  if (!animFile) {
    Serial.println("فایل all_frames_crop120.bin یافت نشد");
    while (true);
  }
  Serial.println("شروع نمایش...");
}

void loop() {
  const uint8_t pausesAll[] = {4, 11, 22, 29, 39, 46};

  while (true) {
    playSequence(0, FRAME_COUNT, 1, pausesAll, sizeof(pausesAll));
    playSequence(0, 18, 2, pausesAll, sizeof(pausesAll));
    playSequence(17, 35, 2, pausesAll, sizeof(pausesAll));
    playSequence(34, FRAME_COUNT, 2, pausesAll, sizeof(pausesAll));
  }
}

