void NixieLightning(char port, char number){
  switch( port ){
    case 1: //1つ目のニキシー管を選択
      digitalWrite(NixieSelectPort1, HIGH);
      digitalWrite(NixieSelectPort2, LOW);
      digitalWrite(NixieSelectPort3, LOW);
      digitalWrite(NixieSelectPort4, LOW);
      digitalWrite(NixieSelectPort5, LOW);
      digitalWrite(NixieSelectPort6, LOW);
      break;
    case 2: //2つ目のニキシー管を選択
      digitalWrite(NixieSelectPort1, LOW);
      digitalWrite(NixieSelectPort2, HIGH);
      digitalWrite(NixieSelectPort3, LOW);
      digitalWrite(NixieSelectPort4, LOW);
      digitalWrite(NixieSelectPort5, LOW);
      digitalWrite(NixieSelectPort6, LOW);
      break;
    case 3: //3つ目のニキシー管を選択
      digitalWrite(NixieSelectPort1, LOW);
      digitalWrite(NixieSelectPort2, LOW);
      digitalWrite(NixieSelectPort3, HIGH);
      digitalWrite(NixieSelectPort4, LOW);
      digitalWrite(NixieSelectPort5, LOW);
      digitalWrite(NixieSelectPort6, LOW);
      break;
    case 4: //4つ目のニキシー管を選択
      digitalWrite(NixieSelectPort1, LOW);
      digitalWrite(NixieSelectPort2, LOW);
      digitalWrite(NixieSelectPort3, LOW);
      digitalWrite(NixieSelectPort4, HIGH);
      digitalWrite(NixieSelectPort5, LOW);
      digitalWrite(NixieSelectPort6, LOW);
      break;
    case 5: //5つ目のニキシー管を選択
      digitalWrite(NixieSelectPort1, LOW);
      digitalWrite(NixieSelectPort2, LOW);
      digitalWrite(NixieSelectPort3, LOW);
      digitalWrite(NixieSelectPort4, LOW);
      digitalWrite(NixieSelectPort5, HIGH);
      digitalWrite(NixieSelectPort6, LOW);
      break;
    case 6: //6つ目のニキシー管を選択
      digitalWrite(NixieSelectPort1, LOW);
      digitalWrite(NixieSelectPort2, LOW);
      digitalWrite(NixieSelectPort3, LOW);
      digitalWrite(NixieSelectPort4, LOW);
      digitalWrite(NixieSelectPort5, LOW);
      digitalWrite(NixieSelectPort6, HIGH);
      break;
    default:
      //処理なし
      break;
  }

  switch( number ){
    case 0: //0を表示
      digitalWrite(NixieNamberSelectPort1, LOW);
      digitalWrite(NixieNamberSelectPort2, LOW);
      digitalWrite(NixieNamberSelectPort3, LOW);
      digitalWrite(NixieNamberSelectPort4, LOW);
      break;
    case 1: //1を表示
      digitalWrite(NixieNamberSelectPort1, HIGH);
      digitalWrite(NixieNamberSelectPort2, LOW);
      digitalWrite(NixieNamberSelectPort3, LOW);
      digitalWrite(NixieNamberSelectPort4, LOW);
      break;
    case 2: //2を表示
      digitalWrite(NixieNamberSelectPort1, LOW);
      digitalWrite(NixieNamberSelectPort2, HIGH);
      digitalWrite(NixieNamberSelectPort3, LOW);
      digitalWrite(NixieNamberSelectPort4, LOW);
      break;
    case 3: //3を表示
      digitalWrite(NixieNamberSelectPort1, HIGH);
      digitalWrite(NixieNamberSelectPort2, HIGH);
      digitalWrite(NixieNamberSelectPort3, LOW);
      digitalWrite(NixieNamberSelectPort4, LOW);
      break;
    case 4: //4を表示
      digitalWrite(NixieNamberSelectPort1, LOW);
      digitalWrite(NixieNamberSelectPort2, LOW);
      digitalWrite(NixieNamberSelectPort3, HIGH);
      digitalWrite(NixieNamberSelectPort4, LOW);
      break;
    case 5: //5を表示
      digitalWrite(NixieNamberSelectPort1, HIGH);
      digitalWrite(NixieNamberSelectPort2, LOW);
      digitalWrite(NixieNamberSelectPort3, HIGH);
      digitalWrite(NixieNamberSelectPort4, LOW);
      break;
    case 6: //6を表示
      digitalWrite(NixieNamberSelectPort1, LOW);
      digitalWrite(NixieNamberSelectPort2, HIGH);
      digitalWrite(NixieNamberSelectPort3, HIGH);
      digitalWrite(NixieNamberSelectPort4, LOW);
      break;
    case 7: //7を表示
      digitalWrite(NixieNamberSelectPort1, HIGH);
      digitalWrite(NixieNamberSelectPort2, HIGH);
      digitalWrite(NixieNamberSelectPort3, HIGH);
      digitalWrite(NixieNamberSelectPort4, LOW);
      break;
    case 8: //8を表示
      digitalWrite(NixieNamberSelectPort1, LOW);
      digitalWrite(NixieNamberSelectPort2, LOW);
      digitalWrite(NixieNamberSelectPort3, LOW);
      digitalWrite(NixieNamberSelectPort4, HIGH);
      break;
    case 9: //9を表示
      digitalWrite(NixieNamberSelectPort1, HIGH);
      digitalWrite(NixieNamberSelectPort2, LOW);
      digitalWrite(NixieNamberSelectPort3, LOW);
      digitalWrite(NixieNamberSelectPort4, HIGH);
      break;
  }
}

