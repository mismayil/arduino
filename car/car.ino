// motor enable pins
#define ELEFT 10
#define ERIGHT 11

// motor control pins
#define CLEFT1 6
#define CLEFT2 7
#define CRIGHT1 8
#define CRIGHT2 9

// sensor trigger and echo pins
#define TRIG_FRONT A0
#define ECHO_FRONT A1
#define TRIG_LEFT A2
#define ECHO_LEFT A3
#define TRIG_RIGHT A4
#define ECHO_RIGHT A5
#define TRIG_BACK_RIGHT 2
#define ECHO_BACK_RIGHT 3
#define TRIG_BACK_LEFT 4
#define ECHO_BACK_LEFT 5
 
#define TRIG_DELAY 10
#define SENSOR_CONST 58
#define SAFE_DISTANCE 10

#define DELAY_TIME 5
//#define DEBUG

long getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(3);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(TRIG_DELAY);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  long distance = duration / SENSOR_CONST;

#ifdef DEBUG
  Serial.print("distance=");
  Serial.println(distance);
#endif

  return distance;
}

void goForwardLeft() {
#ifdef DEBUG
  Serial.println("going forward left");
#endif

  digitalWrite(ERIGHT, HIGH);
  digitalWrite(ELEFT, LOW);
  
  digitalWrite(CRIGHT1, HIGH);
  digitalWrite(CRIGHT2, LOW);
}

void goForwardRight() {
#ifdef DEBUG
  Serial.println("going forward right");
#endif

  digitalWrite(ELEFT, HIGH);
  digitalWrite(ERIGHT, LOW);
  
  digitalWrite(CLEFT1, HIGH);
  digitalWrite(CLEFT2, LOW);
}

void goBackwardLeft() {
#ifdef DEBUG
  Serial.println("going backward left");
#endif

  digitalWrite(ERIGHT, HIGH);
  digitalWrite(ELEFT, LOW);
  
  digitalWrite(CRIGHT1, LOW);
  digitalWrite(CRIGHT2, HIGH);
}

void goBackwardRight() {
#ifdef DEBUG
  Serial.println("going backward right");
#endif

  digitalWrite(ELEFT, HIGH);
  digitalWrite(ERIGHT, LOW);
  
  digitalWrite(CLEFT1, LOW);
  digitalWrite(CLEFT2, HIGH);
}

void goForward() {
#ifdef DEBUG
  Serial.println("going forward");
#endif
  
  digitalWrite(ERIGHT, HIGH);
  digitalWrite(ELEFT, HIGH);
  
  digitalWrite(CRIGHT1, HIGH);
  digitalWrite(CRIGHT2, LOW);
  digitalWrite(CLEFT1, HIGH);
  digitalWrite(CLEFT2, LOW);
}

void goBackward() {
#ifdef DEBUG
  Serial.println("going backward");
#endif

  digitalWrite(ERIGHT, HIGH);
  digitalWrite(ELEFT, HIGH);
  
  digitalWrite(CRIGHT1, LOW);
  digitalWrite(CRIGHT2, HIGH);
  digitalWrite(CLEFT1, LOW);
  digitalWrite(CLEFT2, HIGH);
}

void goRandom() {
  long randNum = random(6);

  switch (randNum) {
    case 0: goForward(); break;
    case 1: goBackward(); break;
    case 2: goForwardLeft(); break;
    case 3: goForwardRight(); break;
    case 4: goBackwardLeft(); break;
    case 5: goBackwardRight(); break;
    default: goForward();
  }
}

void setup() {
  pinMode(ELEFT, OUTPUT);
  pinMode(ERIGHT, OUTPUT); 

  pinMode(CLEFT1, OUTPUT);
  pinMode(CLEFT2, OUTPUT);
  pinMode(CRIGHT1, OUTPUT);
  pinMode(CRIGHT2, OUTPUT);

  pinMode(TRIG_FRONT, OUTPUT);
  pinMode(ECHO_FRONT, INPUT);
  pinMode(TRIG_LEFT, OUTPUT);
  pinMode(ECHO_LEFT, INPUT);
  pinMode(TRIG_RIGHT, OUTPUT);
  pinMode(ECHO_RIGHT, INPUT);
  pinMode(TRIG_BACK_RIGHT, OUTPUT);
  pinMode(ECHO_BACK_RIGHT, INPUT);
  pinMode(TRIG_BACK_LEFT, OUTPUT);
  pinMode(ECHO_BACK_LEFT, INPUT);

  digitalWrite(ELEFT, LOW);
  digitalWrite(ERIGHT, LOW);

#ifdef DEBUG
  Serial.begin(9600);
#endif
}

void loop() {
  
  long distFront = getDistance(TRIG_FRONT, ECHO_FRONT);
  long distLeft = getDistance(TRIG_LEFT, ECHO_LEFT);
  long distRight = getDistance(TRIG_RIGHT, ECHO_RIGHT);
  long distBackLeft = getDistance(TRIG_BACK_LEFT, ECHO_BACK_LEFT);
  long distBackRight = getDistance(TRIG_BACK_RIGHT, ECHO_BACK_RIGHT);
  
  if (distFront > SAFE_DISTANCE) goForward();
  else if (distBackLeft > SAFE_DISTANCE && distBackRight > SAFE_DISTANCE) goBackward();
  else if (distLeft > SAFE_DISTANCE) goForwardLeft();
  else if (distRight > SAFE_DISTANCE) goForwardRight();
  else if (distBackLeft > SAFE_DISTANCE) goBackwardLeft();
  else if (distBackRight > SAFE_DISTANCE) goBackwardRight();
  else goRandom();
}
