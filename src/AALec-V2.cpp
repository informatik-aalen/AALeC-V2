#include <Arduino.h>
#include <AALeC-V2.h>
//#include <Adafruit_NeoPixel.h>
#include <SimpleDHT.h>
//#include <SH1106Wire>

//#include "SSD1306.h"


void ICACHE_RAM_ATTR AALeC_V2_ISR_DREH() {
	static int16_t val, z, n;
	const static int8_t delta[4][4] = {
		{0, 1, 2, 0},
		{0, 1, 0, 3},
		{0, 0, 2, 3},
		{0, 1, 2, 3}
	},
	lambda[4][4] = {
		{  0,  1, -1,  0},
		{ -1,  0,  0,  1},
		{  1,  0,  0, -1},
		{  0, -1,  1,  0}
	};
	noInterrupts();
	val = ~GPIO_REG_READ(GPIO_IN_ADDRESS) >> PIN_ENCODER_TRACK_1 & 3;
	n += lambda[z][val], z = delta[z][val];
	if (z == 0) {
		if (n == 4)
			aalec.drehgeber_int--;
		else if (n == -4)
			aalec.drehgeber_int++;
		n = 0;
	}
	interrupts();
}

c_AALeC_V2::c_AALeC_V2() {
}


void c_AALeC_V2::init() {
	
	pinMode(PIN_BEEPER, OUTPUT);
	pinMode(PIN_LED_RESET, OUTPUT);
	pinMode(PIN_BUTTON, INPUT_PULLUP);
	pinMode(PIN_ENCODER_TRACK_1, INPUT_PULLUP);
	pinMode(PIN_ENCODER_TRACK_2, INPUT_PULLUP);
	
	GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS, 0xFFFF);
	attachInterrupt(PIN_ENCODER_TRACK_1, AALeC_V2_ISR_DREH, CHANGE);
	attachInterrupt(PIN_ENCODER_TRACK_2, AALeC_V2_ISR_DREH, CHANGE);
	
	Serial.begin(115200);
	while (!Serial)
		delay(100);
	Serial.println("AALeC init");
	Serial.flush();
	
	Wire.begin();
	strip = new Adafruit_NeoPixel(5, PIN_RGB_STRIP, NEO_GRB + NEO_KHZ800);
	//strip = new NeoPixel<NeoRgbFeature, NeoEsp8266Uart800KbpsMethod>(3, PIN_RGB_STRIP);
	strip->begin();
	strip->clear();
	for (int i = 0; i < 5; i++)
		set_rgb_strip(i, 0, 0, 0);
	strip->show();
	
	
	display.init();
	display.flipScreenVertically();
	display.setFont(ArialMT_Plain_10);
	display.setTextAlignment(TEXT_ALIGN_LEFT);
	
}

const char * c_AALeC_V2::id() {
	const static String myId = "AALeC-" + String(ESP.getChipId(), HEX);
	return myId.c_str();
}

void c_AALeC_V2::set_rgb_strip(int led, unsigned int x) {
    uint16_t r = x % 768, g = (x + 256) % 768, b = (x + 512) % 768;
	set_rgb_strip(led,
           (r < 256) ? r : ((r < 512) ? 511 - r : 0),
           (g < 256) ? g : ((g < 512) ? 511 - g : 0),
           (b < 256) ? b : ((b < 512) ? 511 - b : 0)
      );
}



void c_AALeC_V2::set_rgb_strip(int led, uint8_t r, uint8_t g, uint8_t b) {
	strip->setPixelColor(led % 5, strip->Color(r, g, b));
	strip->show();
}


void c_AALeC_V2::set_rgb_strip(int led, const RgbColor & c) {
	set_rgb_strip(led, c.r, c.g, c.b);
}




void c_AALeC_V2::set_rgb_strip(const RgbColor * c) {
	for (int i = 0; i < 5; i++)
		strip->setPixelColor(i, strip->Color(c[i].r, c[i].g, c[i].b));
	strip->show();
}


void c_AALeC_V2::set_led(int a) {
	digitalWrite(PIN_LED_RESET, a);
}


int c_AALeC_V2::get_led() {
	return digitalRead(PIN_LED_RESET);
}


void c_AALeC_V2::dim_led(int a) {
	analogWrite(PIN_LED_RESET, a);
}


int c_AALeC_V2::get_button() {
	return  ~GPIO_REG_READ(GPIO_IN_ADDRESS)  & 1;
}


int c_AALeC_V2::get_rotate() {
	return drehgeber_int;
}


int c_AALeC_V2::rotate_changed() {
	int rc = 0;
	if (drehgeber_int !=drehgeber_int_alt)
		rc = 1, drehgeber_int_alt = drehgeber_int;
	return rc;
}


void c_AALeC_V2::reset_rotate() {
	drehgeber_int = 0;
}


uint8_t c_AALeC_V2::get_temp() {
	dht11_mess();
	return temp_int;
}

uint8_t c_AALeC_V2::get_humidity() {
	dht11_mess();
	return hum_int;
}


uint16_t c_AALeC_V2::get_analog() {
	return analogRead(A0);
}


void c_AALeC_V2::clear_display() {
	display.clear();
}


void c_AALeC_V2::play(unsigned int f) {
	if (f)
	tone(PIN_BEEPER, f);
	else
	noTone(PIN_BEEPER);
}


void c_AALeC_V2::play(unsigned int f, unsigned int dur) {
	tone(PIN_BEEPER, f, dur);
}

void c_AALeC_V2::dht11_mess() {
	uint32_t t = millis();
	if (t - last_dht11 >= 1000) {
		dht11.read(PIN_DHT11, &temp_int, &hum_int, NULL);
		last_dht11 = t;
	}
}

c_AALeC_V2 aalec;
