#include <Arduino.h>

#define LED_VERDE 5
#define LED_AMARILLO 6
#define MICROFONO 7

const unsigned long delay_clap = 500;
const unsigned long delay_timeout = 1000;

unsigned long clap_actual = 0;
bool first_clap = false;

bool encendido = false;

void switch_rele() {
  if (encendido){
    digitalWrite(LED_VERDE, LOW);
    encendido = false;
    Serial.println("APAGA");
  }else{
    digitalWrite(LED_VERDE, HIGH);
    encendido = true;
    Serial.println("ENCIENDE");
  }
}

bool timeout() {
  if( (millis() - clap_actual > delay_timeout) and (digitalRead(LED_AMARILLO) == HIGH) ){
    first_clap = false;
    digitalWrite(LED_AMARILLO, LOW);
    Serial.println("TIMEOUT!!!");
    return true;
  }
  return false;
}

void setup() {
  
  Serial.begin(9600);

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARILLO, OUTPUT);
  pinMode(MICROFONO, INPUT);

  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(LED_AMARILLO, LOW);

  clap_actual = millis();
  Serial.println("INICIADO.");

}

void loop() {
  if( digitalRead(MICROFONO) == HIGH ){
    if( first_clap == false ){
      digitalWrite(LED_AMARILLO, HIGH);
      first_clap = true;
      Serial.println("TRUE FIRST CLAP");
    }
    if( (delay_timeout > (millis() - clap_actual)) and ((millis() - clap_actual) > delay_clap) ){
      if( not timeout() and first_clap == true){
        switch_rele();
        first_clap = false;
        Serial.println("FALSE FIRST CLAP");
      }else{ /*
        digitalWrite(LED_AMARILLO, HIGH);
        first_clap = true;
        Serial.println("TRUE FIRST CLAP");
      */ }
    }
    clap_actual = millis();
  }
  timeout();
  
}