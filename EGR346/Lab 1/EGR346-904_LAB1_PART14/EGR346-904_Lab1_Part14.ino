/* EGR 345-904 Lab 1 #14
   Name: Grant Lubbert & Caleb Capps
   Date: 09/01/2022

   This program reads ana analog input from a potentiometer hooked up to 5V. The analog values are
   converted to the relative voltage between 0V and 5V value and displayed on the serial moniter.
*/

#define LED A4

void setup() {
  pinMode(LED, INPUT);       // Sets the LED pin, A4, to input
  Serial.begin(9600);        // Sets the serial communication baud rate to 9600
}

float voltage;               // Initializes the voltage variable
void loop() {
  voltage = analogRead(LED)*5.0/1023.0;     // Reads in the analog value and converts to voltage
  Serial.print("Voltage: ");                  
  Serial.println(voltage);                  // Prints the voltage allowed by the potentiameter
  delay(500);                               // Delays the program by 0.5 seconds
}
