#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <DHT.h>

#define DHTPIN D5     // CHANGE TO CORRECT PIN
#define DHTTYPE DHT11


DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "WIFI_NAME";
const char* password = "WIFI_PASSWORD";
const char* serverAddress = "PHP_REMOTE_SERVER";

WiFiClient client;

void setup() {
  Serial.begin(9600);
  Serial.println("Iniciando...");
  
  dht.begin();
  connectToWiFi();
}


//LENDO TEMP E UMIDADE
  void loop() {
    delay(20000); // Delay 
  
  float umidade = dht.readHumidity(); 
  float temperatura = dht.readTemperature(); 
  
  if (isnan(umidade) || isnan(temperatura)) {
    Serial.println("Falha ao ler o sensor DHT!");
    return;  
  }
  
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" °C");
  
  Serial.print("Umidade: ");
  Serial.print(umidade);
  Serial.println(" %");

  //////// CONECTANDO COM O BACKEND PHP /////////
  if (client.connect(serverAddress, 80)) {
    Serial.println("CONECTADO");
    client.print("GET /dht/main.php?");
    client.print("temperatura=");
    client.print(temperatura);
    client.print("&umidade=");
    client.print(umidade);
    client.println(" HTTP/1.1");
    client.println("Host: " + String(serverAddress));
    client.println("Connection: close");
    client.println();
    delay(10);
  } else {
    //Serial.println("ERRO NA CONEXAO, VERIFICAR");
  }
}

void connectToWiFi() {
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
   
  Serial.println("");
  Serial.println("Conectado à rede Wi-Fi");
  Serial.println("Endereço IP: ");
  Serial.println(WiFi.localIP());

}
