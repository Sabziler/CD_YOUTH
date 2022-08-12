/*
 Name:    Timer.ino
 Created: 9/8/2020 12:20:43 PM
 Author:  USER
*/

#include <SoftwareSerial.h>
#include <avr/wdt.h>


#define SIGNAL_1 5 
#define SIGNAL_2 6
#define START 3
#define END 6
#define IDLE 9


char cRecv = 0;
char cMode = IDLE;
bool bReadyFlag = true;
unsigned char ucData = 0;


// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);

  pinMode(SIGNAL_1, INPUT);
  pinMode(SIGNAL_2, INPUT);
  
  cMode = IDLE;
  wdt_disable();
}

// the loop function runs over and over again until power down or reset
void loop() {
  
  ucData = Serial.read();   // read the character  

  if (ucData == 'R') {
    cMode = IDLE;

    Serial.print('R');
    wdt_enable(WDTO_15MS);  // 리셋
  }

  switch (cMode) {
    case START:
      // 시작 지점에서 장애물을 감지했을 때
      if (digitalRead(SIGNAL_1) == LOW) {
        Serial.print(START);
        cMode = END;
      }
      break;
  
    case END:
      // 도착지점에서 장애물을 감지했을 때
      if (digitalRead(SIGNAL_2) == LOW) {
        Serial.print(END);
        cMode = IDLE;
      }
      break;
  
    case IDLE:
      if (ucData == 'S') {
        Serial.print("S");
        cMode = START;
      }
      break;
   }
}



// 초음파센서 버전


///*
// Name:    Timer.ino
// Created: 9/8/2020 12:20:43 PM
// Author:  USER
//*/
//
//#include <SoftwareSerial.h>
//#include <avr/wdt.h>
//
//
//#define TRIG_1 9 
//#define ECHO_1 8
//#define TRIG_2 6
//#define ECHO_2 7
//
//#define START 3
//#define END 6
//#define IDLE 9
//
//
//
////SoftwareSerial CSerial(0, 1);
//
//char cRecv =  0;
//char cMode = IDLE;
//unsigned long distance_1, duration_1, distance_2, duration_2 = 1000;
//bool isOn_1 = false;
//bool isOn_2 = false;
//
//bool bReadyFlag = true;
//
//
//// the setup function runs once when you press reset or power the board
//void setup() {
//  Serial.begin(115200);
//  //CSerial.begin(9600);
//
//  pinMode(TRIG_1, OUTPUT);
//  pinMode(ECHO_1, INPUT);
//  pinMode(TRIG_2, OUTPUT);
//  pinMode(ECHO_2, INPUT);
//
//  wdt_disable();
//}
//
//// the loop function runs over and over again until power down or reset
//void loop() {
//    
//    // 센서값 측정
//    if(isOn_1){
//      digitalWrite(TRIG_1, LOW);
//      delayMicroseconds(2);
//      digitalWrite(TRIG_1, HIGH);
//      delayMicroseconds(10);
//      digitalWrite(TRIG_1, LOW);
//
//      duration_1 = pulseIn(ECHO_1, HIGH);
//      distance_1 = duration_1 * 17 / 1000;
//      //Serial.print("1 : ");
//      //Serial.println(distance_1);
//      delay(100);
//    }
//
//    if (isOn_2) {
//      digitalWrite(TRIG_2, LOW);
//      delayMicroseconds(2);
//      digitalWrite(TRIG_2, HIGH);
//      delayMicroseconds(10);
//      digitalWrite(TRIG_2, LOW);
//
//      duration_2 = pulseIn(ECHO_2, HIGH);
//      distance_2 = duration_2 * 17 / 1000;
//      //Serial.print("2 : ");
//      //Serial.println(distance_2);
//      delay(100);
//    }
//  
//  
//    if (Serial.read() == 'R') {
//      // 여기에서는 센서 하나를 끄던지 하자
//      cMode = IDLE;
//      isOn_1 = false;
//      isOn_2 = false;
//      Serial.print('R');
//      wdt_enable(WDTO_15MS);  // 리셋
//    }
//
//    //Serial.print("\nDIstance : ");
//    //Serial.println(" Cm");
//
//    switch (cMode) {
//      case START: 
//        // 기존 디폴트 거리 미만이면 장애물이 있다는 증거 
//        // 그때는 시리얼로 현재 거리를 전송한다.
//        //Serial.print("Q");
//        isOn_1 = true;
//        isOn_2 = false;
//        if (distance_1 <= 4 && distance_1 != 0){
//          Serial.print(START);  
//          //Serial.println(distance_1);
//          cMode = END;
//          distance_1 = 0;
//        }
//        break;
//
//      case END:
//        // 도착지점에서 장애물을 감지했을 때
//        isOn_1 = false;
//        isOn_2 = true;
//        if (distance_2 <= 4 && distance_2 != 0) {
//          //Serial.println(distance_2);
//          Serial.print(END);
//          distance_2 = 0;
//          cMode = IDLE;
//        }
//        break; 
//
//      case IDLE:
//        isOn_1 = false;
//        isOn_2 = false;
//
//        if (bReadyFlag) {
//          Serial.print("O");
//          bReadyFlag = false;
//        }
//
//        if (Serial.read() == 'S') {
//          Serial.print("S");
//          //Serial.print(Serial.read());
//          cMode = START;
//        }
//        break;
//      }
//}
