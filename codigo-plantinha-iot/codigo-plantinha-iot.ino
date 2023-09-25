//Programa: Plantinha IoT
//Autor: FILIPEFLOP

//-------Informações sobre a planta--------

// Valores mínimos e máximos de umidade do solo, temperatura e luminosidade para SUCULENTAS
int u_min = 15;
//int u_max = 30;
int u_max = 47;                                                                                                                                                                                                        
int t_min = 10;
int t_max = 35;
//int l_min = 7000;
int l_min = 250;
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

//-------Configurações iniciais da plataforma Blynk--------

#define BLYNK_PRINT Serial

// Insira abaixo o ID do seu template
#define BLYNK_TEMPLATE_ID "TMPLbDGaqYJH"

// Insira abaixo o seu Auth Token
char auth[] = "KHgunVDCXaPwnT94joCrtzOlQLlLqaaW";

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

//--------Configurações iniciais do sensor de luminosidade--------
BH1750 lightMeter;

//--------Setup--------

char ssid[] = "MonkeyB_2G";
char pass[] = "monkey_615243";

//char ssid[] = "ISRAEL OI FIBRA";
//char pass[] = "01040607";

char serverAddress[] = "137.184.129.157";  // server address
int port = 3000;

WiFiClient wifi;
HttpClient client = HttpClient(wifi, serverAddress, port);
int status = WL_IDLE_STATUS;

void setup(){
  
  // Inicializa a comunicação serial
  Serial.begin(9600);

  Serial.println("Setup done");

  // Inicializa a plataforma Blynk
 // Blynk.begin(auth, ssid, pass);

 //    delay(5000);
  
 //Inicializa o sensor de temperatura
  if(!bmp280.begin(BMP280_I2C_ADDRESS))
  {  
   Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while(1);
  }

  //Inicializa o sensor de luminosidade
  lightMeter.begin();
  
  //Inicializa o display LCD TFT
  tft.initR(INITR_BLACKTAB);
  tft.fillRect( 0, 0, 128, 160, PRETO);

  
  //inicia conexão na rede
  initPlantinha();
  //platinhaStatus("activate");

}

//--------Loop--------

void loop(){

  // Verifica a luminosidade ambiente
  uint16_t luminosidade = lightMeter.readLightLevel();
  Serial.print("Luminosidade= ");
  Serial.println(luminosidade);
  
  // Verifica a temperatura ambiente
  float temperatura = bmp280.readTemperature();
  Serial.print("Temperatura = ");
  Serial.println(temperatura);
  
  // Verifica a umidade do solo
  AOUT = analogRead(A0);
  umidade = 100 * ((978-(float)AOUT) / 978);
  Serial.print("Umidade do solo = ");
  Serial.println(umidade);

  // Atualização da plataforma Blynk                            
  //Blynk.run();
  
  // Envia os dados para a plataforma Blynk
  //Blynk.virtualWrite(V0, luminosidade);
 // Blynk.virtualWrite(V1, temperatura);
 // Blynk.virtualWrite(V2, umidade);
  
  // Se a umidade do solo for muito baixa, a plantinha ficará com sede
  if(umidade < u_min){
    if(var_sede == 0){
      limpar();
      var_sede = 1;
      platinhaStatus("littleWater");
    }
    sede();
  }

  // Se a umidade do solo for muito alta, a plantinha ficará enjoada
  else if(umidade > u_max){ 
    if(var_enjoada == 0){
      limpar();
      var_enjoada = 1;
      platinhaStatus("muchWater");
    }
    enjoada();   
  }

  // Se a temperatura for muito baixa, a plantinha ficará com frio
  else if(temperatura < t_min){
    if(var_frio == 0){
      limpar();
      var_frio = 1;
      platinhaStatus("cold");
    }
    frio();  
  }

  // Se a temperatura for muito alta, a plantinha ficará com calor
  else if(temperatura > t_max){
    if(var_calor == 0){
      limpar();
      var_calor = 1;
      platinhaStatus("hot");
    }
    calor();
  }

  // Se a luminosidade for muito baixa, a plantinha virará uma vampira
  else if(luminosidade < l_min){
    if (var_vampiro == 0){
      limpar();
      var_vampiro = 1;
      platinhaStatus("vampire");
    }
    vampiro(); 
  }
  
  // Se a luminosidade for muito alta, a plantinha ficará com óculos escuros
  else if(luminosidade > l_max){
    if (var_oculos == 0){
      limpar();
      var_oculos = 1;
      platinhaStatus("sun");
    }
    oculos();
  }

  // Se todos os parâmetros estiverem dentro dos valores ideais, a plantinha ficará feliz
  else{
    if(var_feliz == 0){
      limpar();
      var_feliz = 1;
      platinhaStatus("ok");
    }
    feliz();
  }
  
  delay(5000);
}

void initPlantinha() {
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

//função post de iniciado
void platinhaStatus(String status){
  Serial.println("making POST request");
  String contentType = "application/json";
  String postData = "{\"status\":\""+(String)status+"\"}";

  client.post("/api/v1/sendStatus", contentType, postData);

  // read the status code and body of the response
  int statusCode = client.responseStatusCode();
  String response = client.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);

  delay(2000);
}

//--------Função limpar display--------

void limpar()
{
     delay(500);
     tft.fillRect(0,0,128,160,PRETO);
     delay(100);
}

//--------Função plantinha com sede--------

void sede()
{
  tft.drawBitmap(0, 0, sede1, 128, 160, BRANCO);
  tft.drawBitmap(0, 0, sede2, 128, 160, MAGENTA);

  tft.setTextColor(BRANCO);
  tft.setCursor(20,140);
  tft.println("Que seeeeeeede!");
  tft.setCursor(30,150);;
  tft.print("Me da agua?");
  
  var_feliz    = 0;
  var_enjoada = 0;
  var_calor   = 0;
  var_frio    = 0;
  var_vampiro = 0;
  var_oculos  = 0;
}

//--------Função plantinha enjoada--------

void enjoada()
{
  tft.drawBitmap(0, 0, enjoada1, 128, 160, BRANCO);
  tft.setTextColor(BRANCO);
  tft.setCursor(5,140);
  tft.println("Argh! Estou enjoada!");
  tft.setCursor(7,150);
  tft.print("Nao quero mais agua");
  
  var_feliz   = 0;
  var_sede    = 0;
  var_calor   = 0;
  var_frio    = 0;
  var_vampiro = 0;
  var_oculos  = 0; 
}

//--------Função plantinha com frio--------

void frio()
{
  tft.drawBitmap(0, 0, frio1, 128, 160, AZUL);
  tft.drawBitmap(0, 0, frio2, 128, 160, BRANCO);
  tft.setTextColor(BRANCO);
  tft.setCursor(50,140);
  tft.println("Brrr!");
  tft.setCursor(10,150);
  tft.print("Estou com friiiio");
  
  var_feliz   = 0;
  var_sede    = 0;
  var_enjoada = 0;
  var_calor   = 0;
  var_vampiro = 0;
  var_oculos  = 0;  
}

//--------Função plantinha com calor--------

void calor()
{
  tft.drawBitmap(0, 0, calor1, 128, 160, BRANCO);
  tft.drawBitmap(0, 0, calor2, 128, 160, AZUL);
  tft.drawBitmap(0, 0, calor3, 128, 160, MAGENTA);
  tft.setTextColor(BRANCO);
  tft.setCursor(25,140);
  tft.println("Ai! Que calor!");
  tft.setCursor(15,150);
  tft.print("Esta muito quente");
    
  var_feliz   = 0;
  var_sede    = 0;
  var_enjoada = 0;
  var_frio    = 0;
  var_vampiro = 0;
  var_oculos  = 0;  
}

//--------Função plantinha vampira--------

void vampiro()
{
  tft.drawBitmap(0, 0, vampiro1, 128, 80, VERMELHO);
  tft.drawBitmap(0, 80, vampiro2, 128, 80, BRANCO);
  tft.setTextColor(BRANCO);
  tft.setCursor(4,140);
  tft.println("Cuidado! Sem luz vou");
  tft.setCursor(15,150);
  tft.print("virar uma vampira");
  
  var_feliz   = 0;
  var_sede    = 0;
  var_enjoada = 0;
  var_calor   = 0;
  var_frio    = 0;
  var_oculos  = 0;
}

//--------Função plantinha com óculos--------

void oculos()
{
  tft.drawBitmap(0, 0, oculos1, 128, 160, BRANCO);
  tft.drawBitmap(0, 0, oculos2, 128, 160, CINZA);
  tft.setTextColor(BRANCO);
  tft.setCursor(7,140);
  tft.println("Olha esse Sol! Cade");
  tft.setCursor(13,150);
  tft.print("o protetor solar?");
  
  var_feliz   = 0;
  var_sede    = 0;
  var_enjoada = 0;
  var_calor   = 0;
  var_frio    = 0;
  var_vampiro = 0;
}

//--------Função plantinha feliz--------

void feliz()
{
  tft.drawBitmap(0, 0, feliz1, 128, 160, BRANCO);
  tft.drawBitmap(0, 0, feliz2, 128, 160, MAGENTA);
  tft.setTextColor(BRANCO);
  tft.setCursor(20,140);
  tft.println("Hum! Esta tudo");
  tft.setCursor(10,150);
  tft.print("perfeito. Obrigada!");
  
  var_sede    = 0;
  var_enjoada = 0;
  var_calor   = 0;
  var_frio    = 0;
  var_vampiro = 0;
  var_oculos  = 0;
}