// HTTPlib - helpers
#include "HTTPlib.h"

HTTPhelper::HTTPhelper(WiFiClient client)
{ wclient=client;
};


void HTTPhelper::kvstart()
{

  wclient.print(this->httpRequest2);
};
void HTTPhelper::kvparm(String key, String pval)
{
  wclient.print(key);
  wclient.print("=");
  wclient.print(pval);
}
