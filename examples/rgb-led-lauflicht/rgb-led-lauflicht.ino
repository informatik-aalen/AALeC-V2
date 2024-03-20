#include <AALeC-V2.h>
void setup() {
  aalec.init();
}

void loop() {
  
  static uint32_t nr = 0;
  
  aalec.set_rgb_strip(nr++, c_off);
  aalec.set_rgb_strip(nr, c_red);
  delay(aalec.get_analog());
}
