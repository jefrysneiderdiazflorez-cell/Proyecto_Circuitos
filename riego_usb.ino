/*
  PROJECT: AUTOMATIC IRRIGATION SYSTEM
  BOARD: ARDUINO MEGA 2560

  INPUTS:
  D2 = Pulsador manual con resistencia externa PULL-DOWN
  D6 = Sensor digital de humedad (DO)

  OUTPUTS:
  D3 = Modulo rele de la bomba
  D8 = Buzzer

  COMMUNICATION:
  UART - 9600 baudios
*/

// --------------------------------
// 1. PIN DEFINITIONS
// --------------------------------

const int PIN_BUTTON = 2;
const int PIN_SENSOR = 6;
const int PIN_RELAY  = 3;
const int PIN_BUZZER = 8;


// --------------------------------
// 2. COMPONENT CONFIGURATION
// --------------------------------

// Logica del sensor:
// HIGH = suelo humedo
// LOW  = suelo seco

const int SENSOR_DRY = LOW;

// Logica del rele:
// Basada en la configuracion del proyecto.
// Si el rele funciona al contrario, invertir estos valores.

const int RELAY_ON  = HIGH;
const int RELAY_OFF = LOW;


// --------------------------------
// 3. SYSTEM VARIABLES
// --------------------------------

bool pumpActive = false;

bool stableButton = false;
bool lastButtonReading = false;

unsigned long debounceTime = 0;
unsigned long lastReport = 0;

const unsigned long DEBOUNCE_DELAY = 40;
const unsigned long REPORT_INTERVAL = 500;


// --------------------------------
// 4. INITIAL SETUP
// --------------------------------

void setup() {

  Serial.begin(9600);

  // Entradas
  pinMode(PIN_BUTTON, INPUT);   // pull-down externo, no INPUT_PULLUP
  pinMode(PIN_SENSOR, INPUT);

  // Salidas
  digitalWrite(PIN_RELAY, RELAY_OFF);
  pinMode(PIN_RELAY, OUTPUT);

  pinMode(PIN_BUZZER, OUTPUT);

  // Estado inicial
  digitalWrite(PIN_BUZZER, LOW);

  Serial.println("--------------------------------");
  Serial.println(" AUTOMATIC IRRIGATION SYSTEM");
  Serial.println(" ARDUINO MEGA 2560");
  Serial.println("--------------------------------");

  Serial.println("System started successfully");

}


// --------------------------------
// 5. BUTTON READING (DEBOUNCE)
// --------------------------------

bool readButton() {

  bool currentReading = digitalRead(PIN_BUTTON);

  // Si la lectura cambia, se reinicia el temporizador de rebote
  if (currentReading != lastButtonReading) {

    debounceTime = millis();

    lastButtonReading = currentReading;
  }

  // Solo se acepta el estado si es estable durante DEBOUNCE_DELAY
  if (millis() - debounceTime >= DEBOUNCE_DELAY) {

    stableButton = currentReading;

  }

  return stableButton;
}


// --------------------------------
// 6. MAIN CONTROL
// --------------------------------

void loop() {

  // Leer sensor de humedad
  int sensorReading = digitalRead(PIN_SENSOR);

  bool soilDry = (sensorReading == SENSOR_DRY);


  // Leer pulsador manual
  bool buttonPressed = readButton();


  // Decidir si activar el riego
  // Se activa si el suelo esta seco
  // O si el usuario presiona el boton (prioridad manual)

  bool irrigationRequested = soilDry || buttonPressed;


  // --------------------------------
  // 7. RELAY AND PUMP CONTROL
  // --------------------------------

  if (irrigationRequested != pumpActive) {

    pumpActive = irrigationRequested;

    digitalWrite(
      PIN_RELAY,
      pumpActive ? RELAY_ON : RELAY_OFF
    );


    // Activar buzzer al cambiar de estado

    tone(PIN_BUZZER, 1000, 200);


    if (pumpActive) {

      Serial.println("PUMP ON");

    } else {

      Serial.println("PUMP OFF");

    }

  }


  // --------------------------------
  // 8. SERIAL COMMUNICATION
  // --------------------------------

  if (millis() - lastReport >= REPORT_INTERVAL) {

    lastReport = millis();

    Serial.println("--------- SYSTEM STATUS ---------");

    Serial.print("Sensor: ");

    Serial.println(sensorReading);

    Serial.print("Soil moisture: ");

    Serial.println(soilDry ? "DRY" : "WET");

    Serial.print("Manual button: ");

    Serial.println(buttonPressed ? "PRESSED" : "RELEASED");

    Serial.print("Pump: ");

    Serial.println(pumpActive ? "ON" : "OFF");

    Serial.println("---------------------------------");

  }

  delay(20);

}
