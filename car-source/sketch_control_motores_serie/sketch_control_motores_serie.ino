

class Motor{
  public:
    Motor(int pin_positivo, int pin_negativo);
    void mover(int direccion);
  private:
    int pin[2];
};

Motor::Motor(int pin_positivo, int pin_negativo){
  pin[0] = pin_positivo;
  pin[1] = pin_negativo;
  pinMode(pin[0], OUTPUT);
  pinMode(pin[1], OUTPUT);
  digitalWrite(pin[0], LOW);
  digitalWrite(pin[1], LOW);
}

void Motor::mover(int direccion){
  if(direccion == -1){
    // Atras
    digitalWrite(pin[0], HIGH);
    digitalWrite(pin[1], LOW);
  }else if(direccion == 1){    
    // Adelante
    digitalWrite(pin[0], LOW);
    digitalWrite(pin[1], HIGH);
  }else if(direccion == 0){
    // Freno
    digitalWrite(pin[0], LOW);
    digitalWrite(pin[1], LOW);
  }
}

int incomingByte = 0; 
Motor motor_izquierdo(2,4);
Motor motor_derecho(3,5);
void setup() { 
  Serial.begin(9600);
}

void loop() {
  // send data only when you receive data:
  if (Serial.available() > 0) {
          // read the incoming byte:
          incomingByte = Serial.read();
          Serial.println(incomingByte);
          if(incomingByte == 119){
            // ir hacia adelante 
            adelante();
          }else if(incomingByte == 97){
            // ir hacia la izquierda
            izquierda();
          }else if(incomingByte == 115){
            // Ir hacia atras
            atras();
          }else if(incomingByte == 100){
            // ir hacia derecha
            derecha();
          }else if(incomingByte == 102){
            // Detener movimiento
            detener();
          }
  }
}

void adelante(){
  motor_izquierdo.mover(1);
  motor_derecho.mover(1);
}

void atras(){
  motor_izquierdo.mover(-1);
  motor_derecho.mover(-1);
}

void izquierda(){
  motor_izquierdo.mover(0);
  motor_derecho.mover(1);
}

void derecha(){
  motor_izquierdo.mover(1);
  motor_derecho.mover(0);
}

void detener(){
  motor_izquierdo.mover(0);
  motor_derecho.mover(0);
}
