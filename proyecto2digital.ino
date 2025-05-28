/*
Autor: Nicole Haase Martínez
Carnet: 23860
Fecha de creación: 7/05/2025
Ultima modificación: 14/05/2025

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

//Angulos de cada servo
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

  // Configurar salidas
  pinMode(lauto, OUTPUT);
  pinMode(lmanu, OUTPUT);

  // Configurar entrada de modo
  pinMode(modo, INPUT);
}

void loop() {
  

  if (digitalRead(modo) == 0) { // Modo manual
    digitalWrite(lmanu, HIGH);
    digitalWrite(lauto, LOW);

    myservo_Abajo.write(movimientoS(joyAx));
    myservo_lateral_izq.write(movimientoS(joyAy));
    myservo_lateral_der.write(movimientoS(joyBx));
    myservo_pinza.write(movimientoS(joyBy));

  } else { // Modo automático
    digitalWrite(lauto, HIGH);
    digitalWrite(lmanu, LOW);

    //llamar a la función
    int valorJoyAY = analogRead(joyAy);
    int valorJoyAX = analogRead(joyAx);
    int valorJoyBY = analogRead(joyBy);
    int valorJoyBX = analogRead(joyBx);

    // cadena de if para llamar cada movimiento
    movimiento_1();
    movimiento_2();
    movimiento_3();
    movimiento_4();
  }
  
}

int movimientoS(int nombre_boton) { //es int ya que retorna un valor entero
  int lectura = analogRead(nombre_boton);
  int angulo = map(lectura, 0, 1023, 0, 180); // Conversión a grados del servo
  return angulo;
}

// Funciones automáticas
void movimiento_1() { //movimiento aleatorio de prueba
  myservo_Abajo.write(90);
  myservo_lateral_izq.write(45);
  myservo_lateral_der.write(135);
  myservo_pinza.write(30);
}

void movimiento_2() {}
void movimiento_3() {}
void movimiento_4() {}
