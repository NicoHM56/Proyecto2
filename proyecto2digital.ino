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

    moverGrado(joyAx, angulo_Abajo, myservo_Abajo);
    moverGrado(joyAy, angulo_Izq, myservo_lateral_izq);
    moverGrado(joyBx, angulo_Der, myservo_lateral_der);
    moverGrado(joyBy, angulo_Pinza, myservo_pinza);

    delay(20);  // Pequeña pausa para que el movimiento sea suave

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
/*
int movimientoS(int nombre_boton) { //es int ya que retorna un valor entero
  int lectura = analogRead(nombre_boton);
  int angulo = map(lectura, 0, 1023, 0, 180); // Conversión a grados del servo
  return angulo;
}*/

void moverGrado(int pin, int &angulo, Servo &servo) {
  int lectura = analogRead(pin);  // Lee el valor del joystick

  // Si el joystick se mueve hacia izquierda/abajo más allá de la zona muerta
  if (lectura < 512 - zona_muerta) { // eL 512 REPRESENTA 2.5v (0 a 1023)
    if (angulo > 0) angulo--;        // Resta 1 grado si no está en el mínimo
    servo.write(angulo);             // Mueve el servo al nuevo ángulo
  } 
  // Si el joystick se mueve hacia la derecha/arriba más allá de la zona muerta
  else if (lectura > 512 + zona_muerta) {
    if (angulo < 180) angulo++;      // Suma 1 grado si no está en el máximo
    servo.write(angulo);             // Mueve el servo al nuevo ángulo
  }
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
