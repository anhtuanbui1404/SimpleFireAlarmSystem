#define BLYNK_PRINT DebugSerial
#include <MQ2.h>
#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(2, 3); //rx, tx
#define BLYNK_TEMPLATE_ID "TMPL6Zgw1oSk6"
#define BLYNK_TEMPLATE_NAME "baochaytrongcanho"
#define BLYNK_AUTH_TOKEN "2k41OJ1p57W2sp9ztZowiuINITfeg5lb"
#include <BlynkSimpleStream.h>

char auth[]=BLYNK_AUTH_TOKEN;
WidgetLED ledbaochay(V3);
const int BUZZ_PIN = 7;  /// #define BUZZ_PIN 7;
const int LIGHT_1_PIN = 6;
const int LIGHT_2_PIN = 5;
const int light_alarm_pin = 4;
const int FLAME_SENSOR_PIN = A1;
const int smoke_sensor_pin = A2;
void setup()
{
  DebugSerial.begin(9600);
  Serial.begin(9600);  ////khởi tạo giao tiếp qua cổng Serial với tốc độ truyền dữ liệu 9600 bps
//  lcd.begin(16, 2); ///// KHỞI TẠO LCD CÓ 16 CỘT VÀ 2 HÀNG
  ////THIẾT LẬP TRẠNG THÁI CHÂN DỮ LIỆU VÀO VÀ RA CỦA ARDUINO
  pinMode(FLAME_SENSOR_PIN, INPUT);
  pinMode(BUZZ_PIN, OUTPUT);
  pinMode(LIGHT_1_PIN, OUTPUT);
  pinMode(LIGHT_2_PIN, OUTPUT);
  pinMode(light_alarm_pin, OUTPUT);
  pinMode(smoke_sensor_pin, INPUT);
  Blynk.begin(Serial, auth);
}
BLYNK_WRITE(V4)
{
  int pindata = param.asInt();
  if(pindata==1)
  {
    digitalWrite(BUZZ_PIN,HIGH);
  }
  else
  {
    digitalWrite(BUZZ_PIN,LOW);
  }
}
void nhietdoco2()
{
  int GT_digital = analogRead (A3);     //////đọc giá trị analog
  float voltage_T = GT_digital * (5.0 / 1023.0);  ////quy đổi giá trị digital thành điện áp (lấy sẵn từ mã nguồn mở: File->examples->01.Basics->ReadAnalogVoltage)
  ///sensor_output=10mV/*c, Temp=voltage(mV)/10   =>temp=voltage*100
  float T = voltage_T * 100;
  int chay = digitalRead(FLAME_SENSOR_PIN);      ///ĐỌC DỮ LIỆU LẤY TỪ ĐẦU VÀO ANALOG_PIN_1
  int smoke = digitalRead(smoke_sensor_pin); 
  Blynk.virtualWrite(V1,T);
  Blynk.virtualWrite(V2,smoke);
  if (chay == HIGH or smoke > 0.2 or T > 40 )
  {
    ledbaochay.on();
  }
  else
  {
    ledbaochay.off();
  }
}
void loop()
{
  Blynk.run();
  nhietdoco2();
}
