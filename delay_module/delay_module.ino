// Pin Definitions (Using Arduino/Logical mapping)
const int triggerPin = 3;  // Physical Pin 2
const int outputPin  = 1;  // Physical Pin 6
const int onPotPin   = A1; // Physical Pin 3 (Analog 2)
const int offPotPin  = A2; // Physical Pin 7 (Analog 1)
const long maxWaitTime  = 60000; // 60,000 miliseconds is 60 seconds

void setup() {
  pinMode(triggerPin, INPUT);
  pinMode(outputPin, OUTPUT);
  digitalWrite(outputPin, LOW); // Ensure it starts OFF
}

void loop() {
  // 1. Wait for the signal on Physical Pin 2 to go HIGH
  if (digitalRead(triggerPin) == HIGH) {
    delay(50); // "Debounce" - wait for the signal to stabilize
    if (digitalRead(triggerPin) == LOW) return; // If it was just noise, ignore it
    
    // 2. Read the pots (0-1023) and map to max wait time
    // We use 'long' because 60,000 exceeds the capacity of a standard 'int'
    // Read the pots and subtract from 1023 to flip the direction
    int onRead  = 1023 - analogRead(onPotPin);
    int offRead = 1023 - analogRead(offPotPin);

    // Map the inverted values to our time range
    long onDuration  = map(onRead, 0, 1023, 0, maxWaitTime);
    long offDuration = map(offRead, 0, 1023, 0, maxWaitTime);

    // 3. Turn output ON
    digitalWrite(outputPin, HIGH);
    delay(onDuration);

    // 4. Turn output OFF
    digitalWrite(outputPin, LOW);
    
    // 5. Mandatory wait (ignores all input during this time)
    delay(offDuration);
    
    // 6. Loop restarts and waits for next HIGH signal on triggerPin
  }
}