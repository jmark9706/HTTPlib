// HTTPlib - helpers
#include "HTTPlib.h"

HTTPhelper::HTTPhelper()
{
};


void HTTPhelper::kvstart(WiFiClient client)
{
	client.print("999");
  client.print(this->httpRequest2);
};
