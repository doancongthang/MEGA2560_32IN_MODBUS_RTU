#include <ModbusRTU.h>
#include <Arduino.h>
// Firmware đã test ok cho board 32Input
#define REGN 10
//#define SLAVE_ID 1
//For board Ver1
/*
 int input[] =   { 53, 52, 51, 50, 10, 11, 12, 13,
                   37, 36, 35, 34, 33, 32, 31, 30,
                   21, 20, 19, 18, 38,
                   A0, A1, A2, A3, A4, A5, A6, A7};
*/                   
//Define for board Ver2
 int input[] =   { 49, 48, 47, 46, 45, 44, 43, 42,
                   37, 36, 35, 34, 33, 32, 31, 30,
                   A0, A1, A2, A3, A4, A5, A6, A7,
                   A8, A9, A10, A11, A12, A13, A14, A15};
#define ID1 22 // AD0
#define ID2 23 // AD1
#define ID3 24 // AD2
#define ID4 25 // AD3
#define ID5 26 // AD4
#define ID6 27 // AD5
#define ID7 28 // AD6
#define ID8 29 // AD7

#define BR1 8   //ok
#define BR2 9   //ok
#define BR3 10  //ok
#define BR4 11  //ok
#define BR5 12  //ok
#define BR6 13  //ok

 int SLAVE_ID = 1;
 long ModbusBaurate;
 ModbusRTU mb;
 void SetIDModbus()
 {
   if (digitalRead(ID1) == 1)
     SLAVE_ID += 1;
   if (digitalRead(ID2) == 1)
     SLAVE_ID += 2;
   if (digitalRead(ID3) == 1)
     SLAVE_ID += 4;
   if (digitalRead(ID4) == 1)
     SLAVE_ID += 8;
   if (digitalRead(ID5) == 1)
     SLAVE_ID += 16;
   if (digitalRead(ID6) == 1)
     SLAVE_ID += 32;
   if (digitalRead(ID7) == 1)
     SLAVE_ID += 64;
   if (digitalRead(ID8) == 1)
     SLAVE_ID += 128;
}

int SetbaurateModbusRTU()
{
  // bool BR1, BR2, BR3 = true, BR4, BR5, BR6;
  if (digitalRead(BR1) == 1)
  {
    // Serial3.begin(14400);
    mb.setBaudrate(14400);
    ModbusBaurate = 14400;
  }
  if (digitalRead(BR2) == 1)
  {
    // Serial3.begin(19200);
    mb.setBaudrate(19200);
    ModbusBaurate = 19200;
  }
  if (digitalRead(BR3) == 1)
  {
    // Serial3.begin(38400);
    mb.setBaudrate(38400);
    ModbusBaurate = 38400;
  }
  if (digitalRead(BR4) == 1)
  {
    // Serial3.begin(56000);
    mb.setBaudrate(56000);
    ModbusBaurate = 56000;
  }
  if (digitalRead(BR5) == 1)
  {
    // Serial3.begin(57600);
    mb.setBaudrate(57600);
    ModbusBaurate = 57600;
  }
  if (digitalRead(BR6) == 1)
  {
    // Serial3.begin(115200);
    mb.setBaudrate(115200);
    ModbusBaurate = 115200;
  }
  if ((digitalRead(BR1) == LOW) & (digitalRead(BR2) == LOW) & (digitalRead(BR3) == LOW) & (digitalRead(BR4) == LOW) & (digitalRead(BR5) == LOW) & (digitalRead(BR6) == LOW))
  {
    // Serial3.begin(9600);
    mb.setBaudrate(9600);
    ModbusBaurate = 9600;
 }
 return ModbusBaurate;
}

void setup()
{
  Serial.begin(9600);
  for (int i = 0; i < 32; i++)
  {
    pinMode(input[i], INPUT);
  }
  pinMode(ID1, INPUT);
  pinMode(ID2, INPUT);
  pinMode(ID3, INPUT);
  pinMode(ID4, INPUT);
  pinMode(ID5, INPUT);
  pinMode(ID6, INPUT);
  pinMode(ID7, INPUT);
  pinMode(ID8, INPUT);

  pinMode(BR1, INPUT);
  pinMode(BR2, INPUT);
  pinMode(BR3, INPUT);
  pinMode(BR4, INPUT);
  pinMode(BR5, INPUT);
  pinMode(BR6, INPUT);
  SetIDModbus();
  SetbaurateModbusRTU();
  Serial3.begin(ModbusBaurate, SERIAL_8N1);

  mb.begin(&Serial3);
  mb.setBaudrate(ModbusBaurate);
  mb.slave(SLAVE_ID);
  mb.addCoil(0, 0, 32);  //  Thêm 100 Coils
  mb.addHreg(0, 0, 32);  //  Thêm thanh ghi hoding register với địa chỉ bắt đầu = 0 và độ dài thanh ghi =100
  mb.addIsts(0, 0, 32);  //  Thêm thanh ghi discrete với địa chỉ bắt đầu = 0, giá trị set ban đầu = false và độ dài thanh ghi = 100
  mb.addIreg(0, 0, 10);   //  Thêm thanh ghi discrete với địa chỉ bắt đầu = 0, giá trị set ban đầu = false và độ dài thanh ghi = 100
  //mb.Ireg(0,1992);      //  Dùng cho xác thực board từ PLC
}
/*----------------------------------------------------------------*/
/*
void loop()
{
  //mb.Ists(0, 1);

  // for (int i = 0; i < 100; i++)
  // {
  //   mb.Ists(i, random(0, 2));
  // }
   for (int i = 0; i <= 100; i++)
   {
     mb.Ists(i, digitalRead(input[i]));
   }

  // for (int i = 0; i < 100; i++)
  // {
  //   mb.Hreg(i, random(0, 10));
  // }

  mb.task();
  yield();

  //For test ID
  //Serial.println(mb.Ireg(0));
}
*/

/*----------------------------------------------------------------*/
// Firmware for board 32Input
/*
void loop()
{
  while (mb.Hreg(0) == 1992)
  {
    for (int i = 0; i <= 100; i++)
    {
      mb.Ists(i, digitalRead(input[i]));
    }

    mb.task();
    yield();
  }
  mb.task();
  yield();
}
*/

/*----------------------------------------------------------------*/
//// Firmware for board 16In/16Out
//*
void loop()
{
  //while (mb.Hreg(0) == 1992)
  {
    //Đọc input & gán vào thanh ghi
    for (int i = 0; i < 32; i++)
    {
      mb.Ists(i, digitalRead(input[i]));
    }
    mb.task();
    yield();
  }
}
//*/