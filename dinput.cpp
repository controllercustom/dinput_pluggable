/*
 * MIT License
 *
 * Copyright (c) 2024 controllercustom@myyahoo.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include <Arduino.h>

#include "dinput.h"

#if defined(_USING_HID)

// Single Report (ID=04) descriptor
// Joystick with 4 8-bit axes, 1 hat/dpad, 12 buttons
static const uint8_t desc_hid_report [] PROGMEM = {
  0x05,0x01,0x09,0x04,0xA1,0x01,0x85,0x04,0xA1,0x02,0x75,0x08,0x95,0x04,0x15,
  0x00,0x26,0xFF,0x00,0x35,0x00,0x46,0xFF,0x00,0x09,0x30,0x09,0x31,0x09,0x32,
  0x09,0x35,0x81,0x02,0x75,0x04,0x95,0x01,0x25,0x07,0x46,0x3B,0x01,0x65,0x14,
  0x09,0x39,0x81,0x42,0x65,0x00,0x75,0x01,0x95,0x0C,0x25,0x01,0x45,0x01,0x05,
  0x09,0x19,0x01,0x29,0x0C,0x81,0x02,0x06,0x00,0xFF,0x75,0x01,0x95,0x10,0x25,
  0x01,0x45,0x01,0x09,0x01,0x81,0x02,0xC0,0xA1,0x02,0x75,0x08,0x95,0x07,0x46,
  0xFF,0x00,0x26,0xFF,0x00,0x09,0x02,0x91,0x02,0xC0,0xC0
};

DIGamepad::DIGamepad(void) {
  static HIDSubDescriptor node(desc_hid_report, sizeof(desc_hid_report));
  HID().AppendDescriptor(&node);
  startMillis = millis();
  memset(&_report, 0x00, sizeof(_report));
  _report.leftXAxis = _report.leftYAxis = 0x80;
  _report.rightXAxis = _report.rightYAxis = 0x80;
  _report.hat = GAMEPAD_DPAD_CENTERED;
}

void DIGamepad::begin(void) {
  end();
}

void DIGamepad::loop(void) {
  if (startMillis != millis()) {
    sendReport();
    startMillis = millis();
  }
}

void DIGamepad::end(void) {
  memset(&_report, 0x00, sizeof(_report));
  _report.leftXAxis = _report.leftYAxis = 0x80;
  _report.rightXAxis = _report.rightYAxis = 0x80;
  _report.hat = GAMEPAD_DPAD_CENTERED;
  sendReport();
}

void DIGamepad::sendReport() {
  HID().SendReport(4, (void *)&_report, sizeof(_report));
}

void DIGamepad::press(uint8_t b) {
  if (b > BUTTON_11) b = BUTTON_11;
  _report.buttons |= (uint16_t)(1 << b);
}

void DIGamepad::release(uint8_t b) {
  if (b > BUTTON_11) b = BUTTON_11;
  _report.buttons &= ~((uint16_t)(1 << b));
}

// The direction pad is limited to 8 directions plus centered. This means
// some combinations of 4 dpad buttons are not valid and cannot be sent.
// Button down = true(1)
// Valid: Any 1 button down, any 2 adjacent buttons down, no buttons down
// Invalid: all other combinations
void DIGamepad::dPad(bool up, bool down, bool left, bool right) {
  static const Direction_t BITS2DIR[16] = {
    GAMEPAD_DPAD_CENTERED,    // 0000
    GAMEPAD_DPAD_RIGHT,       // 0001
    GAMEPAD_DPAD_LEFT,        // 0010
    GAMEPAD_DPAD_CENTERED,    // 0011
    GAMEPAD_DPAD_DOWN,        // 0100
    GAMEPAD_DPAD_DOWN_RIGHT,  // 0101
    GAMEPAD_DPAD_DOWN_LEFT,   // 0110
    GAMEPAD_DPAD_CENTERED,    // 0111
    GAMEPAD_DPAD_UP,          // 1000
    GAMEPAD_DPAD_UP_RIGHT,    // 1001
    GAMEPAD_DPAD_UP_LEFT,     // 1010
    GAMEPAD_DPAD_CENTERED,    // 1011
    GAMEPAD_DPAD_CENTERED,    // 1100
    GAMEPAD_DPAD_CENTERED,    // 1101
    GAMEPAD_DPAD_CENTERED,    // 1110
    GAMEPAD_DPAD_CENTERED     // 1111
  };
  uint8_t dpad_bits = (up << 3) | (down << 2) | (left << 1) | (right << 0);
  _report.hat = BITS2DIR[dpad_bits];
}

#endif /* defined(_USING_HID) */
