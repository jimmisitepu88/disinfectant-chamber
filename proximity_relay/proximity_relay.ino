const byte rel1 = A0;
const byte rel2 = A1;
const byte sensor = A3;

#define stanby 0
#define run_pump 1
int state;
byte count;
bool hold;
unsigned long curTime, oldTime;

void setup() {
  // put your setup code here, to run once:
  pinMode(rel1, OUTPUT);
  pinMode(rel2, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(sensor, INPUT_PULLUP);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  baca_proxy();
  switch(state){
    case stanby:
      Serial.println("stanby");delay(1000);
      digitalWrite(13, HIGH);
    break;
    case run_pump:
      digitalWrite(13, LOW);
      Serial.println("stanby");delay(1000);
      Serial.println("masuk");
      tunggu(3000); // waktu orang jalan ke chammber
      Serial.println("siram");
      pump_on();
      tunggu(5000);
      pump_off();
      Serial.println("keluar");
      tunggu(4000); // waktu orang keluar
      state = stanby;
    break;
  }
}

void baca_proxy(){
  Serial.print("sen: ");
  Serial.println(digitalRead(sensor));
  if(digitalRead(sensor) == 0){
    if(hold == false){
      state = run_pump;
      hold = true;
    }else{
      hold = false;
    }
  }
}

void tunggu(unsigned long wkt){
  Serial.println("tunggu");
  curTime = millis();
  oldTime = curTime;
  while(curTime - oldTime < wkt){
    curTime = millis();
  }
}

void pump_on(){
  digitalWrite(rel1, HIGH);
  digitalWrite(rel2, HIGH);
}

void pump_off(){
  digitalWrite(rel1, LOW);
  digitalWrite(rel2, LOW);
}
