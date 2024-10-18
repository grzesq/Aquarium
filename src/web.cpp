#include <Arduino.h>
#include <web.h>
#include <structs.h>

Web::Web(Config& c)
{
    conf = &c;
}

void Web::request(WiFiClient& client)
{
    String currentLine = "";                // make a String to hold incoming 
    short line = 0;
    unsigned long currMillis = millis();
    
    Serial.println("Request start");
    
    while (client.connected() && millis() < currMillis + (2000*60)) 
    {   
        // loop while the client's connected
        if (client.available()) 
        {  
            // if there's bytes to read from the client,
            char c = client.read();             
            //Serial.write(c);
            if (c == '\n') 
            {
                if (currentLine.length() == 0) 
                {
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-type:text/html");
                    client.println("Connection: close");
                    client.println();

                    client.write(getHtml().c_str());
                    break;
                } 
                else {
                    if (line==0)
                    {
                        processGet(currentLine);
                    }
                    currentLine = "";
                    line++;
                }
            } else if (c != '\r') 
            {  // if you got anything else but a carriage return character,
                currentLine += c;      // add it to the end of the currentLine
            }
        }
    }

    client.stop();
    Serial.println("Client disconnected.");
    Serial.println();
}

String Web::getHtml()
{
    String html = getRawHtml();
    
    WorkTime t = conf->getWhite1();
    html.replace("_W1B_", String(t.BH)+":"+String(t.BM));
    html.replace("_W1E_", String(t.EH)+":"+String(t.EM));
    html.replace("_W1P_", String(t.P));

    t = conf->getWhite2();
    html.replace("_W2B_", String(t.BH)+":"+String(t.BM));
    html.replace("_W2E_", String(t.EH)+":"+String(t.EM));
    html.replace("_W2P_", String(t.P));

    t = conf->getFull();
    html.replace("_FB_", String(t.BH)+":"+String(t.BM));
    html.replace("_FE_", String(t.EH)+":"+String(t.EM));
    html.replace("_FP_", String(t.P));

    t = conf->getCo2();
    html.replace("_CB_", String(t.BH)+":"+String(t.BM));
    html.replace("_CE_", String(t.EH)+":"+String(t.EM));

    return html;
}

void Web::processGet(String get)
{
    parseGet(get, true);
}

void Web::parseGet(String get, bool log)
{
/*
GET /wh2?B=12%3A30&E=21%3A30&P=50 HTTP/1.1
*/
    WorkTime wt;

    String req = get.substring(5,8);
    String bh = get.substring(11,13);
    String bm = get.substring(16,18);
    String eh = get.substring(21,23);
    String em = get.substring(26,28);
    String p = get.substring(31,33);

    wt.BH = bh.toInt();
    wt.BM = bm.toInt();
    wt.EH = eh.toInt();
    wt.EM = em.toInt();
    wt.P =  p.toInt();

    Serial.print("Req: ");
    Serial.println(req);

    if (req == "wh1")
    {
        conf->setWhite1(wt);
    } 
    else if (req == "wh2")
    {
        conf->setWhite2(wt);
    }
    else if (req == "fsp")
    {
        conf->setFull(wt);
    }
    else if (req == "co2")
    {
        conf->setCo2(wt);
    }

    if (req == "wh1" || req == "wh2" || req == "fsp" || req == "co2")
    {
        if (log)
        {
            Serial.print("GET ->");
            Serial.println(get);

            Serial.print("Req: ");
            Serial.println(req);

            Serial.print("Start: ");
            Serial.print(bh);
            Serial.print(":");
            Serial.println(bm);

            Serial.print("End: ");
            Serial.print(eh);
            Serial.print(":");
            Serial.println(em);

            if (req != "co2")
            {
                Serial.print("Pow: ");
                Serial.println(p);
                Serial.println();
            }
        }
    }
}

String Web::getRawHtml()
{
return PROGMEM R"rawliteral(
    <!DOCTYPE HTML><html><head>
    <style>
    table, th, td {  border: 1px solid black;  border-collapse: collapse; }
    </style></head><body margin:15px;padding:15px>
    <h3>White 1</h3><form action="/wh1">
    <table><tr><th>Start</th><th>Stop</th><th>Moc %</th><th></th></tr><tr>
    <td> <input name="B" type="text" value="_W1B_"></td><td> <input name="E" type="text" value="_W1E_"></td>
    <td> <input name="P" type="text" value="_W1P_"></td><td> <button type="submit">Set</button></td></tr>
    </table></form>
    <h3>White 2</h3><form action="/wh2">
    <table><tr><th>Start</th><th>Stop</th><th>Moc %</th><th></th></tr><tr>
    <td> <input name="B" type="text" value="_W2B_"></td><td> <input name="E" type="text" value="_W2E_"></td>
    <td> <input name="P" type="text" value="_W2P_"></td><td> <button type="submit">Set</button></td></tr>
    </table></form>
    <h3>Full spectrum</h3><form action="/fsp">
    <table><tr><th>Start</th><th>Stop</th><th>Moc %</th><th></th></tr><tr>
    <td> <input name="B" type="text" value="_FB_"></td><td> <input name="E" type="text" value="_FE_"></td>
    <td> <input name="P" type="text" value="_FP_"></td><td> <button type="submit">Set</button></td></tr>
    </table></form>
    <h3>Co2</h3><form action="/co2"><table><tr><th>Start</th><th>Stop</th><th></th></tr><tr>
    <td> <input name="B" type="text" value="_CB_"></td><td> <input name="E" type="text" value="_CE_"></td>
    </td><td> <button type="submit">Set</button></td></tr>
    </table></form></body></html>)rawliteral";
}
