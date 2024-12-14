#define CLK D1 // Rotary encoder CLK pin
#define DT D2  // Rotary encoder DT pin
#define SW D3  // Rotary encoder switch pin

int lastStateCLK;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 5; // Debounce delay in milliseconds

void setup() {
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(SW, INPUT_PULLUP);

  Serial.begin(9600); // Start serial communication

  lastStateCLK = digitalRead(CLK);
}

void loop() {
  int currentStateCLK = digitalRead(CLK);
  unsigned long currentTime = millis();

  // Check for rotation
  if (currentStateCLK != lastStateCLK && (currentTime - lastDebounceTime > debounceDelay)) {
    lastDebounceTime = currentTime; // Update the debounce time

    if (digitalRead(DT) != currentStateCLK) {
      Serial.println("UP"); // Send 'UP' for volume up
    } else {
      Serial.println("DOWN"); // Send 'DOWN' for volume down
    }
  }

  lastStateCLK = currentStateCLK;

  // Check if the button is pressed
  if (digitalRead(SW) == LOW) {
    if (currentTime - lastDebounceTime > debounceDelay) {
      Serial.println("MUTE"); // Send 'MUTE' for mute toggle
      lastDebounceTime = currentTime;
    }
  }
}
