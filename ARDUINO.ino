void setup() {
  Serial.begin(9600);       
  pinMode(8, OUTPUT);      
  Serial.println("Arduino Ready");
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command == "ON") {
      digitalWrite(8, HIGH);
      Serial.println("LED ON");
    } else if (command == "OFF") {
      digitalWrite(8, LOW);
      Serial.println("LED OFF");
    } else {
      Serial.println("Unknown command: " + command);
    }
  }
}
