void OutputClock(){
  for(int i = 0; i < 6; i++){
    NixieLightning(i+1, ClockArray[i]);
    delay(2);
  }
}

void OutputCalender(){
  for(int i = 0; i < 6; i++){
    NixieLightning(i+1, CalenderArray[i]);
    delay(2);
  }
}

void NixieShuffle(){
  for(int i = 0; i <= 9; i++){
    for(int j = 0; j < 6; j++){
      NixieLightning(j+1, i);
      delay(1);
    }
  }
}

