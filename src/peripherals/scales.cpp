/* 09:32 15/03/2023 - change triggering comment */
/* 2024/06/30 add support for single load cess, to enable it, define -DSINGLE_LOAD_CELL in extra_defined.ini */
#include "scales.h"
#include "pindef.h"
#include "remote_scales.h"
#if defined(SINGLE_LOAD_CELL)
#include "HX711.h"
#else
#include <HX711_2.h>
#endif

#if defined(SINGLE_LOAD_CELL) //single load cell
namespace {
  class LoadCellSingleton {
  public:
    static HX711& getInstance() {
      static HX711 instance(TIM3);
      return instance;
    }
  private:
    LoadCellSingleton() = default;
    ~LoadCellSingleton() = default;
  };
}
#else
namespace {
  class LoadCellSingleton {
  public:
    static HX711_2& getInstance() {
      static HX711_2 instance(TIM3);
      return instance;
    }
  private:
    LoadCellSingleton() = default;
    ~LoadCellSingleton() = default;
  };
}
#endif

bool hwScalesPresent = false;

#if defined SINGLE_HX711_BOARD
unsigned char scale_clk = OUTPUT;
#else
unsigned char scale_clk = OUTPUT_OPEN_DRAIN;
#endif

void scalesInit(float scalesF1, float scalesF2) {
  hwScalesPresent = false;
  // Forced predicitve scales in case someone with actual hardware scales wants to use them.
  if (FORCE_PREDICTIVE_SCALES) {
    return;
  }

#ifndef DISABLE_HW_SCALES
  auto& loadCells = LoadCellSingleton::getInstance();
  #if defined(SINGLE_LOAD_CELL)
  loadCells.begin(HX711_dout_1, HX711_sck_1, 128U, scale_clk);
  loadCells.set_scale(scalesF1);
  #else
  loadCells.begin(HX711_dout_1, HX711_dout_2, HX711_sck_1, 128U, scale_clk);
  loadCells.set_scale(scalesF1, scalesF2);
  #endif
  loadCells.power_up();

  if (loadCells.wait_ready_timeout(1000, 10)) {
    loadCells.tare(4);
    hwScalesPresent = true;
  }
  else {
    loadCells.power_down();
  }
#endif

  if (!hwScalesPresent && remoteScalesIsPresent()) {
    remoteScalesTare();
  }
}

void scalesTare(void) {
  if (hwScalesPresent) {
    auto& loadCells = LoadCellSingleton::getInstance();
    if (loadCells.wait_ready_timeout(150, 10)) {
      loadCells.tare(4);
    }
  }
  else if (remoteScalesIsPresent()) {
    remoteScalesTare();
  }
}

Measurement scalesGetWeight(void) {
  Measurement currentWeight = Measurement{ .value = 0.f, .millis = 0 };
  if (hwScalesPresent) {
    auto& loadCells = LoadCellSingleton::getInstance();
    if (loadCells.wait_ready_timeout(150, 10)) {
      #if defined(SINGLE_LOAD_CELL)
      float value = loadCells.get_units();
      currentWeight = Measurement{ .value=value, .millis=millis() };
      #else
      float values[2];
      loadCells.get_units(values);
      currentWeight = Measurement{ .value=values[0] + values[1], .millis=millis() };
      #endif
    }
  }
  else if (remoteScalesIsPresent()) {
    currentWeight = remoteScalesGetWeight();
  }
  return currentWeight;
}

bool scalesIsPresent(void) {
  // Forced predicitve scales in case someone with actual hardware scales wants to use them.
  if (FORCE_PREDICTIVE_SCALES) {
    return false;
  }
  return hwScalesPresent || remoteScalesIsPresent();
}

float scalesDripTrayWeight() {
  #if defined(SINGLE_LOAD_CELL)
  long value = 0;
  if (hwScalesPresent) {
    value = LoadCellSingleton::getInstance().read_average(4);
  }
  return ((float)value);
  #else
  long value[2] = {};
  if (hwScalesPresent) {
    LoadCellSingleton::getInstance().read_average(value, 4);
  }
  return ((float)value[0] + (float)value[1]);
  #endif
}
