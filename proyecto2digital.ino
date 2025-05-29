/*
Autor: Nicole Haase Martínez
Carnet: 23860
Fecha de creación: 7/05/2025
Ultima modificación: 28/05/2025

mejoras del diseño:
no se esta usando uno de los botones del servo A y B
los movimientos automatico se puede poner con Ax movimiento1, Ay movimiento2 y así
Se podria hacer más corto el codigo?
*/


 #include <Servo.h>

// Nombrar los motores
Servo myservo_Abajo;
Servo myservo_lateral_izq;
Servo myservo_lateral_der;
Servo myservo_pinza;

// Declaración de Variables
const int joyAx = A4;
const int joyAy = A5;
const int joyAA = 6;

const int joyBx = A2;
const int joyBy = A3;
const int joyBB = 7;

const int lauto = 11; // LED modo automático
const int lmanu = 8;  // LED modo manual

const int modo = 2;   // DIP switch para seleccionar modo

// Ángulos de cada servo
int angulo_Abajo = 90;
int angulo_Izq = 90;
int angulo_Der = 90;
int angulo_Pinza = 90;

// Margen de tolerancia para ignorar ruido
const int zona_muerta = 80;

void setup() {
  // Conectar motores a los pines
  myservo_Abajo.attach(3);
  myservo_lateral_izq.attach(5);
  myservo_lateral_der.attach(9);
  myservo_pinza.attach(10);

  pinMode(lauto, OUTPUT);
  pinMode(lmanu, OUTPUT);
  pinMode(modo, INPUT);

  // Iniciar comunicación serial
  Serial.begin(9600);
  Serial.println("Sistema iniciado");
}

void loop() {
  digitalWrite(lauto, LOW);
  digitalWrite(lmanu, LOW);

  if (digitalRead(modo) == 0) { // Modo manual
    digitalWrite(lmanu, HIGH);
    digitalWrite(lauto, LOW);

    Serial.println("Modo: MANUAL");

    moverGrado(joyAx, angulo_Abajo, myservo_Abajo);
    moverGrado(joyAy, angulo_Izq, myservo_lateral_izq);
    moverGrado(joyBx, angulo_Der, myservo_lateral_der);
    moverGrado(joyBy, angulo_Pinza, myservo_pinza);

    // Mostrar ángulos actuales
    Serial.print("Abajo: "); Serial.print(angulo_Abajo);
    Serial.print(" | Izq: "); Serial.print(angulo_Izq);
    Serial.print(" | Der: "); Serial.print(angulo_Der);
    Serial.print(" | Pinza: "); Serial.println(angulo_Pinza);

    //delay(200); // Delay más largo para ver mejor en serial

  } else { // Modo automático
    digitalWrite(lauto, HIGH);
    digitalWrite(lmanu, LOW);

    Serial.println("Modo: AUTOMÁTICO");

    int valorJoyAX = analogRead(joyAx);
    int valorJoyAY = analogRead(joyAy);
    int valorJoyBX = analogRead(joyBx);
    int valorJoyBY = analogRead(joyBy);

    // Mostrar valores del joystick
    Serial.print("joyAX: "); Serial.print(valorJoyAX);
    Serial.print(" | joyAY: "); Serial.print(valorJoyAY);
    Serial.print(" | joyBX: "); Serial.print(valorJoyBX);
    Serial.print(" | joyBY: "); Serial.println(valorJoyBY);

    if (valorJoyAX != 512) {
      Serial.println("Ejecutando: movimiento_1");
      movimiento_1();
    }
    else if (valorJoyAY != 512) {
      Serial.println("Ejecutando: movimiento_2");
      movimiento_2();
    }
    else if (valorJoyBX != 512) {
      Serial.println("Ejecutando: movimiento_3");
      movimiento_3();
    }
    else if (valorJoyBY != 512) {
      Serial.println("Ejecutando: movimiento_4");
      movimiento_4();
    }

    delay(300);
  }
}

void moverGrado(int pin, int &angulo, Servo &servo) {
  int lectura = analogRead(pin);

  if (lectura < 512 - zona_muerta) {
    if (angulo > 0) angulo--;
    servo.write(angulo);
  } 
  else if (lectura > 512 + zona_muerta) {
    if (angulo < 180) angulo++;
    servo.write(angulo);
  }
}
void movimiento_1() {
  myservo_Abajo.write(0);        // totalmente abajo
  myservo_lateral_izq.write(0);  // completamente a la izquierda
  myservo_lateral_der.write(180); // completamente a la derecha
  myservo_pinza.write(30);       // pinza cerrada
}

void movimiento_2() {
  myservo_Abajo.write(180);      // totalmente arriba
  myservo_lateral_izq.write(90); // centro
  myservo_lateral_der.write(0);  // completamente al otro lado
  myservo_pinza.write(150);      // pinza abierta
}

void movimiento_3() {
  myservo_Abajo.write(90);       // medio
  myservo_lateral_izq.write(180);
  myservo_lateral_der.write(90);
  myservo_pinza.write(0);        // pinza totalmente cerrada
}

void movimiento_4() {
  myservo_Abajo.write(45);       // ángulo intermedio
  myservo_lateral_izq.write(180);
  myservo_lateral_der.write(0);
  myservo_pinza.write(180);      // totalmente abierta
}

