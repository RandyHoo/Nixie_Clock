void NowDataSet(){
  byte WriteSec;
  byte WriteMin;
  byte WriteHour;
  byte WriteDay;
  byte WriteMonth;
  byte WriteYear;
  byte Work1; //変換作業用1
  byte Work2; //変換作業用2
  byte Work3; //変換作業用3
  
  //送信用にデータを変換
  Work1 = byte(ClockArray[0]);
  Work3 = (Work1 << 4);
  Work2 = byte(ClockArray[1]);
  WriteHour = (Work3 | Work2);
  
  Work1 = byte(ClockArray[2]);
  Work3 = (Work1 << 4);
  Work2 = byte(ClockArray[3]);
  WriteMin = (Work3 | Work2);

  Work1 = byte(ClockArray[4]);
  Work3 = (Work1 << 4);
  Work2 = byte(ClockArray[5]);
  WriteSec = (Work3 | Work2);
  
  Work1 = byte(CalenderArray[0]);
  Work3 = (Work1 << 4);
  Work2 = byte(CalenderArray[1]);
  WriteYear = (Work3 | Work2);
  
  Work1 = byte(CalenderArray[2]);
  Work3 = (Work1 << 4);
  Work2 = byte(CalenderArray[3]);
  WriteMonth = (Work3 | Work2);
  
  Work1 = byte(CalenderArray[4]);
  Work3 = (Work1 << 4);
  Work2 = byte(CalenderArray[5]);
  WriteDay = (Work3 | Work2);
  
  //時計・カレンダー初期値セット
  Wire.beginTransmission(RTCAddress);
  Wire.write(0x00); //Secondsレジスタを指定
  Wire.write(WriteSec); //secをセット
  Wire.write(WriteMin); //minをセット
  Wire.write(WriteHour); //hourをセット
  Wire.write(0x00); //weekをセット(使用しないので0x00固定)
  Wire.write(WriteDay); //dayをセット
  Wire.write(WriteMonth); //monthをセット
  Wire.write(WriteYear); //yearをセット
  Wire.endTransmission();
}

