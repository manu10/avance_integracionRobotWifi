#include <ESP8266WiFi.h>
#include "stdlib.h"
#define PORT 80

//PUENTE H
//Compilando con Wemos D1 R2 & Mini:
//const int AIA = D7;
//const int BIB = D2;
//const int BIA = D5;
//const int AIB = D6;
//Compilando con Wemos D1(retired):
const int AIA = D7;
const int AIB = D6;
const int BIB = D4;
const int BIA = D5;
int speed = 900;



//Sensor de ultrasonido:
#define TRIG D2 //Cambiar a D3 u otro y probar...
#define ECHO D8
long distancia;
long tiempo;
//////////////

const char* ssid = "qwerty";//Modificar segun corresponda
const char* password = "qwerty";//Modificar segun corresponda

WiFiServer server(PORT);

boolean alreadyConnected = false; // whether or not the client was connected previously

void setup() {
  Serial.begin(115200);
  delay(10);
  //HC_SR04_setup();ojo qe se deben suporponer....

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");

  // Start the server
  server.begin();
  Serial.println("Servidor iniciado");

  // Print the IP address
  Serial.print("Conectese mediante TCP a la siguiente IP: ");
  Serial.print(WiFi.localIP());
  Serial.print(" en el puerto: ");
  Serial.println(PORT);



  //Configuracion del puente H
  pinMode( AIA, OUTPUT );
  pinMode( AIB, OUTPUT );
  pinMode( BIA, OUTPUT );
  pinMode( BIB, OUTPUT );

}

WiFiClient client;
void loop() {
  if (!client.connected()) {
    // try to connect to a new client
    client = server.available();//Ver https://www.arduino.cc/en/Reference/ServerAvailable
    delay(100);
    if (client.connected()) {
      Serial.write("Nuevo cliente: ");
      Serial.println(client.remoteIP());
    }
  } else {
    // read data from the connected client
    if (client.available() > 0) {
      String request = client.readStringUntil('\n');
      Serial.println(request);
      if (request == "avanzar") {
        speed = 600;
        delay(10);
        R_forward();
        delay(10);
      } else if (request == "retroceder") {
        speed = 600;
        delay(10);
        R_backward();
        delay(10);
      } else if (request == "acelerar") {
        speed = speed + 200;
        delay(10);
        R_forward();
      } else if (request == "frenar") {
        speed = 0;
        delay(10);
        R_stop();
      } else if (request == "derecha") {
        speed = 600;
        delay(10);
        R_turn_right();
      } else if (request == "izquierda") {
        speed = 600;
        delay(10);
        R_turn_left();
      } else {
        R_stop();
      }
      //              Serial.println("Distancia ");
      //              Serial.println(HC_SR04_getDistancia());
      //              Serial.println(" cm \n");
      //              client.println("$DISTA=");
      //              client.println(HC_SR04_getDistancia());
      //              client.println("$");
      //  //              long distaaa=111111;
      //  //              String dist=String(HC_SR04_getDistancia());
      //  //              String dist=String(13);
      //  //              client.write(dist);
      //
      //  //              char buffer[7];         //the ASCII of the integer will be stored in this char array
      //  //              itoa(HC_SR04_getDistancia(),buffer,10); //(integer, yourBuffer, base)
      //  //              client.write(buffer
      //  //              client.write("$");
      //            }
    }
  }

}


void HC_SR04_setup() {
  pinMode(TRIG, OUTPUT); /*activación del pin TRIG como salida: para el pulso ultrasónico*/
  pinMode(ECHO, INPUT); /*activación del pin ECHO como entrada: tiempo del rebote del ultrasonido*/


}
long HC_SR04_getDistancia() {
  digitalWrite(TRIG, LOW); /* Por cuestión de estabilización del sensor*/
  delayMicroseconds(5);
  digitalWrite(TRIG, HIGH); /* envío del pulso ultrasónico*/
  delayMicroseconds(10);
  tiempo = pulseIn(ECHO, HIGH); /* Función para medir la longitud del pulso entrante. Mide el tiempo que transcurrido entre el envío
  del pulso ultrasónico y cuando el sensor recibe el rebote, es decir: desde que el pin 12 empieza a recibir el rebote, HIGH, hasta que
  deja de hacerlo, LOW, la longitud del pulso entrante*/
  distancia = int(0.017 * tiempo); /*fórmula para calcular la distancia obteniendo un valor entero*/
  /*Monitorización en centímetros por el monitor serial*/
  //  Serial.println("Distancia ");
  //  Serial.println(distancia);
  //  Serial.println(" cm \n");

  return distancia;

}

void R_backward()
{
  analogWrite(AIA, 0);
  analogWrite(AIB, speed);
  analogWrite(BIB, speed);
  analogWrite(BIA, 0);
}
void R_forward()
{
  analogWrite(AIA, speed);
  analogWrite(AIB, 0);
  analogWrite(BIA, speed);
  analogWrite(BIB, 0);

}
void R_turn_right()
{
  analogWrite(AIA, 0);
  analogWrite(AIB, 0);
  analogWrite(BIB, 0);
  analogWrite(BIA, speed);

}
void R_turn_left()
{
  analogWrite(AIA, speed);
  analogWrite(AIB, 0);
  analogWrite(BIB, 0);
  analogWrite(BIA, 0);

}
void R_stop()
{
  delay(10);
  analogWrite(AIA, 0);
  delay(10);
  analogWrite(AIB, 0);
  delay(10);
  analogWrite(BIB, 0);
  delay(10);
  analogWrite(BIA, 0);
  delay(10);

}

