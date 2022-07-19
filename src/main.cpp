#include <Arduino.h>

#include <WiFi.h>

static WiFiClient espClient;
#include <ArduinoJson.h>

#include <AliyunIoTSDK.h>
AliyunIoTSDK iot;

#define PRODUCT_KEY "h5ox50yORmT"
#define DEVICE_NAME "test1"
#define DEVICE_SECRET "a2263a9f340cc38c9d67cf204ff54c4f"
#define REGION_ID "cn-shanghai"

#define WIFI_SSID "ChinaNet-9A4b"
#define WIFI_PASSWD "t9sbf0nd"

void powerCallback(JsonVariant p);
void wifiInit(const char *ssid, const char *passphrase)
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, passphrase);
  WiFi.setAutoConnect(true);
  WiFi.setAutoReconnect(true);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("WiFi not Connect");
  }
  Serial.println("Connected to AP");
}

void setup()
{
  Serial.begin(115200);

  wifiInit(WIFI_SSID, WIFI_PASSWD);

  AliyunIoTSDK::begin(espClient, PRODUCT_KEY, DEVICE_NAME, DEVICE_SECRET, REGION_ID);

  // 绑定属性回调
  // AliyunIoTSDK::bindData("PowerSwitch", powerCallback);
}

unsigned long lastMsMain = 0;
void loop()
{
  AliyunIoTSDK::loop();
  if (millis() - lastMsMain >= 5000)
  {
    lastMsMain = millis();
    // 发送事件到阿里云平台
    // AliyunIoTSDK::sendEvent("xxx");
    // 发送模型属性到阿里云平台
    AliyunIoTSDK::send("LED", 1);
  }
}

void powerCallback(JsonVariant p)
{
  int PowerSwitch = p["PowerSwitch"];
  if (PowerSwitch == 1)
  {
    //
  }
  else
  {
    //
  }
}