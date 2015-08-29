// comment

char inByte;
int ledPin = 13;:q
int powerPin = 7;
int readPin = 0; // Analog A0


void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(powerPin, OUTPUT);

  // start serial port at 9600 bps
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
}

void loop() {
  // if we get a valid byte, read analog ins:
  if (Serial.available() > 0) {
    // get incoming byte:
    inByte = Serial.read(); // we don care what we read...
    measure();
  }
}

void measure() {
  int val;
  
  digitalWrite(ledPin, HIGH);
  digitalWrite(powerPin, HIGH);
  delay(1000); // wait a bit for the current to flow before we measure
  val = analogRead(readPin);
  digitalWrite(ledPin, LOW);
  digitalWrite(powerPin, LOW);
  delay(100);
  sendMessage(val);
}

void sendMessage(int v) { 
  Serial.print("{\"soil\": ");
  Serial.print(v);
  Serial.println("}");
}
