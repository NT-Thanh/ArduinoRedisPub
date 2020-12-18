#include <Adafruit_MLX90614.h>

#include <Redis.h>

#define WIFI_SSID "thanhne"
#define WIFI_PASSWORD "thanha@a"

#define REDIS_ADDR "redis-10104.c239.us-east-1-2.ec2.cloud.redislabs.com"
#define REDIS_PORT 10104
#define REDIS_PASSWORD "12345678@Abc"

Redis redis(REDIS_ADDR, REDIS_PORT);
char* messageNumber = "10000000000000000000000000000";
int counter = 0;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup()
{
    Serial.begin(115200);
    Serial.println();

    mlx.begin();
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

    Serial.println("Adafruit MLX90614 test");


//    redis.close();
//    Serial.print("Connection closed!");
}

void loop()
{
    counter++;
    char cstr[16];
    char mid[3] = ",";
    String sepa = "";
    sepa.concat(mlx.readAmbientTempC());
    sepa.concat(mid);
    sepa.concat(mlx.readObjectTempC());
    char object[100];
    sepa.toCharArray(object, 100);
//    char ambitent[9];
//    dtostrf(mlx.readAmbientTempC(), 9, 4, ambitent);
//    dtostrf(mlx.readObjectTempC(), 9, 4, object);
    itoa(counter, cstr, 10);
    strcpy(messageNumber, cstr);
    Serial.print("\nMessage Number: ");
    Serial.print(object);
    Serial.print("; SentStatus: ");
    Serial.print(redis.publish("test", object));
    delay(1000);
}
