// Pin Definitions (Using Arduino/Logical mapping)
const int triggerPin = 3;  // Physical Pin 2
const int outputPin  = 1;  // Physical Pin 6
const int onPotPin   = A1; // Physical Pin 3 (Analog 1)
const int offPotPin  = A2; // Physical Pin 7 (Analog 2)
const int modePin    = 0;  // Physical Pin 5 (Digital 0)

const long maxWaitTime = 60000; // 60,000 miliseconds is 60 seconds

void setup() {
  pinMode(outputPin, OUTPUT);
  digitalWrite(outputPin, LOW); 
  
  pinMode(triggerPin, INPUT);
  pinMode(modePin, INPUT); // Switch pin
}

void loop() {
  // 1. Wait for the signal on Physical Pin 2 to go HIGH
  if (digitalRead(triggerPin) == HIGH) {
    delay(50); // Debounce
    if (digitalRead(triggerPin) == LOW) return; 

    // 2. Read the pots and map to time range
    int onRead  = 1023 - analogRead(onPotPin);
    int offRead = 1023 - analogRead(offPotPin);

    long onDuration  = map(onRead, 0, 1023, 0, maxWaitTime);
    long offDuration = map(offRead, 0, 1023, 0, maxWaitTime);

    // 3. Check Mode Pin (Physical Pin 5)
    // HIGH = Reversed (Wait then Pulse)
    // LOW  = Normal (Pulse then Wait)
    if (digitalRead(modePin) == HIGH) {
      // REVERSED ORDER: OFF first, then ON
      digitalWrite(outputPin, LOW);
      delay(offDuration);
      
      digitalWrite(outputPin, HIGH);
      delay(onDuration);
      
      digitalWrite(outputPin, LOW); // Ensure it ends in OFF state
    } 
    else {
      // NORMAL ORDER: ON first, then OFF
      digitalWrite(outputPin, HIGH);
      delay(onDuration);

      digitalWrite(outputPin, LOW);
      delay(offDuration);
    }
    
    // Loop restarts and waits for next trigger
  }
}