#include <AALeC-V2.h>

void setup() {
  aalec.init();
}

void loop() {
  static uint32_t n = 0;
  aalec.set_rgb_strip(0, n++);
  delay(10);
}
