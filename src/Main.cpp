#include "Main.h"

Encoder enc; 
Display& disp = Display::instance();

void setup()
{
	// UART für Debugging
	Serial.begin(115200);

	// WLAN initialisieren
	initWLAN();

	// Konfiguration aus dem SPIFFS lesen
	readConfiguration();

	// Drehencoder initialisieren
	enc.attachSingleEdge(ENCODER_DT, ENCODER_CLK);
	enc.attachButton(ENCODER_SW);

	// Vernünftigen Ausgangszustand definieren
	state = STATE::SCROLLTEXT;
	enc.setLimits(0, 20, 5);

	// Display initialisieren
	disp.init(ENCODER_SW, enc);
	disp.setDisplayState();
}

void loop()
{
	wm.process();
	disp.render();
	delay(1);
}