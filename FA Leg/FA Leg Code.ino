//Esta pata utiliza 2 servos mg995 conectados a un Arduino Uno
// La posición de cada servo se controla con potenciometros
#include <Servo.h>

Servo servo1; // Declarar servo 1
Servo servo2; // Declarar servo 2

const int pinServo1 = 5; // Motor 1 (Link superior)
const int pinServo2 = 6; // Motor 2 (Link inferior)

int angulo1_actual = 90;  // Estado inicial ángulo 1 (Pata vertical)
int angulo2_actual = 0; // Estado inicial ángulo 2 (Pata inferior retraida)

int pot1 = 0 ; // Pin Potenciómetro 1 asociado al Motor 1
int pot2 = 1; // Pin Potenciómetro 2 asociado al Motor 2

int valor_pot1; // Valor leído del potenciómetro 1
int valor_pot2; // Valor leído del potenciómetro 2

void setup() {
  Serial.begin(9600);
  // Definir Servomotores
  servo1.attach(pinServo1); // Pin servo 1
  servo2.attach(pinServo2); // Pin servo 2

  servo1.write(angulo1_actual); // Imponer estado inicial Motor 1
  servo2.write(angulo2_actual); // Imponer estado inicial Motor 2

}

void loop() {
  // Leer valores de los potenciómetros
  valor_pot1 = analogRead(pot1);
  valor_pot2 = analogRead(pot2);

  // Mapear y escribir ángulos
  angulo1_actual = map(valor_pot1, 0, 1023, 180, 60); // Acotar rango entre 60 y 180
  angulo2_actual = map(valor_pot2, 0, 1023, 90, 0); // Acotar rango entre 0 y 90

  // Imprimir valores de ángulos mapeados
  Serial.print("Motor1: ");
  Serial.print(angulo1_actual);
  Serial.print(" - Motor2: ");
  Serial.println(angulo2_actual);

  // Escribir ángulos en tiempo real en el potenciómetro
  servo1.write(angulo1_actual);
  servo2.write(angulo2_actual);
  delay(50);
}
