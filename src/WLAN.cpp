#include "WLAN.h"
#include "HTML.h"

WiFiManager wm; // global wm instance
WiFiManagerParameter text_field; 
WiFiManagerParameter animation_field;
WiFiManagerParameter pause_field;

String ssid; 

String getParam(String name){
  //read parameter from server, for customhmtl input
  String value;
  if(wm.server->hasArg(name)) {
    value = wm.server->arg(name);
  }
  return value;
}

void saveParamCallback()
{
    Display& disp = Display::instance();
    disp.scrollText = getParam("textid"); 
    disp.animation  = getParam("animation").toInt();
    disp.pause      = getParam("pauseid").toInt();

    saveConfiguration();
}

void initWLAN()
{
  ssid = String("LED") + String(WIFI_getChipId(),HEX);

	#ifdef CUSTOM_HOSTNAME
		ssid = CUSTOM_HOSTNAME; 
	#endif

	wm.setHostname(ssid.c_str());

	wm.setClass("invert");
	wm.setConfigPortalBlocking(false);
	wm.setConfigPortalTimeout(300);

	if (wm.getWiFiIsSaved())
	{
		if(wm.autoConnect(ssid.c_str(), NULL))
		{
			Serial.println("Connected!");
		}
		else
		{
			Serial.println("Connect failed :( ");
		}
	}
	
	int customFieldLength = 100;
	
	new (&text_field) WiFiManagerParameter("textid", "Text", "Hallo Welt!", customFieldLength,"placeholder=\"Hallo Welt!\"");
	new (&animation_field) WiFiManagerParameter(animationHTML);
	new (&pause_field) WiFiManagerParameter("pauseid", "Pausendauer (in ms)", "1000", customFieldLength,"placeholder=\"1000\"");

	wm.addParameter(&text_field);
	wm.addParameter(&animation_field);
	wm.addParameter(&pause_field);

	wm.setSaveParamsCallback(saveParamCallback);

	std::vector<const char *> menu = {"wifi","info","param","sep","restart","exit"};
	wm.setMenu(menu);

}