boolean sensorState, prevState;
unsigned long startMillis;

//int const trigPina = 7;
//int const echoPina = 6;
//int const trigPinb = 5;
//int const echoPinb = 4;
int pirSen = 5;

int gled = 14;
int yleda = 12;
int yledb = 13;
int rled = 15;
void setup() {
  //pinMode(trigPina, OUTPUT); // trig pin will have pulses output
  //pinMode(echoPina, INPUT);
  pinMode (gled , OUTPUT);
  pinMode (yleda , OUTPUT);
  pinMode (yledb , OUTPUT);
  pinMode (rled , OUTPUT);
  pinMode (pirSen, INPUT);
  Serial.begin (9600);
}

void loop() {
  //int durationA, distanceA;
  // Output pulse with 1ms width on trigPina
  /*digitalWrite(trigPina, HIGH);
  digitalWrite(trigPinb, HIGH);
  delay(1);
  digitalWrite(trigPina, LOW);
  digitalWrite(trigPinb, LOW);
  // Measure the pulse input in echo pin
  durationA = pulseIn(echoPina, HIGH);
  // distanceA is half the durationA devided by 29.1 (from datasheet)
  distanceA = (durationA/2) / 29.1;
  Serial.println (distanceA); */
  sensorState = digitalRead(pirSen); //((distanceA <= 10 && distanceA >= 0)) ; // compressed if/else
  if (sensorState == LOW) { // if >=1000
    if (!prevState) startMillis = millis(); { // mark if just changed to >=1000
      if ((millis() - startMillis > 1000) && (millis() - startMillis <= 2500)) {
      digitalWrite(yleda, HIGH);
      digitalWrite (yledb , HIGH);
      digitalWrite(rled, LOW);
      digitalWrite(gled, LOW);
      Serial.println(millis()-startMillis);
      delay (1000);// compressed if/else
      digitalWrite(yleda, HIGH);
      digitalWrite(yledb, HIGH);
      digitalWrite(rled, LOW);
      digitalWrite(gled, LOW);
      Serial.println(millis()-startMillis);
    }
      if ((millis() - startMillis > 2500) && (millis() - startMillis >= 6000)) {
      digitalWrite(yleda, HIGH);
      digitalWrite(yledb, LOW);
      digitalWrite(rled, LOW);
      digitalWrite(gled, LOW);
      Serial.println(millis()-startMillis);
      delay (1000);
      digitalWrite(yleda, HIGH);
      digitalWrite(yledb, LOW);
      digitalWrite(rled, LOW);
      digitalWrite(gled, LOW);
      Serial.println(millis()-startMillis);
    } 
      if (millis() - startMillis > 7000) {
      digitalWrite(yleda, LOW);
      digitalWrite(yledb, LOW);
      digitalWrite(rled, HIGH);
      digitalWrite(gled, LOW);
      Serial.println(millis()-startMillis);
      delay (1000);
      digitalWrite(yleda, LOW);
      digitalWrite(yledb, LOW);
      digitalWrite(rled, HIGH);
      digitalWrite(gled, LOW);
      Serial.println(millis()-startMillis);
    } 
   } 
  }
    else { // if <1000
    digitalWrite(rled, LOW);
    digitalWrite(yleda, LOW);
    digitalWrite(yledb, LOW);
    digitalWrite (gled, HIGH);
  }
  prevState = sensorState; 
  delay (1000);
}
