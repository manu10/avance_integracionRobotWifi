 long distancia;
long tiempo;
#define SALIDA D15
#define ENTRADA D14
void setup(){
   Serial.begin(115200);
  delay(10);
 
 
//  pinMode(ledPin, OUTPUT);
//  digitalWrite(ledPin, LOW);
  
  Serial.println("Prueba Serial \n");
  pinMode(SALIDA, OUTPUT); /*activación del pin 9 como salida: para el pulso ultrasónico*/
  pinMode(ENTRADA, INPUT); /*activación del pin 8 como entrada: tiempo del rebote del ultrasonido*/
  
}


void loop(){
  digitalWrite(SALIDA,LOW); /* Por cuestión de estabilización del sensor*/
  delayMicroseconds(5);
  digitalWrite(SALIDA, HIGH); /* envío del pulso ultrasónico*/
  delayMicroseconds(10);
  tiempo=pulseIn(ENTRADA, HIGH); /* Función para medir la longitud del pulso entrante. Mide el tiempo que transcurrido entre el envío
  del pulso ultrasónico y cuando el sensor recibe el rebote, es decir: desde que el pin 12 empieza a recibir el rebote, HIGH, hasta que
  deja de hacerlo, LOW, la longitud del pulso entrante*/
  distancia= int(0.017*tiempo); /*fórmula para calcular la distancia obteniendo un valor entero*/
  /*Monitorización en centímetros por el monitor serial*/
  Serial.println("Distancia ");
  Serial.println(distancia);
  Serial.println(" cm \n");
  delay(1000);
}
