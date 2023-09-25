//Programa: Plantinha IoT
//Autor: FILIPEFLOP

//-------Informações sobre a planta--------

// Valores mínimos e máximos de umidade do solo, temperatura e luminosidade para SUCULENTAS
int u_min = 15;
int u_max = 35;
int t_min = 10;
int t_max = 30;
int l_min = 7000;
int l_max = 40000;

// Valores mínimos e máximos de umidade do solo, temperatura e luminosidade para CACTOS
//int u_min = 10;
//int u_max = 40;
//int t_min = 10;
//int t_max = 30;
//int l_min = 7000;
//int l_max = 40000;

// Valores mínimos e máximos de umidade do solo, temperatura e luminosidade para BEGÔNIAS
//int u_min = 40;
//int u_max = 60;
//int t_min = 20;
//int t_max = 28;
//int l_min = 300;
//int l_max = 1000;

// Valores mínimos e máximos de umidade do solo, temperatura e luminosidade para ROSAS
//int u_min = 20;
//int u_max = 50;
//int t_min = 25;
//int t_max = 30;
//int l_min = 7000;
//int l_max = 40000;

// Valores mínimos e máximos de umidade do solo, temperatura e luminosidade para ESPADA DE SÂO JORGE
//int u_min = 20;
//int u_max = 50;
//int t_min = 15;
//int t_max = 30;
//int l_min = 300;
//int l_max = 10000;

//--------Bibliotecas utilizadas no código--------

#include <Adafruit_BMP280.h>
#include <Adafruit_GFX.h> 
#include <Adafruit_Sensor.h>
#include <Adafruit_ST7735.h>
#include <BH1750.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <Wire.h>
#include <ArduinoHttpClient.h>
#include <Arduino_JSON.h>

//--------Configurações iniciais do display LCD TFT--------

//Definição dos pinos
#define TFT_SCK     0  // Pino SCK ou CLK do display TFT no Pino D3 do NodeMCU
#define TFT_SDA     12 // Pino SDA do display TFT no Pino D6 do NodeMCU
#define TFT_A0      2  // Pino A0 ou RS do display TFT no Pino D4 do NodeMCU
#define TFT_RESET   15 // Pino RESET ou RST do display TFT no Pino D8 do NodeMCU
#define TFT_CS      14 // Pino CS do display TFT no Pino D5 do NodeMCU

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_A0, TFT_SDA, TFT_SCK, TFT_RESET);

// Definição das cores
#define PRETO     0x0000
#define AZUL      0x0C3A
#define CINZA     0xD6BA
#define MAGENTA   0xF81F
#define VERMELHO  0xF800 
#define BRANCO    0xFFFF

// Caracteres externos
extern unsigned char feliz1[];
extern unsigned char feliz2[];
extern unsigned char sede1[];
extern unsigned char sede2[];
extern unsigned char enjoada1[];
extern unsigned char calor1[];
extern unsigned char calor2[];
extern unsigned char calor3[];
extern unsigned char frio1[];
extern unsigned char frio2[];
extern unsigned char vampiro1[];
extern unsigned char vampiro2[];
extern unsigned char oculos1[];
extern unsigned char oculos2[];

// Variáveis globais utilizados no código
int var_feliz   = 0;
int var_sede    = 0;
int var_enjoada = 0;
int var_calor   = 0;
int var_frio    = 0;
int var_vampiro = 0;
int var_oculos  = 0;

//--------Configurações iniciais do sensor de umidade do solo--------

int AOUT;
float umidade;

//--------Configurações iniciais do sensor de temperatura--------

#define BMP280_I2C_ADDRESS  0x76
Adafruit_BMP280 bmp280;

char ssid[] = "ISRAEL OI FIBRA";
char pass[] = "01040607";

char serverAddress[] = "192.168.100.4";  // server address
int port = 3000;

WiFiClient wifi;
HttpClient client = HttpClient(wifi, serverAddress, port);
int status = WL_IDLE_STATUS;


void setup() {
  Serial.begin(9600);
  Serial.println("Setup done");
  
  status = WiFi.begin(ssid,pass);
  Serial.print("Conectando na rede ");
  Serial.println(ssid);
  
  while (WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print(".");
  }

  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}

void loop() {
  Serial.println("making POST request");
  String contentType = "application/json";
  String postData = "{\"humidade\":\"45232\",\"temperatura\":\"45444\"}";

  client.post("/api/v1/test", contentType, postData);

  // read the status code and body of the response
  int statusCode = client.responseStatusCode();
  String response = client.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);

  Serial.println("Wait five seconds");
  delay(5000);
}