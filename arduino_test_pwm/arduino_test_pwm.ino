// test PWM leds on D3 D5 D6 D9
// program for arduino uno
#define PWM0 3
#define PWM1 5
#define PWM2 6
#define PWM3 9

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(PWM0, OUTPUT); 
  pinMode(PWM1, OUTPUT); 
  pinMode(PWM2, OUTPUT); 
  pinMode(PWM3, OUTPUT); 
}

// the loop routine runs over and over again forever:
void loop() {
  for(int i=0; i<=255; i++){
    analogWrite(PWM0, i);
    delay(3);
  }
  for(int i=0; i<=255; i++){
    analogWrite(PWM1, i);
    delay(3);
  }
  for(int i=0; i<=255; i++){
    analogWrite(PWM2, i);
    delay(3);
  }
  for(int i=0; i<=255; i++){
    analogWrite(PWM3, i);
    delay(3);
  }
  for(int i=255; i>=0; i--){
    analogWrite(PWM0, i);
    delay(3);
  }  
  for(int i=255; i>=0; i--){
    analogWrite(PWM1, i);
    delay(3);
  }  
  for(int i=255; i>=0; i--){
    analogWrite(PWM2, i);
    delay(3);
  }  
  for(int i=255; i>=0; i--){
    analogWrite(PWM3, i);
    delay(3);
  }  
  for(int i=0; i<=255; i++){
    analogWrite(PWM0, 0);
    analogWrite(PWM1, 0);
    analogWrite(PWM2, 0);
    analogWrite(PWM3, 0);
    delay(3);
  }  
  
}
