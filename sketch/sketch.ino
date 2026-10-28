// ESP32-S2 - 4 LED blink patterns on GPIO 1, 2, 3, 4
// Patterns cycle automatically, each running for a few seconds.

const uint8_t LED_PINS[] = {1, 2, 3, 4};
const uint8_t LED_COUNT = sizeof(LED_PINS) / sizeof(LED_PINS[0]);

// Write the same state to all LEDs
void setAll(bool state) {
  for (uint8_t i = 0; i < LED_COUNT; i++) {
    digitalWrite(LED_PINS[i], state ? HIGH : LOW);
  }
}

// Pattern 1: all LEDs blink together
void patternAllBlink(uint8_t times, uint16_t delayMs) {
  for (uint8_t t = 0; t < times; t++) {
    setAll(true);
    delay(delayMs);
    setAll(false);
    delay(delayMs);
  }
}

// Pattern 2: chase left to right, then back (ping-pong)
void patternChase(uint8_t rounds, uint16_t delayMs) {
  for (uint8_t r = 0; r < rounds; r++) {
    for (int8_t i = 0; i < LED_COUNT; i++) {
      setAll(false);
      digitalWrite(LED_PINS[i], HIGH);
      delay(delayMs);
    }
    for (int8_t i = LED_COUNT - 2; i > 0; i--) {
      setAll(false);
      digitalWrite(LED_PINS[i], HIGH);
      delay(delayMs);
    }
  }
  setAll(false);
}

// Pattern 3: alternate LEDs (1,3 on / 2,4 on)
void patternAlternate(uint8_t times, uint16_t delayMs) {
  for (uint8_t t = 0; t < times; t++) {
    for (uint8_t i = 0; i < LED_COUNT; i++) {
      digitalWrite(LED_PINS[i], (i % 2 == 0) ? HIGH : LOW);
    }
    delay(delayMs);
    for (uint8_t i = 0; i < LED_COUNT; i++) {
      digitalWrite(LED_PINS[i], (i % 2 == 0) ? LOW : HIGH);
    }
    delay(delayMs);
  }
  setAll(false);
}

// Pattern 4: fill up one by one, then turn off one by one
void patternFillUp(uint8_t rounds, uint16_t delayMs) {
  for (uint8_t r = 0; r < rounds; r++) {
    setAll(false);
    for (uint8_t i = 0; i < LED_COUNT; i++) {
      digitalWrite(LED_PINS[i], HIGH);
      delay(delayMs);
    }
    for (int8_t i = LED_COUNT - 1; i >= 0; i--) {
      digitalWrite(LED_PINS[i], LOW);
      delay(delayMs);
    }
  }
}

// Pattern 5: outside-in / inside-out
void patternOutsideIn(uint8_t rounds, uint16_t delayMs) {
  for (uint8_t r = 0; r < rounds; r++) {
    setAll(false);
    digitalWrite(LED_PINS[0], HIGH);
    digitalWrite(LED_PINS[LED_COUNT - 1], HIGH);
    delay(delayMs);
    setAll(false);
    digitalWrite(LED_PINS[1], HIGH);
    digitalWrite(LED_PINS[LED_COUNT - 2], HIGH);
    delay(delayMs);
  }
  setAll(false);
}

// Pattern 6: random sparkle
void patternRandom(uint8_t steps, uint16_t delayMs) {
  for (uint8_t s = 0; s < steps; s++) {
    for (uint8_t i = 0; i < LED_COUNT; i++) {
      digitalWrite(LED_PINS[i], random(2));
    }
    delay(delayMs);
  }
  setAll(false);
}

void setup() {
  for (uint8_t i = 0; i < LED_COUNT; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    digitalWrite(LED_PINS[i], LOW);
  }
  randomSeed(esp_random());
}

void loop() {
  patternAllBlink(5, 250);
  delay(300);

  patternChase(3, 120);
  delay(300);

  patternAlternate(6, 200);
  delay(300);

  patternFillUp(3, 150);
  delay(300);

  patternOutsideIn(6, 200);
  delay(300);

  patternRandom(20, 120);
  delay(500);
}
