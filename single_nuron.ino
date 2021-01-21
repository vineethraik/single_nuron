#include<EEPROM.h>
int adress=100;
int i,j,k,d0,d1,d2,t;
const int isize=6;
char ch;
float dif2,pred;
float wt[4]={1.485,2.784,1.145,-3.123};
float in[isize][3]={{0,0,1},{0,1,1},{1,0,0},{1,0,1},{0,1,0},{1,1,0}};
float out[isize]={0,1,0,1,0,0};

float sigmoid(float x)
{
  return 1/(1+exp(-x));
}

float ds(float x)
{
  return x*(1-x);
}
void setup() {
//  for(i=0;i<4;i++)
// {
//   EEPROM.get(adress+i*100,wt[i]);
//}
  Serial.begin(2000000);
  Serial.println();

 for(i=0;i<isize;i++)
  {
    
    Serial.print((int)in[i][0]);
    Serial.print(" | ");
    Serial.print((int)in[i][1]);
    Serial.print(" | ");
    Serial.print((int)in[i][2]);
    Serial.print(" |>>>>>> ");
    Serial.println(out[i]);
    delay(1000);
  }
   
  
}

void loop() 
{
 
  for(i=0;!Serial.available()&&i<20000;i++)
  {
    for(j=0;j<isize;j++)
    {
    pred=wt[0]*in[j][0]+wt[1]*in[j][1]+wt[2]*in[j][2]+wt[3];
    dif2=sq((out[j]-sigmoid(pred)));
    
    wt[0]+=.1*2*(out[j]-sigmoid(pred))*(sigmoid(pred)*(1-sigmoid(pred))*in[j][0]);
    wt[1]+=.1*2*(out[j]-sigmoid(pred))*(sigmoid(pred)*(1-sigmoid(pred))*in[j][1]);
    wt[2]+=.1*2*(out[j]-sigmoid(pred))*(sigmoid(pred)*(1-sigmoid(pred))*in[j][2]);
    wt[3]+=.1*2*(out[j]-sigmoid(pred))*(sigmoid(pred)*(1-sigmoid(pred)));
    //Serial.print(sigmoid(pred));
    //Serial.print(" # ");
    }
    //Serial.println();
    
    
  }

  
  Serial.println("//////////////////////////////////////////////////////////////////");
  for(i=0;i<4;i++)
  {
    Serial.print(wt[i]);
    Serial.print("  //  ");
  }
  Serial.println("||");
  Serial.println("//////////////////////////////////////////////////////////////////");
  delay(2000);
   for(t=0;t<8;t++)
  {
    i=t;
    d0=i%2;
    i=i/2;
    d1=i%2;
    i=i/2;
    d2=i%2;
    i=i/2;
    Serial.print(d2);
    Serial.print(" | ");
    Serial.print(d1);
    Serial.print(" | ");
    Serial.print(d0);
    Serial.print(" |>>>>>> ");
    Serial.print(sigmoid(d2*wt[0]+d1*wt[1]+d0*wt[2]+wt[3]));
    Serial.print("  >>>>");
    Serial.println((d2||d1)&&d0);
    delay(1000);
  }
  for(i=0;i<4;i++)
  {
    EEPROM.put(adress+i*100,wt[i]);
  }
  while(Serial.available()){ch=Serial.read();}
  while(!Serial.available()){}
  while(Serial.available()){Serial.print(Serial.read());}
  
  
}
