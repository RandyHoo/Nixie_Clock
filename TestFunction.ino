void TestOutputCalender() {
  for(int i = 0; i < 6; i++){
    Serial.print(CalenderArray[i]);
  }
  Serial.print("\n");
}

void TestOutputClock() {
  for(int i = 0; i < 6; i++){
    Serial.print(ClockArray[i]);
  }
  Serial.print("\n");
}

void TestInputButton() {
  Serial.print("Button1=");
  Serial.print(InputB1Flag);
  Serial.print("\n");
  Serial.print("Button2=");
  Serial.print(InputB2Flag);
  Serial.print("\n");
  Serial.print("Mode_Status=");
  Serial.print(Mode_Status);
  Serial.print("\n");
}

void TestDynamicLightning(){
  for(int i = 0; i < 6; i++){
    NixieLightning(i+1, i+1);
    delay(3);
  }
}

