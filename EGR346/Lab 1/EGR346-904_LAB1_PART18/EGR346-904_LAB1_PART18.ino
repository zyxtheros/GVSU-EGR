/*
 * Course:  EGR 346-904
 * Name:    Caleb Capps
 * Date:    9/1/2022
 * 
 * Desc:  This project creates an 8-bit binary display
 *        that will show using 8 LEDs the binary 
 *        representation of a user-entered number from
 *        the serial monitor
 */
 /*
  * Equipment:
  *       8 X red LEDs
  *       8 X 100Ω ± 5% Resistors
  */

//Global Variables
int ledpin[8] = {2, 3, 4, 5, 6, 7, 8, 9};
int ledpin_size = sizeof(ledpin)/sizeof(ledpin[0]);

    
void setup() {

  Serial.begin(9600);
  // put your setup code here, to run once:
  for (int i = 0; i < ledpin_size; i++){ // step through the LED array elements
    pinMode(ledpin[i], OUTPUT); // make all LEDs outputs
  }
}
int mynum = 0,
    mynum_prev = mynum;
    
void loop() {
  while (mynum == mynum_prev){
    mynum = Serial.parseInt();
  }
  int mask = 0b00000001;
  for (int i = 0; i < ledpin_size; i++){ // step through the LED array elements
    Serial.print("Mask is\t");
    Serial.println(mask);
    if (mynum & mask) {
      Serial.print("Bit ");
      Serial.print(i);
      Serial.print(" is HIGH");
      digitalWrite(ledpin[i], HIGH);
    }
    else {
      digitalWrite(ledpin[i], LOW);
    }
    mask = mask << 1; // shift to the next bit
  }
  delay(500);
  mynum_prev = mynum;
}
