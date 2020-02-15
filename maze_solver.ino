#include <PID_v1.h>
#include<NewPing.h>

//Settings
int max_dist = 4000;
double Kp = 0.7, Ki = 0.1, Kd = 0.5;
int baseSpeed = 150;
int lExtSpeed = 30;  //Error
int turnTime = 350;
int uTurnTime = 750;
int goFowdTime = 250;
int thershold = 40;
int fThershold = 20; 
int outLowLim = 100;
int outHigLim = 225;

//Functions
void readSensors();
void lTurn();
void rTurn();
void stopAll();
void stabilize();
void goFowd();
void decide();
void uTurn();
void Print();
 
int lTrig = A0;
int fTrig = A1;
int rTrig = A2;
int lEcho = A3;
int fEcho = A4;
int rEcho = A5;

const int lFowd = 6; //Left Forward pwm
const int lBack = 4;
const int rBack = 7;
const int rFowd = 5; //Right Forward pwm

double lDist, rDist, fDist;
double mean;   

double lms = baseSpeed, rms = baseSpeed;

NewPing lSensor(lTrig, lEcho, max_dist);
NewPing fSensor(fTrig, fEcho, max_dist);
NewPing rSensor(rTrig, rEcho, max_dist);

PID lPid(&lDist, &lms, &mean, Kp, Ki, Kd, DIRECT);
PID rPid(&rDist, &rms, &mean, Kp, Ki, Kd, DIRECT);

void setup() {
  Serial.begin(9600);
  pinMode(rBack, OUTPUT);
  pinMode(rFowd, OUTPUT);
  pinMode(lBack, OUTPUT);
  pinMode(lFowd, OUTPUT);
  lPid.SetMode(AUTOMATIC);
  rPid.SetMode(AUTOMATIC);
  lPid.SetOutputLimits(outLowLim, outHigLim);
  rPid.SetOutputLimits(outLowLim, outHigLim);
}



void loop() {

  readSensors();
  stabilize();
  decide();
  stopAll();
}




void readSensors() {

  int iterations = 5;
  int lDura = lSensor.ping_median(iterations);
  delay(50);
  int fDura = fSensor.ping_median(iterations);
  delay(50);
  int rDura = rSensor.ping_median(iterations);
  delay(50);

  lDist = lSensor.convert_cm(lDura);
  fDist = fSensor.convert_cm(fDura);
  rDist = rSensor.convert_cm(rDura);
}

void lTurn(){
  
  digitalWrite(lFowd, LOW);
  digitalWrite(lBack, HIGH);
  digitalWrite(rFowd, HIGH);
  digitalWrite(rFowd, LOW);
  delay(turnTime);
}
void rTurn(){
  
  digitalWrite(rFowd, LOW);
  digitalWrite(rBack, HIGH);
  digitalWrite(lFowd, HIGH);
  digitalWrite(lBack, LOW);
  delay(turnTime);
}
void stopAll() {

  digitalWrite(rBack, LOW);
  digitalWrite(rFowd, LOW);
  digitalWrite(lBack, LOW);
  digitalWrite(lFowd, LOW);
}
void stabilize(){
  
  mean = (lDist+rDist)/2;
  lPid.Compute();
  rPid.Compute();
  
}
void goFowd() {

  analogWrite(lFowd, lms + lExtSpeed);
  digitalWrite(lBack, LOW);
  analogWrite(rFowd, rms);
  digitalWrite(rBack, LOW);
  delay(goFowdTime);
}
void uTurn()  {
  digitalWrite(lFowd, LOW);
  digitalWrite(lBack, HIGH);
  digitalWrite(rFowd, HIGH);
  digitalWrite(rFowd, LOW);
  delay(uTurnTime);
}
void decide() {
  
  if (lDist > thershold)
  {
     lTurn();
  }
  else if (fDist > fThershold)
  {
     goFowd();
  }
  else if (rDist > thershold)
  {
     rTurn();
  }
  else 
  {
     uTurn();
  }
}

void Print(){
Serial.print("Leftdistance = ");
Serial.println(lDist);
Serial.print("Rightdistance = ");
Serial.println(rDist);
Serial.print("Frontdistance = ");
Serial.println(fDist);  
Serial.print("Mean = ");
Serial.println(mean);
Serial.print("Lms = ");
Serial.println(lms);
Serial.print("Rms = ");
Serial.println(rms);
Serial.print("\n");
delay(3000);
}
