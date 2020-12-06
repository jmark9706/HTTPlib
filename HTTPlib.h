// HTTP library
#ifndef HTTPlib
#define HTTPlib
#include <ESP8266WiFi.h>

class HTTPhelper
{public:
	HTTPhelper(WiFiClient client);
	void kvstart(void);
  void kvparm(String key, String pval, uint16_t sep);
  void kvamper(void);
  void kvend(void);
private:
WiFiClient wclient;
const String httpRequest2 = "GET /parms?";
const String httpRequest3 = "&humidity=";
const String httpRequest4 = "\nHTTP/1.1\n"
                           "Host: 10.0.0.151\n"
                           "Connection: close\n\n";
const String ampersand = "&";
};



#endif
