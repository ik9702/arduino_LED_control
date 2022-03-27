#include <Arduino.h>
#line 1 "c:\\Users\\Jeong\\Desktop\\Dev\\arduino_LED_control\\sketch.ino"




#line 5 "c:\\Users\\Jeong\\Desktop\\Dev\\arduino_LED_control\\sketch.ino"
void setup();
#line 31 "c:\\Users\\Jeong\\Desktop\\Dev\\arduino_LED_control\\sketch.ino"
void loop();
#line 5 "c:\\Users\\Jeong\\Desktop\\Dev\\arduino_LED_control\\sketch.ino"
void setup(){
  Serial.begin(9600);
  pinMode(3, OUTPUT);
}

int dly = 1;
int PID_cnt = 100;
int cnt = 100;

int target = 90;
float k_p = 1;
float k_i = 0.008;
float k_d = 0.006;

int i = 0;
int j = 0;
int sum = 0;
int lux = 0;
int val = 0;
int dt = 0;
unsigned long tim = 0;
long imem = 0;
int pree = 0;
int Bright;
int e = 0;
float PID = 0;
void loop(){
  //lux refresh
  sum += analogRead(A0);
  if(i>cnt){
    val = sum/cnt;
    float vol = 5.0*val/1023;
    float ohm = 1000*vol/(5-vol);
    float cal = 1.64;
    float hmm = 1/pow(ohm, cal);
    lux = 679517*hmm;
    
    Serial.print(target);
    Serial.print(" ");
    Serial.print(lux);
    Serial.print(" ");
    Serial.println(40*Bright/255); 
    
    sum = 0;
    i=0;
  }

  e = target-lux;
  
  if(j>PID_cnt){
    float P = e;
    
    dt = millis()-tim;
    imem += e*dt;
    float I = imem;
    float D = (e-pree)/dt;
    
    tim = millis();
    pree = e;
    
    PID = k_p*P+k_i*I+k_d*D;  
    j = 0;
  }
  
  if(PID<0){
    PID = 0;
    Bright = PID;
  }
  else if(PID>255){
    PID = 255;
    Bright = PID;
  }
  else{
    Bright = PID;
  }
  analogWrite(3, Bright);
  
  i++;
  j++;
  delay(dly);
}
