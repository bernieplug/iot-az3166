#include "AzureIotHub.h"
#include "AZ3166WiFi.h"
#include "configuration.h"
#include "utility.h"
#include "iothubclientsample.h"
#include "Telemetry.h"

static bool hasWifi = false;
int messageCount = 1;
void initWifi()
{
     Screen.print("IoT DevKit\r\n \r\nConnecting.....\r\n");

    if (WiFi.begin() == WL_CONNECTED)
    {
        IPAddress ip = WiFi.localIP();
        Screen.print(1, ip.get_address());
        hasWifi = true;
        Screen.print(2, "Running... \r\n");
    }
    else
    {
        Screen.print(1, "No Wi-Fi\r\n ");
    }
}

void setup()
{
    hasWifi = false;
    initWifi();
    if (!hasWifi)
    {
        LogInfo("Please make sure the wifi connected!");
        return;
    }
    
    send_telemetry_data_async("", "HappyPathSetup", "");
    Serial.begin(115200);
    sensorInit();
    iothubInit();
}

void loop()
{
    char messagePayload[MESSAGE_MAX_LEN];
    bool temperatureAlert = readMessage(messageCount,messagePayload);
    bool humidityAlert;
    iothubSendMessage((const unsigned char *)messagePayload, temperatureAlert,humidityAlert);
    iothubLoop();
    delay(10);
}
