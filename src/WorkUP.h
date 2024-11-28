#pragma once
#include <Arduino.h>


class WorkUP {
  private:
    uint32_t _up;
    uint32_t _tmr;
    uint16_t _tmrDelay;
    uint32_t _periodTimer;
    uint16_t _speed;
    bool _run;
    bool _pause;
    bool _millisMode = false;

    String addSymbNull(uint8_t t) {
      String s = "";
      if (t <= 9) s = String("0") + String(t);
      else s = String(t);
      return s;
    }

    uint32_t divideBy24(uint32_t x) {
        return x / 24; // Множник для ділення на 24
    }

    uint32_t divideBy60(uint32_t x) {
        return x / 60; // Швидке ділення на 60
    }

    uint32_t remainderBy60(uint32_t x) {
        uint32_t quotient = divideBy60(x);
        return x - (quotient * 60); // Залишок від ділення
    }

    uint32_t remainderBy24(uint32_t x) {
        uint32_t quotient = divideBy24(x);
        return x - (quotient * 24); // Залишок від ділення
    }

    uint32_t _getUp()
    {
      return (_millisMode) ? millis() / 1000 : _up;
    }
  public:
    WorkUP() {
      _speed = 1;
      _periodTimer = 1000;
    }

    void useMillisTimeAsUptime() // Max 24 days Uptime !!!!
    {
      _millisMode = true;
    }

    void begin() {
      _run = true;
      _pause = false;
      _up = 0;
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
      return (uint8_t)remainderBy60(_getUp());
    }

    uint8_t getMinutes() {
      uint32_t res = divideBy60(_getUp());
      res = remainderBy60(res);
      return (uint8_t)res;
    }

    uint8_t getHours() {
      uint32_t res = divideBy60(_getUp());
      res = divideBy60(res);
      res = remainderBy24(res);
      return (uint8_t)res;
    }

    uint16_t getDays() {
      uint32_t res = divideBy60(_getUp());
      res = divideBy60(res);
      res = divideBy24(res);
      return (uint16_t)res;
    }

    uint32_t getUpSecunds() {
      return _getUp();
    }

    uint32_t getUpMinutes() {
      return divideBy60(_getUp());
    }

    uint32_t getUpHours() {
      return divideBy60(getUpMinutes());
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

    void tick() {
      if (_millisMode) return;
      if (millis() - _tmr >= _periodTimer) {
        _up += _speed;
        do {
          _tmr += _periodTimer;
          if (_tmr < _periodTimer) break;
        } while (_tmr < millis() - _periodTimer);
      } 
    }

    void delayAsync1Sec(void (*_callback)())
    {
      uint16_t timerLeft = millis() - _tmrDelay;
      uint16_t prdDelay1 = 1024;
      if (timerLeft >= prdDelay1) {
        _tmrDelay += prdDelay1 * (timerLeft >> 10);
        _callback();
      }
    }
};

extern WorkUP WUP;