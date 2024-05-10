
#include <MQ2.h>  ////KHAI BÁO THƯ VIỆN MQ2 CHO SENSOR CẢM BIẾN KHÓI MQ 2
#include <LiquidCrystal.h>   //// KHỞI TẠO THƯ VIỆN màn hình tinh thể lỏng(LCD)
LiquidCrystal lcd(13, 12, 11, 10, 9, 8); //// CÁC CHÂN CỦA MÀN HÌNH LCD(tinh thể lỏng) NỐI VỚI ARDUINO lcd(RS: chọn thanh ghi,EN:enable cho phép ghi dữ liệu lên lcd,D7,D6,D5,D4)
///KHỞI TẠO CÁC CHÂN
const int BUZZ_PIN = 7;  /// #define BUZZ_PIN 7;
const int LIGHT_1_PIN = 6;
const int LIGHT_2_PIN = 5;
const int light_alarm_pin = 4;
const int FLAME_SENSOR_PIN = A1;
const int smoke_sensor_pin = A2;
//const int temperature_pin= A3;
void setup()
{
  Serial.begin(9600);  ////khởi tạo giao tiếp qua cổng Serial với tốc độ truyền dữ liệu 9600 bps
  lcd.begin(16, 2); ///// KHỞI TẠO LCD CÓ 16 CỘT VÀ 2 HÀNG
  ////THIẾT LẬP TRẠNG THÁI CHÂN DỮ LIỆU VÀO VÀ RA CỦA ARDUINO
  pinMode(FLAME_SENSOR_PIN, INPUT);
  pinMode(BUZZ_PIN, OUTPUT);
  pinMode(LIGHT_1_PIN, OUTPUT);
  pinMode(LIGHT_2_PIN, OUTPUT);
  pinMode(light_alarm_pin, OUTPUT);
  pinMode(smoke_sensor_pin, INPUT);
}
void loop()
{
  int GT_digital = analogRead (A3);     //////đọc giá trị analog
  float voltage_T = GT_digital * (5.0 / 1023.0);  ////quy đổi giá trị digital thành điện áp (lấy sẵn từ mã nguồn mở: File->examples->01.Basics->ReadAnalogVoltage)
  ///sensor_output=10mV/*c, Temp=voltage(mV)/10   =>temp=voltage*100
  float T = voltage_T * 100;
  int chay = digitalRead(FLAME_SENSOR_PIN);      ///ĐỌC DỮ LIỆU LẤY TỪ ĐẦU VÀO ANALOG_PIN_1
  int smoke = digitalRead(smoke_sensor_pin);     ///ĐỌC DỮ LIỆU LẤY TỪ ĐẦU VÀO ANALOG_PIN_2
  ///NGƯỠNG khói,CO.CO2 TRONG 1 VỤ HỎA HOẠN THƯỜNG Ở MỨC che phủ >20% trên 1 khoảng cách
  if (chay == HIGH or smoke > 0.2 or T > 40 ) /////KHI ĐÁM CHÁY XẢY RA       độ che mờ khói trên 1 khoẳng cách(mét) TB>20%, nhiệt độ phòng duy trì 27 độ C
  {
    /////ĐẨY DỮ LIỆU RA CÁC THIẾT BỊ KẾT NỐI VỚI ARDUINO
    digitalWrite(light_alarm_pin, HIGH);      /////KHI CÓ ĐÁM CHÁY XẢY RA ĐÈN BÁO ĐỘNG SẼ BẬT
    //delay(100);
    //digitalWrite(light_alarm_pin,LOW);
    //delay(100);
    digitalWrite(LIGHT_1_PIN, HIGH);       /////KHI CÓ ĐÁM CHÁY XẢY RA ĐÈN SẼ BẬT ĐỂ SOI SANG LỐI ĐI
    digitalWrite(LIGHT_2_PIN, HIGH);
    digitalWrite(BUZZ_PIN, HIGH);     ////KHI CÓ ĐÁM CHÁY XẢY RA SẼ CÓ CÒI BÁO ĐỘNG
    lcd.setCursor(4, 0);    ////CHỈ ĐỊNH NƠI KÝ TỰ BẮT ĐẦU
    lcd.print("BAO DONG");      ////IN RA MÀN HÌNH LCD KÝ TỰ MONG MUỐN
    lcd.setCursor(3, 1);
    lcd.print("<= EXIT =>");
    delay(500);
  }
  else
  {
    digitalWrite(LIGHT_1_PIN, LOW);
    digitalWrite(light_alarm_pin, LOW);
    digitalWrite(LIGHT_2_PIN, LOW);
    digitalWrite(BUZZ_PIN, LOW);
    lcd.clear();
    delay(100);
    lcd.setCursor(4, 0);
    lcd.print("AN TOAN");
    delay(500);
  }
}
