#include <Joystick.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_JOYSTICK,
                   15, 0,                  // Button Count, Hat Switch Count
                   true, true, false,     // X and Y, but no Z Axis
                   false, false, false,   // No Rx, Ry, or Rz
                   false, false,          // No rudder or throttle
                   false, false, false);  // No accelerator, brake, or steering

int lastButtonState = 0;


void sendCommand(int btn) {
  Joystick.setButton(btn, true);
  delay(25);
  Joystick.setButton(btn, false);
}

//Class for rotary encoder
class RotBtn
{
  int aVal;
  int pinALast;
  int pinA;
  int pinB;
  int D;
  int U;

  public:
    RotBtn(int pinD, int pinU, int btnDn, int btnUp)
    {
      pinA = pinD;
      pinB = pinU;
      D = btnDn;
      U = btnUp;
      pinMode (pinA, INPUT);
      pinMode (pinB, INPUT);
      pinALast = digitalRead(pinA);
    }
    void Update() {
      aVal = digitalRead(pinA);
      if (aVal != pinALast) {
        if (digitalRead(pinB) != aVal) {
          sendCommand(D);
        } else {
          sendCommand(U);
        }

      }
      pinALast = aVal;
    }
};

//Class for button
class PushBtn
{
  int aVal;
  int pinALast;
  int pinA;
  int B;

  public:
    PushBtn(int pinD, int btn)
    {
      pinA = pinD;
      B = btn;
      pinMode (pinA, INPUT_PULLUP);
      pinALast = digitalRead(pinA);
    }
    void Update() {
      aVal = digitalRead(pinA);
      if (aVal != pinALast && aVal == LOW) {
          Joystick.setButton(B, true);
      } else if (aVal != pinALast && aVal == HIGH) {
          Joystick.setButton(B, false);}
      pinALast = aVal;
    }
};

//Create buttons and rotary encoders
RotBtn RT1(8, 9, 6, 7);
RotBtn RT2(10, 16, 8, 9);
RotBtn RT3(15, 14, 10, 11);
RotBtn RT4(A0, A1, 13, 12);
PushBtn BTN1(2, 0);
PushBtn BTN2(3, 1);
PushBtn BTN3(4, 2);
PushBtn BTN4(5, 3);
PushBtn BTN5(6, 4);
PushBtn BTN6(7, 5);

void setup() {
  Joystick.begin();
}


void loop() {
  RT1.Update();
  RT2.Update();
  RT3.Update();
  RT4.Update();
  BTN1.Update();
  BTN2.Update();
  BTN3.Update();
  BTN4.Update();
  BTN5.Update();
  BTN6.Update();
}
