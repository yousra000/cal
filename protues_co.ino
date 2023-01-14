#include <Keypad.h>
#include  <LiquidCrystal.h>


LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
const byte r = 4;
const byte c = 4;
byte r_pins[r] ={2,3,4,5};
byte c_pins[c] ={6,7,8,9};
char keys[r][c] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {'C', '0', '=', '+'}
};

Keypad myKeypad = Keypad(makeKeymap(keys),r_pins,c_pins,r,c );
boolean firstMinus=false;
boolean secondMinus = false;
boolean NUM_ONE_CHECK = false;
boolean NUM_two_CHECK=false;
// boolean Button1_CHECK=false;
// boolean Button3_CHECK=false;
// boolean Button2_CHECK=false;
boolean FirSec_Op = false;
boolean final_Op = false;
String n1="",n2="",res="";
int ans;
char op;
int Button_Val=0;
int Button_tan=13;
//SIN
int Button_Val2=0;
int Button_SIN=12;
//COS
int Button_Val3=0;
int Button_COS=11;

int Button_Val4=0;
int Button_sqrl=1;

int Button_Val5=0;
int Button_pow=0;
void setup()
{
  pinMode(Button_tan, INPUT);
  digitalWrite(Button_tan, HIGH);
  pinMode(Button_COS, INPUT);
  digitalWrite(Button_COS, HIGH);
  pinMode(Button_SIN, INPUT);
  digitalWrite(Button_SIN, HIGH);
  pinMode(Button_sqrl, INPUT);
  digitalWrite(Button_sqrl, HIGH);
  pinMode(Button_pow, INPUT);
  digitalWrite(Button_pow, HIGH);

  lcd.begin(16,2);
  lcd.setCursor(5,0);
  lcd.clear();
}


void loop() {
  Button_Val=digitalRead(Button_tan);
  Button_Val2=digitalRead(Button_SIN);
  Button_Val3=digitalRead(Button_COS);
  Button_Val4=digitalRead(Button_sqrl);
  Button_Val5=digitalRead(Button_pow);

  char key = myKeypad.getKey();// key='7'
  
  double num;
    
  if (key != NO_KEY &&(key=='1'||key=='2'||key=='3'||
                        key=='4'||key=='5'||key=='6'||
                        key=='7'||key=='8'||key=='9'||
                              key=='0') )
  {
    
    if (FirSec_Op ==false )
    {
      lcd.clear();
      n1 = n1 + key;// '7' + '5' ='75'
      int numLength = n1.length();
      lcd.setCursor(15 - numLength, 0); 
      lcd.print(n1);
      NUM_ONE_CHECK=true;
    }
    else
    {
      n2 = n2 + key;
      int numLength = n2.length();
      lcd.setCursor(15-numLength, 1);
      lcd.print(n2);
      final_Op = true;// n1 n2 op
      NUM_two_CHECK=true;
      
    }
  }
  if (NUM_ONE_CHECK && FirSec_Op==false && key != NO_KEY && (key=='/'||key=='*'||key=='+'||key=='-'))
  {
        op = key;
        //int numLength = n1.length();
        lcd.setCursor(15, 0); 
        lcd.print(op);
        FirSec_Op = true;
        //delay(500);
}
  else if (NUM_two_CHECK==false && NUM_ONE_CHECK == true && FirSec_Op== true && !secondMinus &&( key != NO_KEY && (key=='-')))
    {

        n2 = n2 + key;
 
        int numLength = n2.length();
        lcd.setCursor(15 - numLength, 1);
        lcd.print(n2);
        secondMinus=true;
      
    
    }
  if (!NUM_ONE_CHECK && !FirSec_Op  && !firstMinus&&( key != NO_KEY && (key=='-')))
  {

      n1 = n1 + key;
      NUM_ONE_CHECK=true;
      if (key!=NO_KEY && (key=='1'||key=='2'||key=='3'||
                        key=='4'||key=='5'||key=='6'||
                        key=='7'||key=='8'||key=='9'||
                              key=='0') )
      {
        n1 = n1 + key;
        int numLength = n1.length();
        lcd.setCursor(14, 0); 
        lcd.print(n1);
        }
        NUM_ONE_CHECK=true;        
        firstMinus=true;
        
    }

    
    if(final_Op == false &&FirSec_Op==false&& key != NO_KEY && key == '='){
    
      if(Button_Val==LOW ) {
        lcd.clear();
        int numLength = n1.length();
        num=n1.toDouble();
        lcd.setCursor(15 - numLength, 0); 
        lcd.print(tan(num*3.14 / 180));
      }

      else if (Button_Val2==LOW ){
      //lcd.setCursor(0,1);
      lcd.clear();
      int numLength = n1.length();
      num=n1.toDouble();
      lcd.setCursor(15 - numLength, 0); 
      lcd.print(sin(num*3.14 / 180));

      }
      else if (Button_Val3==LOW ){
      //lcd.setCursor(0,1);
      lcd.clear();
      int numLength = n1.length();
      num=n1.toDouble();
      lcd.setCursor(15 - numLength, 0); 
      lcd.print(cos(num*3.14 / 180));

      }
      else if (Button_Val4==LOW ){
      //lcd.setCursor(0,1);
      lcd.clear();
      int numLength = n1.length();
      num=n1.toDouble();
      lcd.setCursor(15 - numLength, 0); 
      lcd.print(sqrt(num));

      }
      else if (Button_Val5==LOW ){
      //lcd.setCursor(0,1);
      lcd.clear();
      int numLength = n1.length();
      num=n1.toDouble();
      lcd.setCursor(15 - numLength, 0); 
      lcd.print(pow(num,2));

      }
      
    }
    if (final_Op == true && key != NO_KEY && key == '='){
      if (op=='+'){
        ans = n1.toInt() + n2.toInt();
        res=String(ans);
        int ansLength = res.length();
        lcd.clear();
        lcd.setCursor(15-ansLength,0);
        lcd.print(ans);
        delay(3000);
        lcd.clear();

        n1=res;
        FirSec_Op = false;
          firstMinus = false; 
          secondMinus=false;
          //NUM_ONE_CHECK = false;
          NUM_two_CHECK=false;
          final_Op = false;
          //n1 = "";
          n2 = "";
          ans = 0;
          op = ' ';
          num=0;

        lcd.setCursor(15-ansLength,0);
        lcd.print(n1);

  }
      else if (op=='-'){
        ans = n1.toInt()-n2.toInt();
        res=String(ans);
        int ansLength = res.length();
        lcd.clear();
        lcd.setCursor(15-ansLength,0);
        lcd.print(ans);
        delay(3000);
        lcd.clear();

        n1=res;
        FirSec_Op = false;
          firstMinus = false; 
          secondMinus=false;
          //NUM_ONE_CHECK = false;
          NUM_two_CHECK=false;
          final_Op = false;
          //n1 = "";
          n2 = "";
          ans = 0;
          op = ' ';
          num=0;

        lcd.setCursor(15-ansLength,0);
        lcd.print(n1);
      }
      else if (op=='*'){
        ans = n1.toInt() * n2.toInt();
        res=String(ans);
        int ansLength = res.length();
        lcd.clear();
        lcd.setCursor(15-ansLength,0);
        lcd.print(ans);
        // delay(3000);
        // lcd.clear();

          n1=res;
          FirSec_Op = false;
          firstMinus = false; 
          secondMinus=false;
          //NUM_ONE_CHECK = false;
          NUM_two_CHECK=false;
          final_Op = false;
          n2 = "";
          ans = 0;
          op = ' ';
          num=0;

        lcd.setCursor(15-ansLength,0);
        lcd.print(n1);
      }
      else if (op=='/'){
        if(n2.toInt()==0){
          //lcd.begin(16,2);
          lcd.setCursor(0,0);
          lcd.print("undefined");
          delay(3000);
          lcd.clear();

          FirSec_Op = false;
          firstMinus = false; 
          secondMinus=false;
          //NUM_ONE_CHECK = false;
          NUM_two_CHECK=false;
          final_Op = false;
          n1 = "";
          n2 = "";
          ans = 0;
          op = ' ';
          num=0;
        }
        else {
          ans = n1.toInt() / n2.toInt();
          res=String(ans);
          int ansLength = res.length();
          
          lcd.clear();
          lcd.setCursor(15-ansLength,0);
          lcd.print(ans);
          // delay(3000);
          // lcd.clear();

          n1=res;
          FirSec_Op = false;
          firstMinus = false; 
          secondMinus=false;
          //NUM_ONE_CHECK = false;
          NUM_two_CHECK=false;
          final_Op = false;
          n2 = "";
          ans = 0;
          op = ' ';
          num=0;

          lcd.setCursor(15-ansLength,0);
          lcd.print(n1);
          }
      }    
        
    }
  if (key!=NO_KEY&&key=='C'){
      lcd.clear();
      FirSec_Op = false;
      firstMinus = false; 
      secondMinus=false;
      NUM_ONE_CHECK = false;
      NUM_two_CHECK=false;
      final_Op = false;
      n1 = "";
      n2 = "";
      ans = 0;
      op = ' ';
      num=0;
    }
    



}