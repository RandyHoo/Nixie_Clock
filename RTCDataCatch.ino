void RTCDataCatch(){

  //配列化してforループを回させれば簡略化できそう
  //データ読み出し処理
  Wire.beginTransmission(RTCAddress);
  Wire.write(0x00); //Secondsレジスタを指定
  Wire.endTransmission(false);
  
  Wire.requestFrom(RTCAddress,8,false);
  seconds = Wire.read();
  minutes = Wire.read();
  hours = Wire.read();
  Wire.read();
  days = Wire.read();
  months = Wire.read();
  years = Wire.read();
  Wire.endTransmission(true);

  //データ入力処理
  CalenderArray[0] = (years >> 4);
  CalenderArray[1] = (years & 0xF);
  CalenderArray[2] = (months >> 4);
  CalenderArray[3] = (months & 0xF);
  CalenderArray[4] = (days >> 4);
  CalenderArray[5] = (days & 0xF);
  ClockArray[0] = (hours >> 4);
  ClockArray[1] = (hours & 0xF);
  ClockArray[2] = (minutes >> 4);
  ClockArray[3] = (minutes & 0xF);
  ClockArray[4] = (seconds >> 4);
  ClockArray[5] = (seconds & 0xF);
  
}

void RTCValueJudge(){
  //異常なデータを取得した場合
  if((seconds >= 0x60) || (minutes >= 0x60) || (hours >= 0x24) ||
     (days >= 0x32) || (months >= 0x13) || (years >= 0x99) ){
    NixieLightning(1,8); //修正中の表記
    //GPSからデータを取得できるまで実行
    do {
      GPSDataCatch();//初期値設定用のデータ取得
    } while ( data_get_flag == false );
    NowDataSet();//データを補正
  }
  //UTCと日本の時差によるバグの修正
  if((seconds == 0x00) && (minutes == 0x05) && (hours == 0x09)){
    NixieLightning(1,9); //修正中の表記
    //GPSからデータを取得できるまで実行
    do {
      GPSDataCatch();//初期値設定用のデータ取得
    } while ( data_get_flag == false );
    NowDataSet();//データを補正
  }
}
