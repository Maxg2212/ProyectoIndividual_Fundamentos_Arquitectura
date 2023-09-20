#include <Servo.h>

Servo miServo;
const int trigPin = 13;
const int echoPin = 12;
const int outputPin1 = 8;  // Primer pin de salida en código Gray
const int outputPin2 = 9;  // Segundo pin de salida en código Gray
const int outputPin3 = 10; // Tercer pin de salida en código Gray
const int servoPin = 7;
const int xorPin = 2;

int duracion;
float distanciaReal;

void setup() {
  Serial.begin(9600);
  miServo.attach(servoPin);
  pinMode(xorPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(outputPin1, OUTPUT);
  pinMode(outputPin2, OUTPUT);
  pinMode(outputPin3, OUTPUT);
}

void grayEncode(int distance) {
  // Convierte el valor de distancia a código Gray
  int grayCode = (distance >> 1) ^ distance;
  
  // Escribe el código Gray en los pines de salida
  digitalWrite(outputPin1, (grayCode & 0b001) > 0);
  digitalWrite(outputPin2, (grayCode & 0b010) > 0);
  digitalWrite(outputPin3, (grayCode & 0b100) > 0);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duracion = pulseIn(echoPin, HIGH);
  distanciaReal = duracion * 0.034 / 2;

  // Llama a la función para codificar y enviar el código Gray
  grayEncode(distanciaReal);

  int estadoCompuerta = digitalRead(xorPin);
  
  if (estadoCompuerta == HIGH) {
    // Activa el servo moviéndolo a una posición específica (por ejemplo, 90 grados)
    miServo.write(90);
  } else {
    // Desactiva el servo moviéndolo a otra posición (por ejemplo, 0 grados)
    miServo.write(0);
  }
  
  delay(100);  // Añade una pequeña pausa para evitar lecturas rápidas y movimientos bruscos
}
