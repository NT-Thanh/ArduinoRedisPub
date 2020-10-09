#include <Redis.h>

#define WIFI_SSID "Thanh ne"
#define WIFI_PASSWORD "thanha@a"

#define REDIS_ADDR "redis-10104.c239.us-east-1-2.ec2.cloud.redislabs.com"
#define REDIS_PORT 10104
#define REDIS_PASSWORD "12345678@Abc"

Redis redis(REDIS_ADDR, REDIS_PORT);
char* messageNumber = "10000000000000000000000000000";
int counter = 0;

void setup()
{
    Serial.begin(115200);
    Serial.println();

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to the WiFi");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(250);
        Serial.print(".");
    }
    Serial.println();
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.println("Connecting to the Redis database");
    if (redis.begin(REDIS_PASSWORD))
    {
        Serial.println("Connected to the Redis server!");
    }
    else
    {
        Serial.println("Failed to connect to the Redis server!");
        return;
    }



//    redis.close();
//    Serial.print("Connection closed!");
}

void loop()
{
    counter++;
    char cstr[16];
    itoa(counter, cstr, 10);
    strcpy(messageNumber, cstr);
    delay(2000);
    Serial.print("\nMessage Number: ");
    Serial.print(messageNumber);
    Serial.print("; SentStatus: ");
    Serial.print(redis.publish("test", messageNumber));
}
