//LogSample : $GPRMC,142152.000,A,3247.4679,N,12957.0161,E,0.00,36.32,250116,,,A*5A
#include <SoftwareSerial.h>
#include <string.h>
#include <stdlib.h>
#include <MsTimer2.h>
#include <Wire.h>

#define NixieSelectPort1 A0 //ニキシー管選択ポート1のピン番号
#define NixieSelectPort2 A1 //ニキシー管選択ポート2のピン番号
#define NixieSelectPort3 A2 //ニキシー管選択ポート3のピン番号
#define NixieSelectPort4 A3 //ニキシー管選択ポート4のピン番号
#define NixieSelectPort5 11 //ニキシー管選択ポート5のピン番号
#define NixieSelectPort6 12 //ニキシー管選択ポート6のピン番号
#define NixieNamberSelectPort1 2//ニキシー管ドライバIC用ポート1
#define NixieNamberSelectPort2 3//ニキシー管ドライバIC用ポート2
#define NixieNamberSelectPort3 4//ニキシー管ドライバIC用ポート3
#define NixieNamberSelectPort4 5//ニキシー管ドライバIC用ポート4
#define RTCSCLPort A5 //RTC(I2C通信)のSCLポートのピン番号(変更不可)
#define RTCSDAPort A4 //RTC(I2C通信)のSDAポートのピン番号(変更不可)
#define GpsRxPort 7 //GPS Rx (Data Out) のピン番号
#define GpsTxPort 6 //GPS Tx (Data In) のピン番号
#define Button1 10//操作ボタン1のピン番号
#define Button2 9//操作ボタン2のピン番号

#define SerialBaudrate 9600 //シリアル通信のボーレート
#define GpsBaudrate 9600 //GPSのボーレート
#define Max_Mode_Number 2 //実装モード数
#define RTCAddress 0x32 //RTCのスレーブアドレス

SoftwareSerial sGps(GpsRxPort, GpsTxPort);  // ソフトウェアシリアルの設定(ポート指定)

//0:Year1桁目, 1:Year2桁目, 2:Month1桁目, 3:Month2桁目, 4:Day1桁目, 5:Day2桁目
int CalenderArray[6] = {};
//0:Hour1桁目, 1:Hour2桁目, 2:Min1桁目, 3:Min2桁目, 4:Sec1桁目, 5:Sec2桁目
int ClockArray[6] = {};
//RTCから取得したデータ
byte seconds,minutes,hours,days,months,years;

boolean data_get_flag = false; //GPSデータ取得確認用フラグ
int InterruptCount = 0;

volatile boolean InputB1Flag = false; //ボタン1入力フラグ
volatile boolean InputB2Flag = false; //ボタン2入力フラグ

int Mode_Status = 1; //モードセレクト用変数

void InterruptFunction(){
  Button1InputCheck(); //ボタン1の状態を取得
  Button2InputCheck(); //ボタン2の状態を取得
  InterruptCount++;
}

void setup() {
  //ピン設定
  pinMode(NixieSelectPort1, OUTPUT);
  pinMode(NixieSelectPort2, OUTPUT);
  pinMode(NixieSelectPort3, OUTPUT);
  pinMode(NixieSelectPort4, OUTPUT);
  pinMode(NixieSelectPort5, OUTPUT);
  pinMode(NixieSelectPort6, OUTPUT);
  pinMode(NixieNamberSelectPort1, OUTPUT);
  pinMode(NixieNamberSelectPort2, OUTPUT);
  pinMode(NixieNamberSelectPort3, OUTPUT);
  pinMode(NixieNamberSelectPort4, OUTPUT);
  pinMode(Button1, INPUT_PULLUP);
  pinMode(Button2, INPUT_PULLUP);
  pinMode(13, OUTPUT);

  MsTimer2::set(10, InterruptFunction); //10ms毎に割込み関数を呼び出すように設定
  Serial.begin(SerialBaudrate); // シリアル通信の初期化
  sGps.begin(GpsBaudrate); //ソフトウェアシリアル(GPS)の初期化

  NixieLightning(1,1);
  //RTC初期化
  Wire.begin();
  //コンフィグ初期値セット
  Wire.beginTransmission(RTCAddress);
  Wire.write(0xE0); //コントロール1レジスタを指定
  Wire.write(0x20); //24hモードに指定
  Wire.write(0x00); //PON(パワーオンリセットフラグ)をリセット
  Wire.endTransmission();
  delay(1);

  //時計・カレンダー初期値セット
  Wire.beginTransmission(RTCAddress);
  Wire.write(0x00); //Secondsレジスタを指定
  Wire.write(0x32); //secをセット
  Wire.write(0x45); //minをセット
  Wire.write(0x11); //hourをセット
  Wire.write(0x00); //weekをセット(使用しないので0x00固定)
  Wire.write(0x20); //dayをセット
  Wire.write(0x02); //monthをセット
  Wire.write(0x16); //yearをセット
  Wire.endTransmission();
  delay(1);

  NixieLightning(2,1);
  //GPSからデータを取得できるまで実行
  do {
    GPSDataCatch();//初期値設定用のデータ取得
  } while ( data_get_flag == false );
  NowDataSet();//データを補正
  NixieLightning(3,1);
  MsTimer2::start(); //タイマー割り込み開始
}

void loop() {

  if( InterruptCount >= 100 ){
    RTCDataCatch();
    RTCValueJudge();
    InterruptCount = 0;
  }
  
  if ( InputB1Flag == true ) {
    Mode_Status++;
    if ( Mode_Status > Max_Mode_Number ) {
      Mode_Status = 1;
    }
  }
  switch (Mode_Status) {
    //モード1:時計モード
    //SUBボタン機能:ニキシー管シャッフル動作
    case 1:
      if ( InputB2Flag == true ) {
        NixieShuffle();
      }else{
        OutputClock();
      }
      break;
    //モード2:カレンダーモード
    //SUBボタン機能:GPSから時刻取得
    case 2:
      if ( InputB2Flag == true ) {
        NixieLightning(1,7); //修正中の表記
        //GPSからデータを取得できるまで実行
        do {
          GPSDataCatch();//初期値設定用のデータ取得
        } while ( data_get_flag == false );
        NowDataSet();//データを補正
      }else{
        OutputCalender();
      }
      break;
    default:
      //処理なし
      break;
  }
  
}
