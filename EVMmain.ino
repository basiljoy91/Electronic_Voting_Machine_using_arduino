#include<LiquidCrystal.h>
#include <EEPROM.h>
LiquidCrystal lcd(13,12,11,10,9,8);

//defining the variables 
int result=5;
int closed=6;
int total=7;
int clearbutton=A0;
int a=4;
int b=3;
int c=2;

int can_1;//candidate_1
int can_2;//candidate_2
int can_3;//candidate_3
int total_votes;
int stat;

void setup()
{
  stat=EEPROM.read(0);

  //here it stores the count of each candidate or stores the input 
  can_1=EEPROM.read(1);
  can_2=EEPROM.read(2); //stores count of can_2
  can_3=EEPROM.read(3); 
  pinMode(a,INPUT); 
  pinMode(b,INPUT);
  pinMode(c,INPUT);
  pinMode(total,INPUT);
  pinMode(closed,INPUT);
  pinMode(result,INPUT);
  pinMode(clearbutton,INPUT);
  
  //when not pressed the button state will always be high
  digitalWrite(a,HIGH); 
  digitalWrite(b,HIGH);
  digitalWrite(c,HIGH);
  digitalWrite(total,HIGH);
  digitalWrite(closed,HIGH);
  digitalWrite(result,HIGH);
  digitalWrite(clearbutton,HIGH);
  lcd.begin(16,2);
  if(stat==0)
  {
  lcd.print("Press button");
  lcd.setCursor(0,1);
  lcd.print("to vote...");
  delay(1000);
  }
  if(stat==1)
  {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Voting Closed");
  lcd.setCursor(0,1);
  total_votes=can_1+can_2+can_3;
  lcd.print("Total Votes:");
  lcd.print(total_votes);
  }
}

void rpt()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Press button");
  lcd.setCursor(0,1);
  lcd.print("to vote...");
}

//calculating the vote difference
void votedifference()
{
  if(can_1>can_2)
  {
    if(can_2>can_3)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("A wins by");
      lcd.setCursor(0,1);
      lcd.print(can_1-can_2);
      lcd.print(" votes");
    }
    else
    {
      if(can_1>can_3)
      {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("A wins by");
      lcd.setCursor(0,1);
      lcd.print(can_1-can_3);
      lcd.print(" votes");
      }
      if(can_1<can_3)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("C wins by");
        lcd.setCursor(0,1);
        lcd.print(can_3-can_1);
        lcd.print(" votes");
      }
    }
    }
   
    else
    {
      if(can_1>can_3)
      {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("B wins by");
      lcd.setCursor(0,1);
      lcd.print(can_2-can_1);
      lcd.print(" votes");
      }
     
      else
      {
      if(can_2>can_3)
      {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("B wins by");
      lcd.setCursor(0,1);
      lcd.print(can_2-can_3);
      lcd.print(" votes");
      }
      if(can_2<can_3)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("C wins by");
        lcd.setCursor(0,1);
        lcd.print(can_3-can_2);
        lcd.print(" votes");
      }
    }
    }
}

void loop()
{
  //can_1 which means A
  if(digitalRead(a)==LOW && stat==0) 
  {
    can_1=can_1+1;
    EEPROM.write(1,can_1);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("vote received...");
    delay(3000);
    rpt(); 
  }
 //can_2 which means "B"
  if(digitalRead(b)==LOW && stat==0) 
  {
    can_2=can_2+1;
    EEPROM.write(2,can_2);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("vote received...");
    delay(3000);
    rpt(); 
  }

  //can_3 which means "C"
  if(digitalRead(c)==LOW && stat==0) 
  {
    can_3=can_3+1;
    EEPROM.write(3,can_3);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("vote received...");
    delay(3000);
    rpt(); 
  }
  // "total" button was pressed but no "close" was pressed
  if(digitalRead(total)==LOW && stat==0)
  {
    total_votes=can_1+can_2+can_3;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Total votes:");
    lcd.setCursor(0,1);
    lcd.print(total_votes);
    delay(2000);
    rpt();
  }

  //"close" button
  if(digitalRead(closed)==LOW) 
  {
    stat=1;
    EEPROM.write(0,stat);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Voting Closed...");
    lcd.setCursor(0,1);
    total_votes=can_1+can_2+can_3;
    lcd.print("Total Votes:");
    lcd.print(total_votes);
    while(digitalRead(result)==HIGH);
  }
 
  //"result" button before the "close" button
  if(digitalRead(result)==LOW && stat==1)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("A:");
    lcd.print(can_1);
    lcd.setCursor(7,0)
    lcd.print("B:");
    lcd.print(can_2);
    lcd.setCursor(0,1);
    lcd.print("C:");
    lcd.print(can_3);
    delay(1500);
   

    if(can_1==can2 && can_2==can_3)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Result Tied");
      delay(1500);
    }
   
    if(can_1==can_2 && can_1>can_3)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Tie b/w A and B");
      delay(1500);
    }
   
    if(can_2==can_3 && can_2>can_1)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Tie b/w B and C");
      delay(1500);
    }
    if(can_1==can_3 && can_1>can_2)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Tie b/w A and C");
      delay(1500);
    }
   
    if(can_1>can_2)
    {
      if(can_1>can_3)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Party A wins");
        delay(1500);
        votedifference();
      }
      else if(can_3>can_1)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Party C wins");
        delay(1500);
        votedifference();
      }
    }
   
    else
    {
      if(can_2>can_3 && can_1!=can_2)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Party B wins");
        delay(1500);
        votedifference();
      }
      else if(can_3>can_2)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Party C wins");
        delay(1500);
        votedifference();
      }
    }
  }
 //defining "clear" button function
  if(digitalRead(clearbutton)==LOW) 
  {
    for (int i = 0; i < 512; i++)
    {
      EEPROM.write(i, 0);
    }
    can_1=0;
    can_2=0;
    can_3=0;
    stat=0;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Memory Cleared");
    delay(1500);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Press button");
    lcd.setCursor(0,1);
    lcd.print("to vote...");
  }
}
