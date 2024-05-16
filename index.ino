#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define NEM_OLCER_GUC 7
#define NEM_OLCER_PIN A0

#define ROLE_PIN 2
#define ROLE_ACIK HIGH
#define ROLE_KAPALI LOW

#define LIMIT_SEVIYE 750

int roleOncekiDurumu = ROLE_KAPALI;
int roleSuankiDurumu = ROLE_KAPALI;

void setup() {
  pinMode(NEM_OLCER_GUC, OUTPUT);
  pinMode(ROLE_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(ROLE_PIN, ROLE_KAPALI);
  digitalWrite(NEM_OLCER_GUC, HIGH);
  
  lcd.begin();
  lcd.setCursor(3, 0);
  lcd.print("Nem Dusuk");

  Serial.begin(9600);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW); 
  delay(500); 

  int nemSeviyesi = nemSeviyesiniOlc();
  
  if(nemSeviyesi <= LIMIT_SEVIYE){
    roleSuankiDurumu = ROLE_KAPALI;
  }else{
    roleSuankiDurumu = ROLE_ACIK;
  }
  
  Serial.println(nemSeviyesi);
  
  if(roleOncekiDurumu == roleSuankiDurumu) return;

  lcd.clear();
  lcd.setCursor(3, 0);
  if(nemSeviyesi <= LIMIT_SEVIYE){
    lcd.print("Nem Yuksek");
    digitalWrite(ROLE_PIN, ROLE_KAPALI);
  }else{
    lcd.print("Nem Dusuk");
    digitalWrite(ROLE_PIN, ROLE_ACIK);
  }

  roleOncekiDurumu = roleSuankiDurumu;
  delay(1000);
}

int nemSeviyesiniOlc() {
  digitalWrite(NEM_OLCER_GUC, HIGH);
  delay(50);
  int val = analogRead(NEM_OLCER_PIN);
  digitalWrite(NEM_OLCER_GUC, LOW);
  return val;
}
