#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // (주소값, 16x2 디스플레이)
int trig = 12;
int echo = 13;

int LED_1 = 9;
int LED_2 = 10;
int LED_3 = 11;

void setup() {

  Serial.begin(9600); //PC모니터로 센서값을 확인하기위해서 시리얼 통신정의
                      //시리얼 통신을 이용해 PC모니터로 데이터 값을 확인하는 부분은 자주사용되기 때문에
                      //필수교육 필요  
  /*초음파 핀설정*/         
  // pinMode(7, OUTPUT);
  // pinMode(8, INPUT);
  
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  /*LCD 핀설정 부분*/
  lcd.init(); // lcd 객체 초기화
  lcd.clear();  // 화면 지우고 커서를 왼쪽 상단 모서리로 옮김         
  lcd.backlight();  	// 백라이트 on

  /*LED핀설정 부분*/
  
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  //pinMode(12, OUTPUT);

  /*buz핀 설정부분*/
  pinMode(2, OUTPUT);
}

void loop(){

  long duration, distance;

  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn (echo, HIGH); //물체에 반사되어돌아온 초음파의 시간을 변수에 저장합니다.

  //34000*초음파가 물체로 부터 반사되어 돌아오는시간 /1000000 / 2(왕복값이아니라 편도값이기때문에 나누기2를 해줍니다.)
 //초음파센서의 거리값이 위 계산값과 동일하게 Cm로 환산되는 계산공식 입니다. 수식이 간단해지도록 적용했습니다.
  distance = duration * 17 / 1000; 
  
  if (distance <= 5){ //5cm 이하일 시
    lcd.setCursor(2,0);   // 커서 옮김. 0행에 2열
    lcd.print("Danger!");
    //lcd.clear();            // LCD에 표시된 내용 지우기
    digitalWrite(LED_1,LOW); // 빨간색 LED점등 
    digitalWrite(LED_2,HIGH);
    digitalWrite(LED_3,HIGH);
    delay(500);
    lcd.clear();
  }
  else if (distance > 5 && distance <=10){ //5cm 초과 10cm 이하일 시
    lcd.setCursor(2,0);   // 커서 옮김. 0행에 2열
    lcd.print("SoSo!");
    //lcd.clear();            // LCD에 표시된 내용 지우기
    digitalWrite(LED_1,HIGH);
    digitalWrite(LED_2,LOW); // 녹색 LED점등
    digitalWrite(LED_3,HIGH);
    delay(500);
    lcd.clear();
  }
  else {
    lcd.setCursor(2,0);   //10cm 초과일시
    lcd.print("Good!");
    //lcd.clear();            // LCD에 표시된 내용 지우기
    digitalWrite(LED_1,HIGH);
    digitalWrite(LED_2,HIGH);
    digitalWrite(LED_3,LOW);  // 파란색 LED점등
    delay(500);
    lcd.clear();
  }

  //PC모니터로 초음파 거리값을 확인 하는 코드 입니다.

   //시리얼 모니터 부분 
  // Serial.print("Duration : ");
  // Serial.println(duration ); //초음파가 반사되어 돌아오는 시간을 보여줍니다.
  // Serial.print("DIstance : ");
  // Serial.print(distance); //측정된 물체로부터 거리값(cm값)을 보여줍니다.
  // Serial.println(" Cm");
  // Serial.println("");
  // delay(1000); //1초마다 측정값을 보여줍니다.
}