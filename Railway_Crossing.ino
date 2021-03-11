bool sensorState, prevState; // Variables for handling conditional states
bool mainFnRun;
unsigned long startMillis; // Variable for noting timestamp from the time code execution began
unsigned long currentMillis; // Variable for noting current timestamp called at anytime

/* // Ultrasonic Sensors Trial: */
int const trigPina = 7;
int const echoPina = 6;
int const trigPinb = 5;
int const echoPinb = 4;

 // PIR Sensor Trial:
int pirSen = 5; 

// Railway Signal Lights
int gled = 14; // Perfect GO
int yleda = 12; // If Single ON, next Signal is STOP (Red)
int yledb = 13; // Conditional Go, if YLEDA & YLEDB is ON
int rled = 15; // Perfect STOP
void setup() {
  pinMode(trigPina, OUTPUT); // trig pin will have pulses output
  pinMode(echoPina, INPUT); // ech pin will have pulses input
  pinMode (gled , OUTPUT);
  pinMode (yleda , OUTPUT);
  pinMode (yledb , OUTPUT);
  pinMode (rled , OUTPUT);
  pinMode (pirSen, INPUT);
  Serial.begin (9600); // Initializing Serial Monitor
  startMillis = millis();
}

void loop() {
  int durationA, distanceA;
  // Output pulse with 1ms width on trigPina
  digitalWrite(trigPina, HIGH);
  digitalWrite(trigPinb, HIGH);
  delay(1);
  digitalWrite(trigPina, LOW);
  digitalWrite(trigPinb, LOW);
  // Measure the pulse input in echo pin
  durationA = pulseIn(echoPina, HIGH); // Computing Duration
  // distanceA is half the durationA devided by 29.1 (from datasheet)
  distanceA = (durationA/2) / 29.1;
  Serial.println (distanceA); 
  sensorState = digitalRead(pirSen); //((distanceA <= 10 && distanceA >= 0)) ; // compressed if/else
  pirSensor(sensorState);

}
void pirSensor(bool value)
{
if (value == true) {
  startMillis = millis(); // Initializing timestamp from the time object is detected.
  PartialGo();
  delay (10000);
  if ((millis() - startMillis > 10000) && digitalRead(pirSen) == HIGH){ // if object detected for more than 10 sec
    Caution();
    delay(10000);
    if ((millis() - startMillis > 20000) && digitalRead(pirSen) == HIGH){
      if ((millis() - startMillis > 30000) && digitalRead(pirSen) == HIGH) { // if object detected for more than 30 sec
        Stop();
      }
      else{
        PartialGo();
      }
    }
    else{
      CompleteGo();
    }
  }
  else{
    CompleteGo();
  }
}
else{
  CompleteGo();
}
}

void CompleteGo(){ // Complete Go function 
  digitalWrite(gled, HIGH);
  digitalWrite(yleda, LOW);
  digitalWrite(yledb, LOW);
  digitalWrite(rled, LOW);
}

void PartialGo () {
  digitalWrite(gled, LOW);
  digitalWrite(yleda, HIGH);
  digitalWrite(yledb, HIGH);
  digitalWrite(rled, LOW);
}

void Caution (){
  digitalWrite(gled, LOW);
  digitalWrite(yleda, LOW);
  digitalWrite(yledb, HIGH);
  digitalWrite(rled, LOW);
}

void Stop() {
  digitalWrite(gled, LOW);
  digitalWrite(yleda, LOW);
  digitalWrite(yledb, LOW);
  digitalWrite(rled, HIGH);
}