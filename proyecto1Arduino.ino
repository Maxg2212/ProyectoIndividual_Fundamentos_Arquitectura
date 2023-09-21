#include <Servo.h>

Servo miServo;
const int trigPin = 13;
const int echoPin = 12;
const int A = 8;  // Primer pin de salida en código Gray
const int B = 9;  // Segundo pin de salida en código Gray
const int C = 10; // Tercer pin de salida en código Gray
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
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
}


void loop() {
  // put your main code here, to run repeatedly:
  long Time;
  long Dist;
  int Hex;
  int Graya;
  int Grayb;
  int Grayc;

  digitalWrite(trigPin,LOW);
  delayMicroseconds(4);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);

  Time = pulseIn(echoPin,HIGH);
  Dist = Time/59;

  if(Dist < 5 || Dist < 40){  
    digitalWrite(A,LOW);
    digitalWrite(B,LOW);
    digitalWrite(C,LOW);
    Graya = 0;
    Grayb = 0;
    Grayc = 0;
    Hex = 0;
  }
  if(Dist >= 5 && Dist < 10){  
    digitalWrite(A,LOW);
    digitalWrite(B,LOW);
    digitalWrite(C,HIGH);
    Graya = 0;
    Grayb = 0;
    Grayc = 1;
    Hex = 1;
  }
  if(Dist >= 10 && Dist < 15){
    digitalWrite(A,LOW);
    digitalWrite(B,HIGH);
    digitalWrite(C,HIGH);
    Graya = 0;
    Grayb = 1;
    Grayc = 1;
    Hex = 2;
  }
  if(Dist >= 15 && Dist < 20){
    digitalWrite(A,LOW);
    digitalWrite(B,HIGH);
    digitalWrite(C,LOW);
    Graya = 0;
    Grayb = 1;
    Grayc = 0;
    Hex = 3;
  }
  if(Dist >= 20 && Dist < 25){
    digitalWrite(A,HIGH);
    digitalWrite(B,HIGH);
    digitalWrite(C,LOW);
    Graya = 1;
    Grayb = 1;
    Grayc = 0;
    Hex = 4;
  }
  if(Dist >= 25 && Dist < 30){
    digitalWrite(A,HIGH);
    digitalWrite(B,HIGH);
    digitalWrite(C,HIGH);
    Graya = 1;
    Grayb = 1;
    Grayc = 1;
    Hex = 5;
  }
  if(Dist >= 30 && Dist < 35){
    digitalWrite(A,HIGH);
    digitalWrite(B,LOW);
    digitalWrite(C,HIGH);
    Graya = 1;
    Grayb = 0;
    Grayc = 1;
    Hex = 6;
  }
  if(Dist >= 35 && Dist <= 40){
    digitalWrite(A,HIGH);
    digitalWrite(B,LOW);
    digitalWrite(C,LOW);
    Graya = 1;
    Grayb = 0;
    Grayc = 0;
    Hex = 7;
  }

  int estadoCompuerta = digitalRead(xorPin);
  
  if (estadoCompuerta == HIGH) {
    // Activa el servo moviéndolo a una posición específica (por ejemplo, 90 grados)
    miServo.write(90);
  } else {
    // Desactiva el servo moviéndolo a otra posición (por ejemplo, 0 grados)
    miServo.write(0);
  }
  
  delay(100);  // Añade una pequeña pausa para evitar lecturas rápidas y movimientos bruscos
  Serial.print("Hexadecimal: ");
  Serial.println(Hex);
  Serial.print("Código Gray: ");
  Serial.print(Graya);
  Serial.print(Grayb);
  Serial.println(Grayc);
}
