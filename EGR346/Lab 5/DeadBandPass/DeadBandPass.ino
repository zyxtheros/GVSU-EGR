#define c_kinetic_pos 8 /* static friction */
#define c_kinetic_neg 8 /* make the value positive */
#define c_static_pos 8 /* kinetic friction */
#define c_static_neg 8 /* make the value positive */
#define c_max 255
#define c_min 255 /* make the value positive */

int moving = 0; /* assume it starts without moving */
int count = 0;
int db_correct = 0;
char incomingByte;

//Pin Definitions
int EN12  = 11,
    IN1   = 10,
    IN2   = 9;


void setup() {
  Serial.begin(9600); // Opens serial port and sets the data rate to 9600 bits-per-second
  Serial.println("---------------------------------------------");
  Serial.println("\n\rDeadBand Compensation application");
  Serial.println("---------------------------------------------");
  Serial.println("Press '+' to increment counter ");
  Serial.println("Press '-' to decrement counter ");
  Serial.println("Press 'p' to display counter value and deadband compensation status");
  Serial.println("Press 'd' to enable or disable (default) deadband compensation");
  Serial.println("Press 'h' to display HELP ");
  Serial.println("Press 'q' to quit ");
  IO_setup();
}
void loop() {
  if (Serial.available() > 0) { // print data only when you receive data:
    incomingByte = Serial.read(); // read the incoming byte:
    if (incomingByte == '+') {
      Serial.print("You entered ");
      Serial.print(incomingByte);
      Serial.println(". So counter incremented");
      if (++count > 255) count = 255;
      if (count == 1) { // it has just started moving
        moving = 0;
        IO_update();
        delay(200);
        moving = 1;
      }
      IO_update();
    }
    if (incomingByte == '-') {
      Serial.print("You entered ");
      Serial.print(incomingByte);
      Serial.println(". So counter decremented");
      if (--count < -255) count = -255;
      if (count == -1) { // it has just started moving
        moving = 0;
        IO_update();
        delay(200);
        moving = 1;
      }
      IO_update();
    }
    if (incomingByte == 'd') {
      if (db_correct == 0) {
        db_correct = 1;
        Serial.print("You entered ");
        Serial.print(incomingByte);
        Serial.println(". So DeadBand Compensation is ON");
      }
      else {
        db_correct = 0;
        Serial.print("You entered ");
        Serial.print(incomingByte);
        Serial.println(". So DeadBand Compensation is OFF ");
      }
      IO_update();
    }
    if (incomingByte == 'p') {
      Serial.print("Count is: ");
      Serial.println(count);
      Serial.print("Deadband is: ");
      Serial.println(db_correct);
    }
    if (incomingByte == 'h') {
      Serial.println(" +: increment value");
      Serial.println(" -: decrement value");
      Serial.println(" d: enable or disable (default) deadband comp.");
      Serial.println(" q: quit");
    }
    if (incomingByte == 'q') {
      count = 0;
      moving = 0;
      IO_update();
      Serial.println("GOOD-BYE !!!");
      delay(1000);
      exit(1);
    }
    Serial.println("---------------------------------------------");
    Serial.println("\n\rDeadBand Compensation application");
    Serial.println("---------------------------------------------");
    Serial.println("Press '+' to increment counter ");
    Serial.println("Press '-' to decrement counter ");
    Serial.println("Press 'p' to display counter value and deadband compensation status");
    Serial.println("Press 'd' to enable or disable (default) deadband compensation");
    Serial.println("Press 'h' to display HELP ");
  }
}

int deadband(int c_wanted) { /* call this routine when updating */
  int c_pos;
  int c_neg;
  int c_adjusted;
  if (moving == 1) {
    c_pos = c_kinetic_pos;
    c_neg = c_kinetic_neg;
  }
  else {
    c_pos = c_static_pos;
    c_neg = c_static_neg;
  }
  if (c_wanted == 0) { /* turn off the output */
    c_adjusted = 0;
  }
  else if (c_wanted > 0) { /* a positive output */
    c_adjusted = c_pos + (unsigned)(c_max - c_pos) * c_wanted / c_max;
    if (c_adjusted > c_max) c_adjusted = c_max;
  }
  else { /* the output must be negative */
    c_adjusted = -c_neg - (unsigned)(c_min - c_neg) * -c_wanted / c_min;
    if (c_adjusted < -c_min) c_adjusted = -c_min;
  }
  return c_adjusted;
}

int v_output(int v_adjusted) { /* call from the loop through IO_update*/
  int RefSignal; // the value to be returned
  if (v_adjusted >= 0) { /* set the direction bits to CW on, CCW off */
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(EN12, count);
    if (v_adjusted > 255) { /* clip output over maximum */
      RefSignal = 255;
    }
    else {
      RefSignal = v_adjusted;
    }
  }
  else {
    /* need to reverse output sign *//* set the direction bits to CW off, CCW on */
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(EN12, count);
    if (v_adjusted < -255) { /* clip output below minimum */
      RefSignal = 255;
    }
    else {
      RefSignal = -v_adjusted; /* flip sign */
    }
  }
  return RefSignal;
}
void IO_setup(void) { // this function configures the pins to be used
  pinMode(EN12, OUTPUT);
  digitalWrite(EN12, HIGH); // turn on the enable bit
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
}
void IO_update() {
  int Refsignal;

  IO_setup();
  if (db_correct == 0) {
    Refsignal = v_output(count);
  }

  else {
    Refsignal = v_output(deadband(count));
  }
  analogWrite(5, Refsignal);

  Serial.print("count is ");
  Serial.println(count);
  Serial.print("v_output is ");
  Serial.println(Refsignal);
}
