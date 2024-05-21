int last_direction  = 0;    //variable declaration
int robot_speed     = 150;  //Set the Robot Speed

#define DELAYMS 10

#define FORWARD     0   //flag define
#define HARD_LEFT   1   //flag define
#define HARD_RIGHT  2   //flag define
#define SOFT_LEFT   3   //flag define
#define SOFT_RIGHT  4   //flag define

#define leftMotorPWM  10  
#define rightMotorPWM 11  
#define leftSensor    12
#define rightSensor   13

#define leftMotor1  2
#define leftMotor2  3
#define rightMotor1 4
#define rightMotor2 5




#define trigPin A0
#define echoPin A1

int search(void)
{
      float duration = 0.00;
      float CM = 0.00;
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      CM = (duration / 58.82);
      return CM;
}

void setup()
{
  //Serial.begin(9600);
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  pinMode(leftMotorPWM, OUTPUT);
  pinMode(rightMotorPWM, OUTPUT);

  delay(100);
  pinMode(leftSensor, INPUT);
  pinMode(rightSensor, INPUT);
  delay(100);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  delay(100);
  
  analogWrite(leftMotorPWM, robot_speed);
  analogWrite(rightMotorPWM, robot_speed);
  delay(100);


}


void loop()
{
  int left_reading = digitalRead(leftSensor);
  int right_reading = digitalRead(rightSensor);
  float distance = 0.00;
  float RobotSpeed = 0.00;
  distance = search();

  if ((distance < 10)) // forcalculating the distance from the obstacle in cm
  {
      RobotStop();
  }

  else if(left_reading==1 && right_reading==1) // When both sensors are on black line
   {
      //Serial.println("forward");
      robot_move(FORWARD);                //move FORWARD
      last_direction=FORWARD;             //save FORWARD in the variable named last direction
    }
  else if(left_reading==1 && right_reading==0) // When left sensor is on black line
   {
      //Serial.println("soft left");
      robot_move(SOFT_LEFT);              //move left
      last_direction=HARD_LEFT;           //save left in the variable named last direction
   }
  
  else if(left_reading==0 && right_reading==1)// When right sensor is on black line
   {
      //Serial.println("soft right");
      robot_move(SOFT_RIGHT);            //move right
      last_direction=HARD_RIGHT;         //save right in the variable named last direction
   }
  
  else if (left_reading==0 && right_reading==0)// When none of the sensors is on black line
   {
      //Serial.println("memory");
      robot_move(last_direction);       //move to last direction
   }
  delay(DELAYMS);
}



void robot_move(int direc)              //define a function named robot_move which will return direction
{
  if (direc == FORWARD)        {digitalWrite(leftMotor1, LOW); digitalWrite(leftMotor2, HIGH); digitalWrite(rightMotor1, HIGH); digitalWrite(rightMotor2, LOW); }  
  else if (direc == SOFT_LEFT) {digitalWrite(leftMotor1, LOW); digitalWrite(leftMotor2, LOW);  digitalWrite(rightMotor1, HIGH); digitalWrite(rightMotor2, LOW); }  
  else if (direc == HARD_LEFT) {digitalWrite(leftMotor1, HIGH); digitalWrite(leftMotor2, LOW); digitalWrite(rightMotor1, HIGH); digitalWrite(rightMotor2, LOW); }  
  else if (direc == SOFT_RIGHT){digitalWrite(leftMotor1, LOW); digitalWrite(leftMotor2, HIGH); digitalWrite(rightMotor1, LOW);  digitalWrite(rightMotor2, LOW); }  
  else if (direc == HARD_RIGHT){digitalWrite(leftMotor1, LOW); digitalWrite(leftMotor2, HIGH); digitalWrite(rightMotor1, LOW);  digitalWrite(rightMotor2, HIGH);}  
}

void RobotStop()
{digitalWrite(leftMotor1, LOW); digitalWrite(leftMotor2, LOW); digitalWrite(rightMotor1, LOW);  digitalWrite(rightMotor2, LOW);}
