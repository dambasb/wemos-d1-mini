// Wemos WiFi biblioteke:
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// fiksna adresa servera:
#define SERVER_ADDRESS    "http://..."

// Postavke mreže:
const char* ssid     = "...";
const char* password = "...";

// Output functions
void _authorized();
void _notAuthorized();
void _wifiConnected();
void _connectionFailed();

// u setup-u
WiFi.begin(ssid, password);

// u loop-u
while(WiFi.status() != WL_CONNECTED) {
      delay(500);
      #ifdef DEBUG_INFO
        Serial.print(".");
      #endif
      flagConnected = 1;
    }

    if(flagConnected == 1)
    {
      Serial.println("");
      Serial.println("WiFi connected");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP()); 
      #ifdef DEBUG_INFO
        Serial.flush();
      #endif
      flagConnected = 0;
    }

HTTPClient http;
http.begin(SERVER_ADDRESS);
http.addHeader("Content-Type", "application/json");
int var1, var2, var3;
var1=1; var2=2; var3=3;
String msg = "{\"var1\": \""+ String(var1) + \"", \"var2\": \"" + String(var2) + "\", \"var3\": \"" + String(var3) + "\"}";
Serial.println(msg);
int httpCode = http.POST(msg);

   int httpCode = http.POST(msg);

    // httpCode will be negative on error
    if(httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        #ifdef DEBUG_INFO
          Serial.printf("[HTTP] POST... code: %d\n", httpCode);
        #endif

        // file found at server
        if(httpCode == 200) {          
            String payload = http.getString();

            int indEnd = payload.indexOf('}');  //finds location of end ,

            #ifdef TEST_HTTTP_POST
              int indStart = payload.indexOf('"id": ');  //finds location of start ,
              String id = payload.substring(indStart + 8, indEnd);
            #else
              int indStart = payload.indexOf('"msg":');  //finds location of start ,
              String id = payload.substring(indStart + 1, indEnd);
            #endif
            
            int _errorID = id.toInt();

            //SoundNotifications(_errorID);
            //LEDNotifications(_errorID);

            SoundAndLEDNotifications(_errorID);

            #ifdef DEBUG_INFO
              Serial.print("Payload: ");
              Serial.println(payload);
  
              Serial.print("INDEX Start: ");
              Serial.println(indStart);
  
              Serial.print("INDEX End: ");
              Serial.println(indEnd);
              
              Serial.print("Received ID: ");
              Serial.println(id);
              
              Serial.print("_errorID: ");
              Serial.println(_errorID);
            #endif                     
        }
    }
    else
    {
      #ifdef DEBUG_INFO
        Serial.printf("Error: [HTTP] POST... code: %d\n", httpCode);
      #endif
    }    

    http.end();
    
    //delay(RFID_READ_DELAY);
  }
