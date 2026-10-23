/*
 * 3-SENSOR Line Follower - SMOOTH TURNING FIXED
 * - No more backward movement during turns
 * - Smooth differential steering
 */

#include <AFMotor.h>

// --- Motor Setup ---
AF_DCMotor motorLeft(1);   
AF_DCMotor motorRight(2);  

// --- Sensor Setup ---
const int pinLeft = A0;
const int pinRight = A1;
const int pinMiddle = A2;

// --- SETTINGS ---
int threshold = 500; 

// --- SPEED CONTROLS ---
int speedForward = 200;    // Reduced for better control
int speedTurn = 150;       // Slower speed for turning
int speedSlow = 100;       // Even slower for inner wheel

void setup() {
  Serial.begin(9600);
  Serial.println("=== SMOOTH Line Follower ===");

  motorLeft.setSpeed(speedForward);
  motorRight.setSpeed(speedForward);
  
  stopMotors();
  delay(2000); 
}

void loop() {
  int valL = analogRead(pinLeft);
  int valR = analogRead(pinRight);
  int valM = analogRead(pinMiddle);

  // Detect BLACK line
  bool L_black = (valL < threshold);
  bool R_black = (valR < threshold);  
  bool M_black = (valM < threshold);

  // Debug 
  Serial.print("L:"); Serial.print(valL);
  Serial.print(L_black ? "[B]" : "[W]");
  Serial.print(" M:"); Serial.print(valM);
  Serial.print(M_black ? "[B]" : "[W]");
  Serial.print(" R:"); Serial.print(valR);
  Serial.print(R_black ? "[B]" : "[W]");
  Serial.print(" → ");

  // --- SMOOTH TURNING LOGIC ---

  // 1. ONLY MIDDLE DETECTS BLACK - GO FORWARD
  if (!L_black && M_black && !R_black) {
    Serial.println("FORWARD");
    moveForward();
  }

  // 2. NO BLACK DETECTED - STOP 
  else if (!L_black && !M_black && !R_black) {
    Serial.println("STOP");
    stopMotors();
  }

  // 3. ALL THREE DETECT BLACK - STOP
  else if (L_black && M_black && R_black) {
    Serial.println("STOP - Intersection");
    stopMotors();
  }

  // 4. LEFT DETECTS BLACK - GENTLE RIGHT TURN
  else if (L_black && !M_black && !R_black) {
    Serial.println("GENTLE RIGHT");
    gentleRight();
  }

  // 5. RIGHT DETECTS BLACK - GENTLE LEFT TURN
  else if (!L_black && !M_black && R_black) {
    Serial.println("GENTLE LEFT");
    gentleLeft();
  }

  // 6. MIDDLE + LEFT DETECT - MEDIUM RIGHT TURN
  else if (L_black && M_black && !R_black) {
    Serial.println("MEDIUM RIGHT");
    mediumRight();
  }

  // 7. MIDDLE + RIGHT DETECT - MEDIUM LEFT TURN
  else if (!L_black && M_black && R_black) {
    Serial.println("MEDIUM LEFT");
    mediumLeft();
  }

  // Default - STOP for safety
  else {
    Serial.println("STOP (default)");
    stopMotors();
  }

  delay(50);
}

// --- SMOOTH MOVEMENT FUNCTIONS ---

void moveForward() {
  motorLeft.setSpeed(speedForward);   
  motorRight.setSpeed(speedForward);  
  motorLeft.run(FORWARD);
  motorRight.run(FORWARD);
}

// GENTLE TURNS - Both wheels forward, one slightly slower
void gentleLeft() {
  motorLeft.setSpeed(speedSlow);     // Left wheel slower
  motorRight.setSpeed(speedForward); // Right wheel normal
  motorLeft.run(FORWARD);            // BOTH WHEELS FORWARD
  motorRight.run(FORWARD);
}

void gentleRight() {
  motorLeft.setSpeed(speedForward);  // Left wheel normal
  motorRight.setSpeed(speedSlow);    // Right wheel slower
  motorLeft.run(FORWARD);            // BOTH WHEELS FORWARD
  motorRight.run(FORWARD);
}

// MEDIUM TURNS - One wheel normal, one very slow
void mediumLeft() {
  motorLeft.setSpeed(80);            // Left wheel very slow
  motorRight.setSpeed(speedForward); // Right wheel normal
  motorLeft.run(FORWARD);            // BOTH WHEELS FORWARD
  motorRight.run(FORWARD);
}

void mediumRight() {
  motorLeft.setSpeed(speedForward);  // Left wheel normal
  motorRight.setSpeed(80);           // Right wheel very slow
  motorLeft.run(FORWARD);            // BOTH WHEELS FORWARD
  motorRight.run(FORWARD);
}

void stopMotors() {
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
}