void Button1InputCheck() {
  /*
  boolean BeforeB1Status = false; //前周期のボタン1の状態
  boolean NowB1Status = false; //今周期のボタン1の状態
  */

  if( digitalRead(Button1) == LOW ){
    InputB1Flag = true;
  }else{
    InputB1Flag = false;
  }
  /*
  //プルアップしているのでLOW=ON
  if( digitalRead(Button1) == LOW ){
    NowB1Status = true;
    if( BeforeB1Status == true ){
      InputB1Flag = true;
    }
  }else{
    NowB1Status = false;
    InputB1Flag = false;
  }
  BeforeB1Status = NowB1Status;
  */
}

void Button2InputCheck() {
  /*
  boolean BeforeB2Status = false; //前周期のボタン2の状態
  boolean NowB2Status = false; //今周期のボタン2の状態
  */

  if( digitalRead(Button2) == LOW ){
    InputB2Flag = true;
  }else{
    InputB2Flag = false;
  }
  /*
  //プルアップしているのでLOW=ON
  if( digitalRead(Button2) == LOW ){
    NowB2Status = true;
    if( BeforeB2Status == true ){
      InputB2Flag = true;
    }
  }else{
    NowB2Status = false;
    InputB2Flag = false;
  }
  BeforeB2Status = NowB2Status;
  */
}

