void setup() {
  // initialize serial:
  Serial.begin(9600);
}

void loop() {
  // if there's any serial available, read it:
  while (Serial.available() > 0) {

    // look for the next valid integer in the incoming serial stream:
    int in = Serial.parseInt();
    Serial.print("Parsed: ");
    Serial.println(in);
  }
}
