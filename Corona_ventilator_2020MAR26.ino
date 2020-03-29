#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

#define in1 7           ////// driver Input 1   
#define in2 6           ////// driver Input 2
#define motor_speed 5  ////// driver Input PWM

#define pot A5           /////// Potentiometer
int pot_speed = 0;

#define buttonPin A0          //////// count limit switch
// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button


#define but2 5          /////// count reset/exit switch
#define up_but 3        /////// up navigation
#define down_but 4      /////// down navigation 
#define ok_but 2       /////// ok button 
int but1buf = 1;
int but2buf = 1;
int up_buf = 1;
int down_buf = 1;
int ok_buf = 1;
int exit_buf = 1;
int i=0;
int flag = 0;
void setup()
{
  Serial.begin(9600);
  pinMode(buttonPin,INPUT_PULLUP);
  pinMode(but2,INPUT_PULLUP);
  pinMode(up_but,INPUT_PULLUP);
  pinMode(down_but,INPUT_PULLUP);
  pinMode(ok_but,INPUT_PULLUP);
  pinMode(pot,INPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(motor_speed, OUTPUT);

  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("WELCOME");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("CORONA");
  lcd.setCursor(0,1);
  lcd.print("VENTILATOR");
    //digitalWrite(in1, LOW);
  //digitalWrite(in2, HIGH);
  delay(2000);
}
void loop()
{
  menu();
  count();
}
void count()
{
  buttonState = digitalRead(buttonPin);
  if (buttonState != lastButtonState) {
  if (buttonState == HIGH) {
  buttonPushCounter++;
  }
  else {}
  }
  delay(50);
  lastButtonState = buttonState;
  
  //but1buf = digitalRead(but1);
  lcd.setCursor(12,1);
  lcd.print(buttonPushCounter);
  Serial.println(buttonPushCounter);
  
}
void TurnOFF_motor(){
  buttonPushCounter = 0;
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(motor_speed,0);
}
void TurnMotor_speed1()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(motor_speed,85);
}
void TurnMotor_speed2()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(motor_speed,170);
}
void TurnMotor_speed3()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(motor_speed,255);
}
void pot_control()
{
  delay(1000);
  lcd.clear();
  while(1)
  {
    count();
  int pot_val = analogRead(A5);
  pot_speed = map(pot_val, 0, 1023, 0, 255);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(motor_speed,pot_speed);
  
    lcd.setCursor(0,0);
    lcd.print("1.Speed :");
    lcd.setCursor(11,0);
    lcd.print(pot_speed);
    lcd.setCursor(15,1);
    lcd.print("<");
    lcd.setCursor(0,1);
    lcd.print("2.Stop");
    flag = 7;
    delay(200);
  if (digitalRead(ok_but) == 0)
  {
    TurnOFF_motor();
    break;
    }
    
  } 
}
/*void speed_select()
{
  speed1_buf = digitalRead(speed_but1);
  speed2_buf = digitalRead(speed_but2);
  speed3_buf = digitalRead(speed_but3);
  delay(500);
}*/

void menu()
{
  up_buf = digitalRead(up_but);
  down_buf = digitalRead(down_but);
  ok_buf = digitalRead(ok_but);
  if(digitalRead(down_but) == 0 && flag == 0)
  { Serial.println("loop 1");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("1.Speed controls");
    lcd.setCursor(15,0);
    lcd.print("<");
    lcd.setCursor(0,1);
    lcd.print("2.Manual");
    flag = 1;
    delay(1000);
  }
  if(digitalRead(down_but) == 0 && flag == 1)
  { Serial.println("loop 2");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("1.Speed controls");
    lcd.setCursor(15,1);
    lcd.print("<");
    lcd.setCursor(0,1);
    lcd.print("2.Manual");
    flag = 2;
    delay(1000);
  }
  if(digitalRead(up_but) == 0 && flag == 2)
  { Serial.println("loop 3");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("1.Speed controls");
    lcd.setCursor(15,0);
    lcd.print("<");
    lcd.setCursor(0,1);
    lcd.print("2.Manual");
    flag = 1;
    delay(1000);
  }
  
  if(digitalRead(ok_but) == 0 && flag == 1) ////////////////////////// Speed control
  { Serial.println("loop 4");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("1.Slow");
    lcd.setCursor(15,0);
    lcd.print("<");
    lcd.setCursor(0,1);
    lcd.print("2.Medium");
    flag = 3;
    delay(1000);
  }
  if(digitalRead(down_but) == 0 && flag == 3)
  { Serial.println("loop 5");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("1.Slow");
    lcd.setCursor(15,1);
    lcd.print("<");
    lcd.setCursor(0,1);
    lcd.print("2.Medium");
    flag = 4;
    delay(1000);
  }
  if(digitalRead(down_but) == 0 && flag == 4)
  { Serial.println("loop 6");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("3.Fast");
    lcd.setCursor(15,0);
    lcd.print("<");
    lcd.setCursor(0,1);
    lcd.print("4.Exit");
    flag = 5;
    delay(1000);
  }
  if(digitalRead(down_but) == 0 && flag == 5)
  { Serial.println("loop 7");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("3.Fast");
    lcd.setCursor(15,1);
    lcd.print("<");
    lcd.setCursor(0,1);
    lcd.print("4.Exit");
    flag = 6;
    delay(1000);
  }
  if(digitalRead(up_but) == 0 && flag == 6)
  { Serial.println("loop 8");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("3.Fast");
    lcd.setCursor(15,0);
    lcd.print("<");
    lcd.setCursor(0,1);
    lcd.print("4.Exit");
    flag = 5;
    delay(1000);
  }
  if(digitalRead(up_but) == 0 && flag == 5)
  { Serial.println("loop 9");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("1.Slow");
    lcd.setCursor(15,1);
    lcd.print("<");
    lcd.setCursor(0,1);
    lcd.print("2.Medium");
    flag = 4;
    delay(1000);
  }
  if(digitalRead(up_but) == 0 && flag == 4)
  { Serial.println("loop 10");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("1.Slow");
    lcd.setCursor(15,0);
    lcd.print("<");
    lcd.setCursor(0,1);
    lcd.print("2.Medium");
    flag = 3;
    delay(1000);
  }

  if(digitalRead(ok_but) == 0 && flag == 3) ////////////////// speed SLOW
  { Serial.println("loop 11");
    TurnMotor_speed1();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Slow...");
    lcd.setCursor(15,1);
    lcd.print("<");
    lcd.setCursor(0,1);
    lcd.print("Exit");
    flag = 7;
    delay(1000);
  }
  if(digitalRead(ok_but) == 0 && flag == 4) ////////////////// speed Medium
  { Serial.println("loop 12");
    TurnMotor_speed2();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Medium...");
    lcd.setCursor(15,1);
    lcd.print("<");
    lcd.setCursor(0,1);
    lcd.print("Exit");
    flag = 7;
    delay(1000);
  }
  if(digitalRead(ok_but) == 0 && flag == 5) ////////////////// speed Fast
  { Serial.println("loop 13");
    TurnMotor_speed3();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Fast...");
    lcd.setCursor(15,1);
    lcd.print("<");
    lcd.setCursor(0,1);
    lcd.print("Exit");
    flag = 7;
    delay(1000);
  }
  
  if(digitalRead(ok_but) == 0 && flag == 6)//////////////// exit
  { Serial.println("loop 14");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("1.Speed controls");
    lcd.setCursor(15,0);
    lcd.print("<");
    lcd.setCursor(0,1);
    lcd.print("2.Manual");
    TurnOFF_motor();
    flag = 1;
    delay(1000);
  }
  if(digitalRead(ok_but) == 0 && flag == 7)
  { Serial.println("loop 15");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("1.Speed controls");
    lcd.setCursor(15,0);
    lcd.print("<");
    lcd.setCursor(0,1);
    lcd.print("2.Manual");
    TurnOFF_motor();
    flag = 1;
    delay(1000);
  }
  

  if(digitalRead(ok_but) == 0 && flag == 2) //////////////////////////////////// Manual
  { Serial.println("loop 16");
    pot_control();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("1.Speed :");
    lcd.setCursor(11,0);
    lcd.print(pot_speed);
    lcd.setCursor(15,1);
    lcd.print("<");
    lcd.setCursor(0,1);
    lcd.print("2.Exit");
    flag = 7;
    delay(1000);
  }
}
