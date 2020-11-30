// HTTP library
#ifndef HTTPlib
#define HTTPlib
#include <ESP8266WiFi.h>

class HTTPhelper
{public:
	HTTPhelper();
	void kvstart(WiFiClient client);
private:
const String httpRequest2 = "GET /parms?temp=";
const String httpRequest3 = "&humidity=";
const String httpRequest4 = "\nHTTP/1.1\n"
                           "Host: 10.0.0.151\n"
                           "Connection: close\n\n";
};



#endif
