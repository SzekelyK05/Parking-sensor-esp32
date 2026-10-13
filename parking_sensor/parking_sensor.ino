#define SOUND_VELOCITY 0.034
#define trigPin 18
#define echoPin 19
#define buzzerPin 4
#define greenLed 21
#define yellowLed 22
#define redLed 23

const int note = 500;

// Timers
unsigned long previousBeepMillis = 0;
unsigned long previousPingMillis = 0;
const int pingInterval = 60;

bool isPlaying = false;
int currentState = -1;

// Ultrasonic variables
long duration;
float distanceCm = 999;

void setup() {
  Serial.begin(115200);
  pinMode(greenLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousPingMillis >= pingInterval) {
    previousPingMillis = currentMillis;
    handleUltrasonic();
  }

  int targetState = 0;

  if (distanceCm >= 12 && distanceCm <= 17) {
    targetState = 1;
  } else if (distanceCm >= 7.5 && distanceCm < 11.5) {
    targetState = 2;
  } else if(distanceCm < 7) {
    targetState = 3;
  }
  

  if (targetState != currentState) {

    if (targetState == 0) {
      digitalWrite(greenLed, LOW);
      digitalWrite(yellowLed, LOW);
      digitalWrite(redLed, LOW);
      noTone(buzzerPin);
      isPlaying = false;
    }
    else if (targetState == 1) {
      digitalWrite(greenLed, HIGH);
      digitalWrite(yellowLed, LOW);
      digitalWrite(redLed, LOW);
      noTone(buzzerPin);
      isPlaying = false;
      previousBeepMillis = currentMillis;
    }
    else if (targetState == 2) {
      digitalWrite(greenLed, LOW);
      digitalWrite(yellowLed, HIGH);
      digitalWrite(redLed, LOW);
      noTone(buzzerPin);
      isPlaying = false;
      previousBeepMillis = currentMillis;
    }

    else if (targetState == 3) {
      digitalWrite(greenLed, LOW);
      digitalWrite(yellowLed, LOW);
      digitalWrite(redLed, HIGH);
      tone(buzzerPin, note);
      isPlaying = true;
    }
    currentState = targetState;
  }

  if (currentState == 1) {
    playSound(500);
  } else if (currentState == 2) {
    playSound(250);
  }
}

void playSound(int interval) {
  unsigned long currentMillis = millis();

  if (currentMillis - previousBeepMillis >= interval) {
    previousBeepMillis = currentMillis;

    if (isPlaying) {
      noTone(buzzerPin);
      isPlaying = false;
    } else {
      tone(buzzerPin, note);
      isPlaying = true;
    }
  }
}

void handleUltrasonic() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000);
  
  static int timeoutCount = 0;
  float rawDistance;

  if (duration == 0) {
    timeoutCount++;
    if (timeoutCount > 3) {
      rawDistance = 999; 
    } else {
      rawDistance = distanceCm;
    }
  } else {
    timeoutCount = 0; 
    rawDistance = duration * SOUND_VELOCITY / 2;
  }

  if (distanceCm == 999) {
    distanceCm = rawDistance;
  } else {
    distanceCm = (distanceCm * 0.8) + (rawDistance * 0.2); 
  }

}