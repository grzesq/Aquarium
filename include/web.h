#pragma once

#include "WiFi.h"
#include "structs.h"
#include "config.h"

class Web
{
    public:
       Web(Config& c);

       void request(WiFiClient& client);

    private:
        Config* conf;
        void processGet(String get);
        void parseGet(String get, bool log);
        String getHtml();
        String getRawHtml();
};