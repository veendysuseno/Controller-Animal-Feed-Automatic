#include <HCSR04.h>                 //Library HCSR04
#include <LiquidCrystal_I2C.h>      //Library LCD I2C

LiquidCrystal_I2C lcd(0x27,16,2);   //Alamat I2C
HCSR04 hc(5,6);                     //initialisation class HCSR04 (trig pin , echo pin)

float TinggiSensor = 11.21;         //Tinggi pemasangan sensor
float TingkatPakan = 0;             //Tingkat pakan

#define Buzzer 8

void setup() {
  lcd.init ();                //Mulai LCD
  lcd.setBacklight(HIGH);
  pinMode(Buzzer, OUTPUT);    //Setting I/O
}

void loop() {
  TingkatPakan = TinggiSensor - hc.dist();          //Rumus mencari tingkat pakan
  TingkatPakan = map(TingkatPakan, 0, 12, 0, 100);  //konversi ke persen

  if (TingkatPakan > 100){      //Set maksimal 100%
    TingkatPakan = 100;
  }

  else if (TingkatPakan < 0){   //Antisipasi error sensor < 0%
    TingkatPakan = 0;
  }
  
  lcd.setCursor(0,0);
  lcd.print("Pakan : ");
  lcd.print(TingkatPakan);          //Tampilkan tingkat pakan
  lcd.print("%");
  
  if(TingkatPakan < 15){            //Jika tingkat pakan < 15%, maka
    alarm();                        //Nyalakan alarm
    lcd.setCursor(0,1);
    lcd.print("ISI PAKAN...!!!");   //tampilan text
  }
  
  delay(1000);
  lcd.clear();
}

void alarm(){                         //Prosedur alarm
  digitalWrite(Buzzer, HIGH);         //Nyalakan buzzer
  delay(500);                         //Selama 500 ms
  digitalWrite(Buzzer, LOW);          //Matikan buzzer
  delay(500);                         //Selama 500 ms
}
