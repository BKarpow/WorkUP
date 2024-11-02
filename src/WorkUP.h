#pragma once
#include <Arduino.h>


class WorkUP {
  private:
    uint32_t _up;
    uint32_t _tmr;
    uint16_t _speed;
    bool _run;
    bool _pause;

    String addSymbNull(uint8_t t) {
      String s = "";
      if (t <= 9) s = String("0") + String(t);
      else s = String(t);
      return s;
    }
  public:
    WorkUP() {
      _speed = 1;
    }

    void setSpeed(uint8_t speed) {
      _speed = speed;
    }

    void begin() {
      _run = true;
      _pause = false;
      _up = 0;
      _speed = 1;
    }

    void end() {
      _run = false;
      _up = 0;
    }

    void pause() {
      _pause = true;
    }

    void start() {
      _run = true;
      _pause = false;
    }

    uint8_t getSecunds() {
      return _up % 60;
    }

    uint8_t getMinutes() {
      return (_up / 60) % 60;
    }

    uint8_t getHours() {
      return (_up / 60 / 60) % 24;
    }

    uint16_t getDays() {
      return (_up / 60 / 60 / 24);
    }

    uint32_t getUpSecunds() {
      return _up;
    }

    uint32_t getUpMinutes() {
      return _up / 60;
    }

    uint32_t getUpHours() {
      return getUpMinutes() / 60;
    }

    String getUpString() {
      String s = "";
      if (getDays() > 0) s += String(getDays()) + String("d ");
      s +=    addSymbNull(getHours()) +
              String(":") +
              addSymbNull(getMinutes()) + 
              String(":") + 
              addSymbNull(getSecunds());
      return s;
    }

    String strfWorkUpTime(String format = "%d %h:%m:%s") {
      format.replace("%d", String(getDays()) );
      format.replace("%h", String(getHours()) );
      format.replace("%m", String(getMinutes()) );
      format.replace("%s", String(getSecunds()) );
      return format;
    }

    bool tick() {
      if (_run && !_pause && millis() - _tmr >= 1000ul) {
        _tmr = millis();
        _up += _speed;
        return true;
      } 
      return false;
    }
};

extern WorkUP WUP;