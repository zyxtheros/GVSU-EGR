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
  Serial.println("Please enter a number between 0 and 255");
  // put your main code here, to run repeatedly:
  while(mynum == mynum_prev){ // wait for mynum to change
    mynum = Serial.parseInt(); // get the user integer input
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
  mynum_prev = mynum; //set the previous number to now be the new number
  delay(3000);
}

//  int mynum = 0,
//      mask = 0b00000001;
//  for ( ; mynum <256; mynum++){
//    
//    for (int i = 0; i < ledpin_size; i++){ // step through the LED array elements
//      //Serial.print("Mask is\t");
//      //Serial.println(mask);
//      if (mynum & mask) {
//        digitalWrite(ledpin[i], HIGH);
//      }
//      else {
//        digitalWrite(ledpin[i], LOW);
//      }
//      mask = mask << 1; // shift to the next bit
//    }
//    //delay(250);
//    for (int i = 0; i < ledpin_size; i++){ // step through the LED array elements
//      digitalWrite(ledpin[i], LOW);
//    }
//    
//    Serial.println(mynum);
//  }
