#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#include <Adafruit_BMP085.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP085 bmp;

#define LDR_PIN 34

#define GREEN_LED 25
#define YELLOW_LED 26
#define RED_LED 27
#define BUZZER 18

void setup()
{
  Serial.begin(115200);

  Wire.begin(21,22);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  dht.begin();

  if (!bmp.begin())
  {
    Serial.println("BMP180 NOT FOUND");
    while (1);
  }

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println("OLED NOT FOUND");
    while (1);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(10,20);
  display.println("WELCOME");

  display.display();
  delay(2000);

  display.clearDisplay();
}

void loop()
{
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  float pressure = bmp.readPressure()/100.0;
  int light = analogRead(LDR_PIN);

  Serial.print("Temperature : ");
  Serial.println(temperature);

  Serial.print("Humidity : ");
  Serial.println(humidity);

  Serial.print("Pressure : ");
  Serial.println(pressure);

  Serial.print("Light : ");
  Serial.println(light);

  display.clearDisplay();

  display.setTextSize(1);

  display.setCursor(0,0);
  display.print("Temp: ");
  display.print(temperature);
  display.println(" C");

  display.setCursor(0,16);
  display.print("Hum : ");
  display.print(humidity);
  display.println("%");

  display.setCursor(0,32);
  display.print("Pres:");
  display.print(pressure);
  display.println("hPa");

  display.setCursor(0,48);
  display.print("Light:");
  display.println(light);

  display.display();

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BUZZER, LOW);

  if(temperature < 25)
  {
    digitalWrite(GREEN_LED, HIGH);
  }
  else if(temperature >= 25 && temperature <= 35)
  {
    digitalWrite(YELLOW_LED, HIGH);
  }
  else
  {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(BUZZER, HIGH);
  }

  delay(1000);
}