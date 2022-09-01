
void setup() {
  Serial.begin(9600);         // Sets the serial communication baud rate to 9600
}
String message;               // Initializes the string variable message where the user's name is stored
void loop() {
  Serial.println("Please enter your name");             // User prompted for their name
  while(Serial.available()==0){};                       // Delays the program until enter is pressed
  message = Serial.readString();                        // Reads and assigns the user's name to message
  Serial.print("Thanks for giving us your name ");     
  Serial.println(message);                              // Reprints the users name
