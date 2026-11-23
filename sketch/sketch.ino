// ESP32-S2 Dev Board - 5 bulb light pattern
// Bulbs on ports 1-5 (assumed to be GPIO 1-5). Edit BULB_PINS if wired differently.
// If your bulbs/relay board are active-LOW, set ACTIVE_LEVEL to LOW.

const uint8_t BULB_PINS[] = {1, 2, 3, 4, 5};
const uint8_t BULB_COUNT = sizeof(BULB_PINS) / sizeof(BULB_PINS[0]);

const uint8_t ACTIVE_LEVEL = HIGH;
const uint8_t INACTIVE_LEVEL = (ACTIVE_LEVEL == HIGH) ? LOW : HIGH;

const uint16_t STEP_DELAY_MS = 250;   // speed of chase / fill steps
const uint16_t BLINK_DELAY_MS = 400;  // speed of all-blink step

void setBulb(uint8_t index, bool on) {
  digitalWrite(BULB_PINS[index], on ? ACTIVE_LEVEL : INACTIVE_LEVEL);
}

void allBulbs(bool on) {
  for (uint8_t i = 0; i < BULB_COUNT; i++) setBulb(i, on);
}

// Pattern 1: single bulb chases 1 -> 5
void chaseForward() {
  for (uint8_t i = 0; i < BULB_COUNT; i++) {
    allBulbs(false);
    setBulb(i, true);
    delay(STEP_DELAY_MS);
  }
}

// Pattern 2: single bulb chases 5 -> 1
void chaseBackward() {
  for (int8_t i = BULB_COUNT - 1; i >= 0; i--) {
    allBulbs(false);
    setBulb(i, true);
    delay(STEP_DELAY_MS);
  }
}

// Pattern 3: bulbs turn on one by one (1 -> 5), then off one by one (5 -> 1)
void fillAndEmpty() {
  allBulbs(false);
  for (uint8_t i = 0; i < BULB_COUNT; i++) {
    setBulb(i, true);
    delay(STEP_DELAY_MS);
  }
  for (int8_t i = BULB_COUNT - 1; i >= 0; i--) {
    setBulb(i, false);
    delay(STEP_DELAY_MS);
  }
}

// Pattern 4: all bulbs blink together 3 times
void blinkAll() {
  for (uint8_t n = 0; n < 3; n++) {
    allBulbs(true);
    delay(BLINK_DELAY_MS);
    allBulbs(false);
    delay(BLINK_DELAY_MS);
  }
}

void setup() {
  for (uint8_t i = 0; i < BULB_COUNT; i++) {
    pinMode(BULB_PINS[i], OUTPUT);
  }
  allBulbs(false);
}

void loop() {
  chaseForward();
  chaseBackward();
  fillAndEmpty();
  blinkAll();
}
