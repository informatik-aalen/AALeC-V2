#include <AALeC-V2.h>
void setup() {
  aalec.init();
}

void loop() {
  aalec.set_led(!aalec.get_led());
  delay(500);
}
