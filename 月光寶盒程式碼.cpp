#include <SPI.h>
#include <SD.h>
#include <ThreeWire.h>
#include <RtcDS1302.h>
#include <LedControl.h>
#include <binary.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

ThreeWire myWire(8,9,7);
RtcDS1302<ThreeWire> Rtc(myWire);
const String matrix_char_half_69999996[8] = {"0110", "1001", "1001", "1001", "1001", "1001", "1001", "0110"};
const String matrix_char_half_26222227[8] = {"0010", "0110", "0010", "0010", "0010", "0010", "0010", "0111"};
const String matrix_char_half_6911124F[8] = {"0110", "1001", "0001", "0001", "0001", "0010", "0100", "1111"};
const String matrix_char_half_69161196[8] = {"0110", "1001", "0001", "0110", "0001", "0001", "1001", "0110"};
const String matrix_char_half_137D9F11[8] = {"0001", "0011", "0111", "1101", "1001", "1111", "0001", "0001"};
const String matrix_char_half_F88E1196[8] = {"1111", "1000", "1000", "1110", "0001", "0001", "1001", "0110"};
const String matrix_char_half_698E9996[8] = {"0110", "1001", "1000", "1110", "1001", "1001", "1001", "0110"};
const String matrix_char_half_F1124888[8] = {"1111", "0001", "0001", "0010", "0100", "1000", "1000", "1000"};
const String matrix_char_half_69969996[8] = {"0110", "1001", "1001", "0110", "1001", "1001", "1001", "0110"};
const String matrix_char_half_69997196[8] = {"0110", "1001", "1001", "1001", "0111", "0001", "1001", "0110"};
byte LEDArray[8];
const byte matrix_char_3C42A58199A5423C[8] PROGMEM = {B00111100, B01000010, B10100101, B10000001, B10011001, B10100101, B01000010, B00111100};

String k = (String)("11223344");
String j = (String)("");
const int sw = 2;
Sd2Card sd_card;
const int sd_cs_pin = 10;
const int x_pin = A6;
const int y_pin = A7;
long time2;
int i;
LedControl lc_matrix = LedControl(A2, A0, A1, 1);
int click_times;
File myFile;
long time1;
int x_value;
int y_value;

LiquidCrystal_I2C I2CLCD(0x27, 16, 2);

void setup() {
  Rtc.Begin();
  Rtc.SetIsRunning(true);
  pinMode(sw, INPUT_PULLUP);
  I2CLCD.begin();
  pinMode(x_pin, INPUT);
  pinMode(y_pin, INPUT);

  time2 = millis();
  i = 15;
    for(int index = 0; index < lc_matrix.getDeviceCount(); index++) {
      lc_matrix.shutdown(index, false);
    }
  lc_matrix.clearDisplay(0);
  lc_matrix.setIntensity(0, 15);
  click_times = 0;
  I2CLCD.clear();
  I2CLCD.backlight();
    for(int index = 0; index < lc_matrix.getDeviceCount(); index++) {
      lc_matrix.shutdown(index, false);
    }
  lc_matrix.clearDisplay(0);
  lc_matrix.setIntensity(0, 15);

}

void loop() {
  if (i > 0) {
    //使用搖桿輸入密碼 並於SD卡內存入當前輸入的密碼及時間
    if (x_value < 100) {
      j += String("3");
      myFile = SD.open("record.txt", FILE_WRITE);
      myFile.println((String(String(Rtc.GetDateTime().Year()) + String("/") + String(Rtc.GetDateTime().Month()) + String("/") + String(Rtc.GetDateTime().Day()) + String(" ") + String(Rtc.GetDateTime().Hour()) + String(":") + String(Rtc.GetDateTime().Minute()) + String(":") + String(Rtc.GetDateTime().Second())) + String(",") + String("輸入:") + String(j)));
      myFile.flush();
      myFile.close();
      delay(300);
    } else if (x_value > 900) {
      j += String("4");
      myFile = SD.open("record.txt", FILE_WRITE);
      myFile.println((String(String(Rtc.GetDateTime().Year()) + String("/") + String(Rtc.GetDateTime().Month()) + String("/") + String(Rtc.GetDateTime().Day()) + String(" ") + String(Rtc.GetDateTime().Hour()) + String(":") + String(Rtc.GetDateTime().Minute()) + String(":") + String(Rtc.GetDateTime().Second())) + String(",") + String("輸入:") + String(j)));
      myFile.flush();
      myFile.close();
      delay(300);
    } else if (y_value < 100) {
      j += String("1");
      myFile = SD.open("record.txt", FILE_WRITE);
      myFile.println((String(String(Rtc.GetDateTime().Year()) + String("/") + String(Rtc.GetDateTime().Month()) + String("/") + String(Rtc.GetDateTime().Day()) + String(" ") + String(Rtc.GetDateTime().Hour()) + String(":") + String(Rtc.GetDateTime().Minute()) + String(":") + String(Rtc.GetDateTime().Second())) + String(",") + String("輸入:") + String(j)));
      myFile.flush();
      myFile.close();
      delay(300);
    } else if (y_value > 900) {
      j += String("2");
      myFile = SD.open("record.txt", FILE_WRITE);
      myFile.println((String(String(Rtc.GetDateTime().Year()) + String("/") + String(Rtc.GetDateTime().Month()) + String("/") + String(Rtc.GetDateTime().Day()) + String(" ") + String(Rtc.GetDateTime().Hour()) + String(":") + String(Rtc.GetDateTime().Minute()) + String(":") + String(Rtc.GetDateTime().Second())) + String(",") + String("輸入:") + String(j)));
      myFile.flush();
      myFile.close();
      delay(300);
    }
    if (digitalRead(sw) == LOW) {
      delay(20);
      if (digitalRead(sw) == LOW) {
        click_times = click_times + 1;
      }
      //按下搖桿時偵測當前輸入密碼是否正確
      if (digitalRead(sw) == LOW) {
        if (k == j) {
          I2CLCD.setCursor(0, 0);
          I2CLCD.print("                    ");
          I2CLCD.setCursor(0, 0);
          I2CLCD.print("PWD Pass!!");
          delay(1000);
          I2CLCD.setCursor(0, 0);
          I2CLCD.print("                    ");
          I2CLCD.setCursor(0, 0);
          I2CLCD.print(j);
        } else {
          I2CLCD.setCursor(0, 0);
          I2CLCD.print("                    ");
          I2CLCD.setCursor(0, 0);
          I2CLCD.print("PWD error!!");
          delay(1000);
          j = "";
          I2CLCD.setCursor(0, 0);
          I2CLCD.print("                    ");
          I2CLCD.setCursor(0, 0);
          I2CLCD.print(j);
        }
      }
    }
    I2CLCD.setCursor(0, 1);
    I2CLCD.print((String("Click:") + String(click_times)));
    time1 = millis();
    //倒數15秒 並於LED Matrix上顯示剩餘時間
    if (time1 - time2 >= 1000) {
      if (i == 1) {
        for(int index_i = 0; index_i < 8; index_i++)
        {
          String binary_string = matrix_char_half_69999996[index_i] + matrix_char_half_26222227[index_i];
          for (int index_c = 0; index_c < 8; index_c++){
            lc_matrix.setLed(0, index_i, index_c, (binary_string.substring(index_c, index_c + 1) == "0" ? LOW : HIGH));
          }
        }
      }
      if (i == 2) {
        for(int index_i = 0; index_i < 8; index_i++)
        {
          String binary_string = matrix_char_half_69999996[index_i] + matrix_char_half_6911124F[index_i];
          for (int index_c = 0; index_c < 8; index_c++){
            lc_matrix.setLed(0, index_i, index_c, (binary_string.substring(index_c, index_c + 1) == "0" ? LOW : HIGH));
          }
        }
      }
      if (i == 3) {
        for(int index_i = 0; index_i < 8; index_i++)
        {
          String binary_string = matrix_char_half_69999996[index_i] + matrix_char_half_69161196[index_i];
          for (int index_c = 0; index_c < 8; index_c++){
            lc_matrix.setLed(0, index_i, index_c, (binary_string.substring(index_c, index_c + 1) == "0" ? LOW : HIGH));
          }
        }
      }
      if (i == 4) {
        for(int index_i = 0; index_i < 8; index_i++)
        {
          String binary_string = matrix_char_half_69999996[index_i] + matrix_char_half_137D9F11[index_i];
          for (int index_c = 0; index_c < 8; index_c++){
            lc_matrix.setLed(0, index_i, index_c, (binary_string.substring(index_c, index_c + 1) == "0" ? LOW : HIGH));
          }
        }
      }
      if (i == 5) {
        for(int index_i = 0; index_i < 8; index_i++)
        {
          String binary_string = matrix_char_half_69999996[index_i] + matrix_char_half_F88E1196[index_i];
          for (int index_c = 0; index_c < 8; index_c++){
            lc_matrix.setLed(0, index_i, index_c, (binary_string.substring(index_c, index_c + 1) == "0" ? LOW : HIGH));
          }
        }
      }
      if (i == 6) {
        for(int index_i = 0; index_i < 8; index_i++)
        {
          String binary_string = matrix_char_half_69999996[index_i] + matrix_char_half_698E9996[index_i];
          for (int index_c = 0; index_c < 8; index_c++){
            lc_matrix.setLed(0, index_i, index_c, (binary_string.substring(index_c, index_c + 1) == "0" ? LOW : HIGH));
          }
        }
      }
      if (i == 7) {
        for(int index_i = 0; index_i < 8; index_i++)
        {
          String binary_string = matrix_char_half_69999996[index_i] + matrix_char_half_F1124888[index_i];
          for (int index_c = 0; index_c < 8; index_c++){
            lc_matrix.setLed(0, index_i, index_c, (binary_string.substring(index_c, index_c + 1) == "0" ? LOW : HIGH));
          }
        }
      }
      if (i == 8) {
        for(int index_i = 0; index_i < 8; index_i++)
        {
          String binary_string = matrix_char_half_69999996[index_i] + matrix_char_half_69969996[index_i];
          for (int index_c = 0; index_c < 8; index_c++){
            lc_matrix.setLed(0, index_i, index_c, (binary_string.substring(index_c, index_c + 1) == "0" ? LOW : HIGH));
          }
        }
      }
      if (i == 9) {
        for(int index_i = 0; index_i < 8; index_i++)
        {
          String binary_string = matrix_char_half_69999996[index_i] + matrix_char_half_69997196[index_i];
          for (int index_c = 0; index_c < 8; index_c++){
            lc_matrix.setLed(0, index_i, index_c, (binary_string.substring(index_c, index_c + 1) == "0" ? LOW : HIGH));
          }
        }
      }
      if (i == 10) {
        for(int index_i = 0; index_i < 8; index_i++)
        {
          String binary_string = matrix_char_half_26222227[index_i] + matrix_char_half_69999996[index_i];
          for (int index_c = 0; index_c < 8; index_c++){
            lc_matrix.setLed(0, index_i, index_c, (binary_string.substring(index_c, index_c + 1) == "0" ? LOW : HIGH));
          }
        }
      }
      if (i == 11) {
        for(int index_i = 0; index_i < 8; index_i++)
        {
          String binary_string = matrix_char_half_26222227[index_i] + matrix_char_half_26222227[index_i];
          for (int index_c = 0; index_c < 8; index_c++){
            lc_matrix.setLed(0, index_i, index_c, (binary_string.substring(index_c, index_c + 1) == "0" ? LOW : HIGH));
          }
        }
      }
      if (i == 12) {
        for(int index_i = 0; index_i < 8; index_i++)
        {
          String binary_string = matrix_char_half_26222227[index_i] + matrix_char_half_6911124F[index_i];
          for (int index_c = 0; index_c < 8; index_c++){
            lc_matrix.setLed(0, index_i, index_c, (binary_string.substring(index_c, index_c + 1) == "0" ? LOW : HIGH));
          }
        }
      }
      if (i == 13) {
        for(int index_i = 0; index_i < 8; index_i++)
        {
          String binary_string = matrix_char_half_26222227[index_i] + matrix_char_half_69161196[index_i];
          for (int index_c = 0; index_c < 8; index_c++){
            lc_matrix.setLed(0, index_i, index_c, (binary_string.substring(index_c, index_c + 1) == "0" ? LOW : HIGH));
          }
        }
      }
      if (i == 14) {
        for(int index_i = 0; index_i < 8; index_i++)
        {
          String binary_string = matrix_char_half_26222227[index_i] + matrix_char_half_137D9F11[index_i];
          for (int index_c = 0; index_c < 8; index_c++){
            lc_matrix.setLed(0, index_i, index_c, (binary_string.substring(index_c, index_c + 1) == "0" ? LOW : HIGH));
          }
        }
      }
      if (i == 15) {
        for(int index_i = 0; index_i < 8; index_i++)
        {
          String binary_string = matrix_char_half_26222227[index_i] + matrix_char_half_F88E1196[index_i];
          for (int index_c = 0; index_c < 8; index_c++){
            lc_matrix.setLed(0, index_i, index_c, (binary_string.substring(index_c, index_c + 1) == "0" ? LOW : HIGH));
          }
        }
      }
      i = i - 1;
      time2 = millis();
    }
  } 
  //時間到時 於LCD顯示時間到 暫停密碼輸入 等待5秒後重試
  else {
    memcpy_P(&LEDArray, &matrix_char_3C42A58199A5423C, 8);
    for(int index_i = 0; index_i < 8; index_i++)
    {
      lc_matrix.setRow(0, index_i, LEDArray[index_i]);
    }
    I2CLCD.clear();
    I2CLCD.print("Time up!!");
    I2CLCD.setCursor(0, 1);
    I2CLCD.print("5s Retry");
    delay(5000);
    i = 15;
    I2CLCD.clear();
  }
  x_value = analogRead(x_pin);
  y_value = analogRead(y_pin);
  I2CLCD.setCursor(0, 0);
  I2CLCD.print((String(j)));

}