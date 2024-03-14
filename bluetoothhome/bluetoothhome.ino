//code for bluetooth controlled home//
//Author Jeslin Augustin//

#include <Keypad.h> //library for membrane keypad
#include <Servo.h> //library for servomotor

Servo myservo; //servo object creation

int led_in = 13; // pin to connect led
int heater_in = 12; // pin to connect heater control
int ac_in = 11; // pin to connect ac control

String readStr,in_bulb,in_ac,in_heater,a;

int pos = 0;
int mode=0;
const byte ROWS = 4; 
const byte COLS = 4; 

//variables for number lock check and processing
int index=0;
String password="";
String set_password="";

// key arrangement for keypad
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

//row and coloumn pin selection for keypad
byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

//keypad object
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

String no_lock="1234"; //default number lock is set to 1234

//function to operate the number lock door
void door_control(String set_password)
{
  char customKey = customKeypad.getKey();
  if (customKey && index<4)
  {
    password=password+String(customKey) ;
    index=index+1;
  }
  if (index>3 && password==set_password)
  {
    index=0;  
    password="";
    myservo.write(90);
    delay(1000);
    myservo.write(0);
  } 
  else if (index>3 && password!=set_password)
  {
  index=0;  
  password="";  
  }
}
//function to check and decode data received from bluetooth device
//bluetooth is connected to serial port 2

void check_bluetooth()
{
  while(Serial2.available())
  {
  a=Serial2.readString();
  Serial.println(a);
  }
  if (a=="A")
  {
  in_bulb="ON";
  }
  else if (a=="B")
  {
  in_bulb="OFF"; 
  }
  else if(a=="C")
  {
    in_heater="ON";
  }
  else if(a=="D")
  {
     in_heater="OFF";  
  }
  else if(a=="E")
  {
     in_ac="ON";
  }
  else if(a=="F")
  {
   in_ac="OFF";
  }
         
  if(a.indexOf("LOC") >=0) {
        readStr=a.substring(3);//reading the number lock value if the comand is to set the number lock
        Serial.print("LOC is: ");
        Serial.println(readStr);
        no_lock = readStr;
        Serial.println(no_lock); 
       a="";        
      }      
}


//function for bluetooth controlled operation
void bluetooth_mode()
{
  if (in_bulb=="ON")
  {
    digitalWrite(led_in,HIGH);
  }
  if (in_bulb=="OFF")
  {
    digitalWrite(led_in,LOW);
  }
  if (in_heater=="ON")
  {
    digitalWrite(heater_in,HIGH);
  }
  if (in_heater=="OFF")
  {
    digitalWrite(heater_in,LOW);
  }
  if (in_ac=="ON")
  {
    digitalWrite(ac_in,HIGH);
  }
  if (in_ac=="OFF")
  {
    digitalWrite(ac_in,LOW);
  }
}

//setup function
void setup()
{
Serial2.begin(9600);
Serial.begin(9600);
myservo.attach(10);
myservo.write(0);
pinMode(led_in,OUTPUT);
pinMode(heater_in,OUTPUT);
pinMode(ac_in,OUTPUT);
Serial.flush();
Serial2.flush();

}

//main loop function
void loop() 
{
   check_bluetooth();
   bluetooth_mode();

   set_password=no_lock;
   door_control(set_password) ;
    
}