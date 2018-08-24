#define pin    13
char resp;
void setup() {
  pinMode(pin, OUTPUT);
  Serial.begin(9600);
}
void loop(){
  if(Serial.available() > 0){
    resp = Serial.read();
    if(resp == '1'){
        digitalWrite(pin, HIGH);
        Serial.println("led aceso!");
    }else{
        digitalWrite(pin, LOW);
        Serial.println("led apagado!");
    }
  }
}










