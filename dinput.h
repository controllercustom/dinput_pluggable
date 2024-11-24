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
/*
  dinput.h
*/
#ifndef DINPUT_H_
#define DINPUT_H_

#include "HID.h"

#if !defined(_USING_HID)

#warning "Using legacy HID core (non pluggable)"

#else

// Dpad directions
typedef uint8_t Direction_t;
#define GAMEPAD_DPAD_UP  0
#define GAMEPAD_DPAD_UP_RIGHT 1
#define GAMEPAD_DPAD_RIGHT 2
#define GAMEPAD_DPAD_DOWN_RIGHT 3
#define GAMEPAD_DPAD_DOWN 4
#define GAMEPAD_DPAD_DOWN_LEFT 5
#define GAMEPAD_DPAD_LEFT 6
#define GAMEPAD_DPAD_UP_LEFT 7
#define GAMEPAD_DPAD_CENTERED 0xF

enum Buttons {
  BUTTON_0 = 0,
  BUTTON_1,
  BUTTON_2,
  BUTTON_3,
  BUTTON_4,
  BUTTON_5,
  BUTTON_6,
  BUTTON_7,
  BUTTON_8,
  BUTTON_9,
  BUTTON_10,
  BUTTON_11,
};

#define ATTRIBUTE_PACKED  __attribute__((packed, aligned(1)))

// Gamepad with 4 8-bit axes, 1 hat/dpad, 12 buttons
typedef struct ATTRIBUTE_PACKED {
  uint8_t leftXAxis;
  uint8_t leftYAxis;
  uint8_t rightXAxis;
  uint8_t rightYAxis;
  uint16_t hat:4;
  uint16_t buttons:12;
} HID_GamepadReport_Data_t;

class DIGamepad {
  public:
    DIGamepad(void);

    void begin(void);
    void end(void);
    void loop(void);
    void sendReport();
    void press(uint8_t b);
    void release(uint8_t b);
    inline void releaseAll(void) { _report.buttons = 0; }
    inline void buttons(uint16_t b) { _report.buttons = b; }
    inline void leftXAxis(uint8_t a) { _report.leftXAxis = a; }
    inline void leftYAxis(uint8_t a) { _report.leftYAxis = a; }
    inline void rightXAxis(uint8_t a) { _report.rightXAxis = a; }
    inline void rightYAxis(uint8_t a) { _report.rightYAxis = a; }
    inline void dPad(Direction_t d) { _report.hat = constrain(d, 0, 15); }
    void dPad(bool up, bool down, bool left, bool right);

  protected:
    HID_GamepadReport_Data_t _report;
    uint32_t startMillis;
};

#endif
#endif  // DINPUT_H_
