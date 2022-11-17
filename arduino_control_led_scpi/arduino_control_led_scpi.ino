//     ArduinoControlLed SCPI edition
//     17.11.2022 // uses code from https://github.com/Vrekrer/Vrekrer_scpi_parser
/*
Control of the brightness of LEDs using SCPI commands.
Serial is set to 115200 8N1

Hardware required:
LEDs + attached to digital pin 3 5 6 9 and - via 200 Ohm (or 1 kOhm) resistor go to GND

Commands:
  *IDN?
    Gets the instrument's identification string

  *RST
    Perform software reset

  LED:TEST
    Perform quick cycle of test for all LEDs
    
  LED:ON (LED#:ON)
    Sets the LED's brightness to max
    e.g. LED:ON   -  sets LED brightnesses to 10,10,10,10
    e.g. LED2:ON  -  sets LED2 brightness to 10

  LED:OFF (LED#:OFF)
    Sets the LED's brightness to max
    e.g. LED:OFF   -  sets LED brightnesses to 0,0,0,0
    e.g. LED2:OFF  -  sets LED2 brightness to 0

  LED:BRI <value> (LED#:BRI <value>)
    Sets the LED's brightness to <value>
    Valid values : 0 (OFF) to 10 (Full brightness)
    e.g. LED:BRI 10  - sets all LED to full brightness (same as LED:ON)
    e.g. LED2:BRI 5  - sets LED2 to half brightness

  
  LED:BRI? (LED#:BRI)
    Queries the LED's brightness value
    e.g. LED:BRI?  - gets 10,10,5,10
    e.g. LED2:BRI? - gets 5

  LED:BRI:DEC (LED#:BRI:DEC)
    Decreases the LED's brightness value by one
    e.g. LED:BRI:DEC  - sets LED brightnesses to 9,9,4,9
    e.g. LED2:BRI:DEC  - sets LED2 brightness to 3
    
  LED:BRI:INC (LED#:BRI:INC)
    Increases the LED's brightness value by one
    e.g. LED:BRI:INC  - sets LED brightnesses to 10,10,4,10    
    e.g. LED2:BRI:DEC  - sets LED2 brightness to 5    
*/


#include "Arduino.h"
#include "Vrekrer_scpi_parser.h"

SCPI_Parser my_instrument;
#define idn_string "NazerTech,Arduino Control LED SCPI,0001,v0.1"
int bri[4] = {0,0,0,0}; // array of brightnesses
int brightness = 0;     // current temporary brightness value
#define PWM0 3 // LED0 on PIN D3
#define PWM1 5 // LED1 on PIN D5
#define PWM2 6 // LED2 on PIN D6
#define PWM3 9 // LED3 on PIN D9

const int intensity[11] = {0, 3, 5, 9, 15, 24, 38, 62, 99, 159, 255}; // PWM intensity constants from 0 to 10


void led_off(int led_num)
{
  if (led_num>=0){
    switch (led_num){
      case 0:
        analogWrite(PWM0, 0);
        bri[0] = 0;
        break;
      case 1:
        analogWrite(PWM1, 0);
        bri[1] = 0;
        break;        
      case 2:
        analogWrite(PWM2, 0);
        bri[2] = 0;
        break;        
      case 3:
        analogWrite(PWM3, 0);
        bri[3] = 0;
        break;        
      default:
        break;
    }     
  } else {
    analogWrite(PWM0, 0);
    analogWrite(PWM1, 0);
    analogWrite(PWM2, 0);
    analogWrite(PWM3, 0);  
    bri[0] = 0;
    bri[1] = 0;
    bri[2] = 0;
    bri[3] = 0;
  }  
}

void led_on(int led_num)
{
  if (led_num>=0){
    switch (led_num){
      case 0:
        analogWrite(PWM0, 255);
        bri[0] = 10;
        break;
      case 1:
        analogWrite(PWM1, 255);
        bri[1] = 10;
        break;        
      case 2:
        analogWrite(PWM2, 255);
        bri[2] = 10;
        break;        
      case 3:
        analogWrite(PWM3, 255);
        bri[3] = 10;
        break;        
      default:
         break;
    }     
  } else {
    analogWrite(PWM0, 255);
    analogWrite(PWM1, 255);
    analogWrite(PWM2, 255);
    analogWrite(PWM3, 255);  
    bri[0] = 10;
    bri[1] = 10;
    bri[2] = 10;
    bri[3] = 10;
  }  
}

void led_bri_inc(int led_num)
{
  if (led_num>=0){
    switch (led_num){
      case 0:
        brightness = bri[led_num];
        brightness = constrain(brightness + 1, 0, 10);
        analogWrite(PWM0, intensity[brightness]);
        bri[led_num] = brightness;
        break;
      case 1:
        brightness = bri[led_num];
        brightness = constrain(brightness + 1, 0, 10);
        analogWrite(PWM1, intensity[brightness]);
        bri[led_num] = brightness;
        break;        
      case 2:
        brightness = bri[led_num];
        brightness = constrain(brightness + 1, 0, 10);
        analogWrite(PWM2, intensity[brightness]);
        bri[led_num] = brightness;
        break;        
      case 3:
        brightness = bri[led_num];
        brightness = constrain(brightness + 1, 0, 10);
        analogWrite(PWM3, intensity[brightness]);
        bri[led_num] = brightness;
        break;        
      default:
         break;
    }     
  } else {
        brightness = bri[0];
        brightness = constrain(brightness + 1, 0, 10);
        analogWrite(PWM0, intensity[brightness]);
        bri[0] = brightness;
        brightness = bri[1];
        brightness = constrain(brightness + 1, 0, 10);
        analogWrite(PWM1, intensity[brightness]);
        bri[1] = brightness;
        brightness = bri[2];
        brightness = constrain(brightness + 1, 0, 10);
        analogWrite(PWM2, intensity[brightness]);
        bri[2] = brightness;
        brightness = bri[3];
        brightness = constrain(brightness + 1, 0, 10);
        analogWrite(PWM3, intensity[brightness]);
        bri[3] = brightness;
  }  
}


void led_bri_dec(int led_num)
{
  if (led_num>=0){
    switch (led_num){
      case 0:
        brightness = bri[led_num];
        brightness = constrain(brightness - 1, 0, 10);
        analogWrite(PWM0, intensity[brightness]);
        bri[led_num] = brightness;
        break;
      case 1:
        brightness = bri[led_num];
        brightness = constrain(brightness - 1, 0, 10);
        analogWrite(PWM1, intensity[brightness]);
        bri[led_num] = brightness;
        break;        
      case 2:
        brightness = bri[led_num];
        brightness = constrain(brightness - 1, 0, 10);
        analogWrite(PWM2, intensity[brightness]);
        bri[led_num] = brightness;
        break;        
      case 3:
        brightness = bri[led_num];
        brightness = constrain(brightness - 1, 0, 10);
        analogWrite(PWM3, intensity[brightness]);
        bri[led_num] = brightness;
        break;        
      default:
         break;
    }     
  } else {
        brightness = bri[0];
        brightness = constrain(brightness - 1, 0, 10);
        analogWrite(PWM0, intensity[brightness]);
        bri[0] = brightness;
        brightness = bri[1];
        brightness = constrain(brightness - 1, 0, 10);
        analogWrite(PWM1, intensity[brightness]);
        bri[1] = brightness;
        brightness = bri[2];
        brightness = constrain(brightness - 1, 0, 10);
        analogWrite(PWM2, intensity[brightness]);
        bri[2] = brightness;
        brightness = bri[3];
        brightness = constrain(brightness - 1, 0, 10);
        analogWrite(PWM3, intensity[brightness]);
        bri[3] = brightness;
  }  
}



void led_test()
{
  led_on(-1);
  delay(100);  
  led_off(-1);
  for(int i=0; i<=255; i++){
    analogWrite(PWM0, i);
    delay(1);
  }
  for(int i=0; i<=255; i++){
    analogWrite(PWM1, i);
    delay(1);
  }
  for(int i=0; i<=255; i++){
    analogWrite(PWM2, i);
    delay(1);
  }
  for(int i=0; i<=255; i++){
    analogWrite(PWM3, i);
    delay(1);
  }
  led_off(-1);
}


void setup()
{
  my_instrument.RegisterCommand(F("*IDN?"), &Identify);
  my_instrument.RegisterCommand(F("*RST"), &SoftReset);
  my_instrument.SetCommandTreeBase(F("LED#"));
    my_instrument.RegisterCommand(F(":TEST"), &LedTest);
    my_instrument.RegisterCommand(F(":ON"), &LedOn);
    my_instrument.RegisterCommand(F(":OFF"), &LedOff);
    my_instrument.RegisterCommand(F(":BRI"), &SetBrightness);
    my_instrument.RegisterCommand(F(":BRI?"), &GetBrightness);
    my_instrument.RegisterCommand(F(":BRI:INC"), &IncDecBrightness);
    my_instrument.RegisterCommand(F(":BRI:DEC"), &IncDecBrightness);

  Serial.begin(115200);
  pinMode(PWM0, OUTPUT);
  pinMode(PWM1, OUTPUT);
  pinMode(PWM2, OUTPUT);
  pinMode(PWM3, OUTPUT);
  led_test();
}

void loop()
{
  my_instrument.ProcessInput(Serial, "\n");
}

void Identify(SCPI_C commands, SCPI_P parameters, Stream& interface) {
  interface.println(F(idn_string));
}

void SoftReset(SCPI_C commands, SCPI_P parameters, Stream& interface) {
  led_test();
  led_off(-1);  
  interface.println(F("RESET OK"));
}

void LedTest(SCPI_C commands, SCPI_P parameters, Stream& interface) {
  interface.println(F("TEST CYCLE"));
  led_test();
}

void LedOn(SCPI_C commands, SCPI_P parameters, Stream& interface) {
  String header = String(commands.First());
  header.toUpperCase();
  int suffix = -1;
  sscanf(header.c_str(),"%*[LED]%u", &suffix);  
  led_on(suffix);  
  interface.println(F("LED ON"));
}

void LedOff(SCPI_C commands, SCPI_P parameters, Stream& interface) {
  String header = String(commands.First());
  header.toUpperCase();
  int suffix = -1;
  sscanf(header.c_str(),"%*[LED]%u", &suffix);  
  led_off(suffix);  
  interface.println(F("LED OFF"));
}


void SetBrightness(SCPI_C commands, SCPI_P parameters, Stream& interface) {
  // For simplicity no bad parameter check is done.
  if (parameters.Size() > 0) {
    String header = String(commands.First());
    header.toUpperCase();
    int suffix = -1;
    sscanf(header.c_str(),"%*[LED]%u", &suffix);
   
    brightness = constrain(String(parameters[0]).toInt(), 0, 10);
    switch (suffix){
      case -1:
         analogWrite(PWM0, intensity[brightness]);
         analogWrite(PWM1, intensity[brightness]);
         analogWrite(PWM2, intensity[brightness]);
         analogWrite(PWM3, intensity[brightness]);
         bri[0] = brightness;
         bri[1] = brightness;
         bri[2] = brightness;
         bri[3] = brightness;
      case 0:
         analogWrite(PWM0, intensity[brightness]);
         bri[suffix] = brightness;
         break;
      case 1:
         analogWrite(PWM1, intensity[brightness]);
         bri[suffix] = brightness;
         break;
      case 2:
         analogWrite(PWM2, intensity[brightness]);
         bri[suffix] = brightness;
         break;
      case 3:
         analogWrite(PWM3, intensity[brightness]);
         bri[suffix] = brightness;
         break;
      default:
         break;
    } 
  }
}

void GetBrightness(SCPI_C commands, SCPI_P parameters, Stream& interface) {
  char char_buffer[20];
  String header = String(commands.First());
  header.toUpperCase();
  int suffix = -1;
  sscanf(header.c_str(),"%*[LED]%u", &suffix);

  if ((suffix >= 0) && (suffix<=3)){
    interface.println(String(bri[suffix], DEC));    
  } else {
    sprintf(char_buffer,"%d,%d,%d,%d", bri[0],bri[1],bri[2],bri[3]);
    interface.println(char_buffer);    
  }
}


void IncDecBrightness(SCPI_C commands, SCPI_P parameters, Stream& interface) {
  int incdec = -1;
  String last_header = String(commands.Last());
  last_header.toUpperCase();
  if (last_header.startsWith("INC")) {
     incdec = 1;
  } else { 
     if (last_header.startsWith("DEC")){
        incdec = 2;  
     }
  }
  
  String header = String(commands.First());
  header.toUpperCase();
  int suffix = -1;
  sscanf(header.c_str(),"%*[LED]%u", &suffix);    
 
  if (incdec == 1){
      led_bri_inc(suffix);
  }
  if (incdec == 2){
      led_bri_dec(suffix);
  }
}
