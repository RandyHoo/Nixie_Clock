void GPSDataCatch(){
  String year_1; //現在の年1桁目
  String year_2; //現在の年2桁目
  String month_1; //現在の月1桁目
  String month_2; //現在の月2桁目
  String day_1; //現在の日1桁目
  String day_2; //現在の日2桁目
  String hour_1; //現在の時1桁目
  String hour_2; //現在の時2桁目
  String min_1; //現在の分1桁目
  String min_2; //現在の分2桁目
  String sec_1; //現在の秒1桁目
  String sec_2; //現在の秒2桁目
  char GPS_Rx_buf[256]; //受信用バッファ(255文字分)
  char GPS_Rx_count; //受信データカウンタ
  String want_frame = "$GPRMC"; //データを取り出したいフレーム
  String WantStatus = "A"; //ステータス判別用
  char data_read_count = 0; //データ読み出しカウンタ

  //Ackフレームを受信するまでループを回す
  do {
    if ( sGps.available() ) {
      GPS_Rx_buf[ GPS_Rx_count ] = sGps.read();
      GPS_Rx_count++;
    }
    //バッファが溢れそうなら
    if ( GPS_Rx_count > 250 ) {
      break;
    }
  } while ( GPS_Rx_buf[ GPS_Rx_count - 1 ] != 0x0A );
  GPS_Rx_buf[ GPS_Rx_count ] = '\0'; //一番最後の要素に改行を入れる
  String buf_str = GPS_Rx_buf; //Stringで処理するために変換

  //欲しいデータかどうか調べる
  if ( want_frame == buf_str.substring( 0, 6 ) && WantStatus == buf_str.substring( 18, 19 ) ) {
    data_read_count = buf_str.indexOf( ",", data_read_count ); //1つ目の区切り文字を探す
    data_read_count++; //不要データなので次のデータへ

    data_read_count = buf_str.indexOf( ",", data_read_count ); //2つ目の区切り文字を探す(時刻)
    data_read_count++; //時計・カレンダーでは文字列位置を直指定するので次のデータへ
    String UTC_time = buf_str.substring( 7, 9 ); //時刻修正処理の為にHourを抜き出す
    int JP_time = atoi( UTC_time.c_str() ) + 9; //日本時間に修正
    //変換した際に24時以上になった場合
    if ( JP_time > 23 ) {
      JP_time -= 24;
    }
    String JP_time_str = String( JP_time ); //日本時間に差し換えるためにStringに変換
    //時刻が1桁だった場合
    if ( JP_time < 10) {
      String change_double_digit_calc = JP_time_str.substring( 0, 1 ); //1桁目を保持
      JP_time_str = "00"; //JP_time_strのデータ長を2に増設する
      char hoge_cddc = *change_double_digit_calc.c_str(); //1桁目に0を差し込むためにchar型に変換
      JP_time_str.setCharAt( 0, '0' ); //1桁目を0に差し替える
      JP_time_str.setCharAt( 1, hoge_cddc ); //2桁目に1桁目を差し込む
      String JP_time_str = String( JP_time ); //もう一度Stringに変換
    }
    
    String JP_time_first_digit = JP_time_str.substring( 0, 1 ); //1桁目を取り出す
    char hoge_1 = *JP_time_first_digit.c_str(); //char型に変換
    String JP_time_second_digit = JP_time_str.substring( 1, 2 ); //2桁目を取り出す
    char hoge_2 = *JP_time_second_digit.c_str(); //char型に変換
    buf_str.setCharAt( 7, hoge_1 ); //1桁目を差し替える
    buf_str.setCharAt( 8, hoge_2 ); //2桁目を差し替える

    //時1桁目を取得
    hour_1 = buf_str.substring( 7, 8 );
    ClockArray[0] = hour_1.toInt();
    //時2桁目を取得
    hour_2 = buf_str.substring( 8, 9 );
    ClockArray[1] = hour_2.toInt();
    //分1桁目を取得
    min_1 = buf_str.substring( 9, 10 );
    ClockArray[2] = min_1.toInt();
    //分2桁目を取得
    min_2 = buf_str.substring( 10, 11 );
    ClockArray[3] = min_2.toInt();
    //秒1桁目を取得
    sec_1 = buf_str.substring( 11, 12 );
    ClockArray[4] = sec_1.toInt();
    //秒2桁目を取得
    sec_2 = buf_str.substring( 12, 13 );
    ClockArray[5] = sec_2.toInt();

    //3～9つ目までの区切り文字をスキップする
    for (int i = 0; i < 7; i++) {
      data_read_count = buf_str.indexOf( ",", data_read_count ); //3つ目の区切り文字を探す
      data_read_count++; //不要データなので次のデータへ
    }

    //日1桁目を取得
    day_1 = buf_str.substring( data_read_count, data_read_count + 1 );
    CalenderArray[4] = day_1.toInt();
    data_read_count++;
    //日2桁目を取得
    day_2 = buf_str.substring( data_read_count, data_read_count + 1 );
    CalenderArray[5] = day_2.toInt();
    data_read_count++;
    //月1桁目を取得
    month_1 = buf_str.substring( data_read_count, data_read_count + 1 );
    CalenderArray[2] = month_1.toInt();
    data_read_count++;
    //月2桁目を取得
    month_2 = buf_str.substring( data_read_count, data_read_count + 1 );
    CalenderArray[3] = month_2.toInt();
    data_read_count++;
    //年1桁目を取得
    year_1 = buf_str.substring( data_read_count, data_read_count + 1 );
    CalenderArray[0] = year_1.toInt();
    data_read_count++;
    //年2桁目を取得
    year_2 = buf_str.substring( data_read_count, data_read_count + 1 );
    CalenderArray[1] = year_2.toInt();

    data_get_flag = true;
  } else {
    data_get_flag = false;
  }
}

