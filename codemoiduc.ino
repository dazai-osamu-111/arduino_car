#include <SoftwareSerial.h>

#define TX_PIN 8
#define RX_PIN 7
#define R_S A0  //ir sensor Right
#define L_S A1  //ir sensor Left
char value;
SoftwareSerial bluetooth(7, 8);
int baudRate[] = { 300, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200 };

int enbA = 3;
int in1 = 5;
int in2 = 6;
int in3 = 9;
int in4 = 10;
int enbB = 11;
char kytu = "";
String chuoi = "";

void setup() {
  pinMode(R_S, INPUT);  // declare if sensor as input
  pinMode(L_S, INPUT);  // declare ir sensor as input

  Serial.begin(9600);
  while (!Serial) {}

  Serial.println("Configuring, please wait...");

  for (int i = 0; i < 9; i++) {
    bluetooth.begin(baudRate[i]);
    String cmd = "AT+BAUD4";
    bluetooth.print(cmd);
    Serial.println(i);
    bluetooth.flush();
    delay(100);
  }

  bluetooth.begin(9600);
  Serial.println("Config done");
  while (!bluetooth) {}

  Serial.println("Enter AT commands:");

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enbA, OUTPUT);
  pinMode(enbB, OUTPUT);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(enbA, LOW);
  digitalWrite(enbB, LOW);
}

void loop() {

  if (bluetooth.available()) {
    Serial.println("có tín hiệu");
    kytu = bluetooth.read();
    // Serial.println(kytu);
    // kytu = Serial.read();
    Serial.println(kytu);
    chuoi = chuoi + kytu;
    // chuoi.toLowerCase();

    if (chuoi.indexOf("1") >= 0) {
      dithang(3000);
      delay(1000);
      dunglai();
      chuoi = "";
    }
    if (chuoi.indexOf("2") >= 0) {
      dilui(2000);
      delay(1000);
      dunglai();
      Serial.println(chuoi);
      chuoi = "";
    }
    if (chuoi.indexOf("3") >= 0) {
      disangtrai(400);
      delay(300);
      dunglai();
      Serial.println(chuoi);
      chuoi = "";
    }
    if (chuoi.indexOf("4") >= 0) {
      disangphai(400);
      delay(300);
      dunglai();
      Serial.println(chuoi);
      chuoi = "";
    }
    if (chuoi.indexOf("xoay phải") >= 0) {
      xoayphai(100);
      delay(300);
      dunglai();
      Serial.println(chuoi);
      chuoi = "";
    }
    if (chuoi.indexOf("xoay trái") >= 0) {
      xoaytrai(100);
      delay(300);
      dunglai();
      Serial.println(chuoi);
      chuoi = "";
    }
    if (chuoi.indexOf("5") >= 0) {
      while (1) {
        analogWrite(enbA, 150);  // Write The Duty Cycle 0 to 255 Enable Pin A for Motor1 Speed
        analogWrite(enbB, 150);  // Write The Duty Cycle 0 to 255 Enable Pin B for Motor2 Speed
        delay(1000);
        if ((digitalRead(R_S) == 0) && (digitalRead(L_S) == 0)) { forword(); }  //if Right Sensor and Left Sensor are at White color then it will call forword function

        else if ((digitalRead(R_S) == 1) && (digitalRead(L_S) == 0)) { turnRight(); }  //if Right Sensor is Black and Left Sensor is White then it will call turn Right function

         else if ((digitalRead(R_S) == 0) && (digitalRead(L_S) == 1)) { turnLeft(); }  //if Right Sensor is White and Left Sensor is Black then it will call turn Left function

        else if ((digitalRead(R_S) == 1) && (digitalRead(L_S) == 1)) { Stop(); }  //if Right Sensor and Left Sensor are at Black color then it will call Stop function
        if (bluetooth.available()) {
          char receivedChar = bluetooth.read();
          if (receivedChar == 'x') {
            // Thoát khỏi vòng lặp nếu nhận được tín hiệu 'x'
            break;
          }
        }
      }
      chuoi = "";
      dunglai();
    }
  }
}
void dithang(int tocdo) {
  analogWrite(enbA, 200);
  analogWrite(enbB, 200);
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);
}

void dunglai() {
  analogWrite(enbA, 0);
  analogWrite(enbB, 0);
  digitalWrite(in1, 0);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 0);
}

void disangphai(int tocdo) {
  analogWrite(enbA, 200);
  analogWrite(enbB, 200);
  digitalWrite(in1, 0);
  digitalWrite(in2, 1);
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);
}
void disangtrai(int tocdo) {
  analogWrite(enbA, 200);
  analogWrite(enbB, 200);
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  digitalWrite(in3, 1);
  digitalWrite(in4, 0);
}

void dilui(int tocdo) {
  analogWrite(enbA, 200);
  analogWrite(enbB, 200);
  digitalWrite(in1, 0);
  digitalWrite(in2, 1);
  digitalWrite(in3, 1);
  digitalWrite(in4, 0);
}

void xoay(int tocdo) {
  analogWrite(enbA, 200);
  analogWrite(enbB, 200);
  digitalWrite(in1, 0);
  digitalWrite(in2, 1);
  digitalWrite(in3, 1);
  digitalWrite(in4, 0);
}
void xoaytrai(int tocdo) {
  analogWrite(enbA, 200);
  analogWrite(enbB, 200);
  digitalWrite(in1, 1);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 1);
}
void xoayphai(int tocdo) {
  analogWrite(enbA, 200);
  analogWrite(enbB, 200);
  digitalWrite(in1, 0);
  digitalWrite(in2, 1);
  digitalWrite(in3, 1);
  digitalWrite(in4, 0);
}

void forword() {            //forword
  digitalWrite(in1, HIGH);  //Right Motor forword Pin
  digitalWrite(in2, LOW);   //Right Motor backword Pin
  digitalWrite(in3, LOW);   //Left Motor backword Pin
  digitalWrite(in4, HIGH);  //Left Motor forword Pin
}

void turnRight() {          //turnRight
  digitalWrite(in1, LOW);   //Right Motor forword Pin
  digitalWrite(in2, HIGH);  //Right Motor backword Pin
  digitalWrite(in3, LOW);   //Left Motor backword Pin
  digitalWrite(in4, HIGH);  //Left Motor forword Pin
}

void turnLeft() {           //turnLeft
  digitalWrite(in1, HIGH);  //Right Motor forword Pin
  digitalWrite(in2, LOW);   //Right Motor backword Pin
  digitalWrite(in3, HIGH);  //Left Motor backword Pin
  digitalWrite(in4, LOW);   //Left Motor forword Pin
}

void Stop() {              //stop
  digitalWrite(in1, LOW);  //Right Motor forword Pin
  digitalWrite(in2, LOW);  //Right Motor backword Pin
  digitalWrite(in3, LOW);  //Left Motor backword Pin
  digitalWrite(in4, LOW);  //Left Motor forword Pin
}

// void chayduongden(int tocdo) {

//   // delay(1000);
//   if((digitalRead(R_S) == 0)&&(digitalRead(L_S) == 0)){dithang(200);} //if Right Sensor and Left Sensor are at White color then it will call forword function

//   if((digitalRead(R_S) == 1)&&(digitalRead(L_S) == 0)){disangphai(200);} //if Right Sensor is Black and Left Sensor is White then it will call turn Right function

//   if((digitalRead(R_S) == 0)&&(digitalRead(L_S) == 1)){disangtrai(200);} //if Right Sensor is White and Left Sensor is Black then it will call turn Left function

//   if((digitalRead(R_S) == 1)&&(digitalRead(L_S) == 1)){dunglai();} //if Right Sensor and Left Sensor are at Black color then it will call Stop function
// }
