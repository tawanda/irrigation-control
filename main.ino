#include <TimeLib.h>
//https://github.com/PaulStoffregen/Time
//https://www.instructables.com/Using-Motors-With-L293D-IC/


String text;

const int button_1 = 2;     // the number of the pushbutton pin
const int button_2 = 3; 
const int ctrl_1 = 4;     // motor control
const int ctrl_2 = 5; 
const int ledPin =  13;      // the number of the LED pin
const int buttonDelay =  10900; 

// variables will change:
int valve_opened = 0;  // 0 == closed


void setup() {
  
   Serial.begin(9600);
   while (! Serial);
   Serial.println("");
   Serial.println("START PROGRAM");
   //setTime(hr,min,sec,day,mnth,yr);
   setTime(13,48,0,28,10,2020);
   print_date(); 
   
   // put your setup code here, to run once:
   pinMode(ledPin,OUTPUT);
   pinMode(button_1,INPUT);
   pinMode(button_2,INPUT);
   pinMode(ctrl_1,OUTPUT);
   pinMode(ctrl_2,OUTPUT);       

}

void print_date() {
  
     
  
   Serial.print("Time: ");
   Serial.print(hour()); 
   Serial.print(":");;
   Serial.print(minute()); 
   Serial.print(" ");
   Serial.print("Day of Week: ");
   Serial.print(weekday());
   Serial.print(" ");
   Serial.print("Month: ");
   Serial.print(month());
   Serial.print(" ");
   Serial.print("Year: ");
    Serial.println(year()); 
   
  }


void open_valve() {
    if (not valve_opened) {
      print_date(); 
      digitalWrite(ledPin, HIGH);
      digitalWrite(ctrl_1, HIGH);
      digitalWrite(ctrl_2, LOW);
      Serial.println("valve open");
      delay(buttonDelay);
      digitalWrite(ctrl_1, LOW);
      digitalWrite(ctrl_2, LOW);
      valve_opened = 1;
      
    }
}

void close_valve(){
    if (valve_opened) {
      print_date(); 
      // turn LED off:
      digitalWrite(ledPin, LOW);
      digitalWrite(ctrl_1, LOW);
      digitalWrite(ctrl_2, HIGH);
      Serial.println("valve close");
      delay(buttonDelay);
      digitalWrite(ctrl_1, LOW);
      digitalWrite(ctrl_2, LOW);
      valve_opened = 0;
    }
}
void loop() {
  
 if ( digitalRead(button_1) == HIGH) {
    Serial.println("button 1 pressed!!");
    open_valve();  
 } 
  
 if ( digitalRead(button_2) == HIGH) {
    Serial.println("button 2 pressed!!");
    close_valve(); 
 }
 // sunday is 1 sat is 7
 if (weekday() == 7 or weekday() == 3 or weekday() == 5  ) {
   if ( (hour() == 10 or (minute() == 1) ) and (not valve_opened) ){
     
      Serial.println("its time");
      open_valve();
   }

   if ( (hour() == 14) and (minute() == 1) and (valve_opened) ){
      
      Serial.println("irrigation done");
      close_valve();
   }
   
 }

 
  
}
