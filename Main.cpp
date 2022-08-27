#include <avr/eeprom.h>

#include <virtuabotixRTC.h>

#include <SDHT.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

SDHT dht;
virtuabotixRTC myRTC(3,4,5);

LiquidCrystal_I2C lcd(0x27,16,2);

bool coil1 = true;
bool coil2 = true;

String l0 = "0";
String l1 = "0";
int lampTemp = 25;
bool tempArray [2] = {false, false};

String h0 = "0";
String h1 = "0";
String m0 = "0";
String m1 = "0";

char L1h0 = '0';
char L1h1 = '0';
char L1m0 = '0';
char L1m1 = '0';
char L1h2 = '0';
char L1h3 = '0';
char L1m2 = '0';
char L1m3 = '0';

char L2h0 = '0';
char L2h1 = '0';
char L2m0 = '0';
char L2m1 = '0';
char L2h2 = '0';
char L2h3 = '0';
char L2m2 = '0';
char L2m3 = '0';

bool timeArray [4] = {false, false, false, false};
bool L1timeStart [8] = {false, false, false, false, false, false, false, false};
bool L2timeStart [8] = {false, false, false, false, false, false, false, false};

char key = 'A';

char program = '1';

const byte rows = 4; 
const byte cols = 4; 
char keys[rows][cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[rows] = {15, 16, 17, 18};
byte colPins[cols] = {10, 11, 12, 13};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );

void timeLampController () {
  
  String currentHour;
  String currentMinute;
  
  if(myRTC.hours < 10){
      currentHour = '0' + String(myRTC.hours);
  } else {
      currentHour = String(myRTC.hours);
    };
  if(myRTC.minutes < 10){
      currentMinute = '0' + String(myRTC.minutes);
  } else {
      currentMinute = String(myRTC.minutes);
     };
     
  if((String(L1h0) + String(L1h1)) == currentHour) {
        if((String(L1m0) + String(L1m1)) == currentMinute){
            coil1 = false;
          };
    };

    if((String(L1h0) + String(L1h1) + String(L1m0) + String(L1m1)).toInt() <  (String(L1h2) + String(L1h3) + String(L1m2) + String(L1m3)).toInt()){
      if((String(L1h0) + String(L1h1) + String(L1m0) + String(L1m1)).toInt() > (currentHour + currentMinute).toInt() || (String(L1h2) + String(L1h3) + String(L1m2) + String(L1m3)).toInt() < (currentHour + currentMinute).toInt()){
        coil1 = true;
        };
  if((String(L1h0) + String(L1h1) + String(L1m0) + String(L1m1)).toInt() <= (currentHour + currentMinute).toInt()){
    if((String(L1h2) + String(L1h3) + String(L1m2) + String(L1m3)).toInt() > (currentHour + currentMinute).toInt()){
      coil1 = false;
      };
    };
  };
if((String(L1h0) + String(L1h1) + String(L1m0) + String(L1m1)).toInt() >  (String(L1h2) + String(L1h3) + String(L1m2) + String(L1m3)).toInt()){
  if((String(L1h0) + String(L1h1) + String(L1m0) + String(L1m1)).toInt() < (currentHour + currentMinute).toInt() || (String(L1h2) + String(L1h3) + String(L1m2) + String(L1m3)).toInt() > (currentHour + currentMinute).toInt()){
    coil1 = false;
    } else {
      coil1 = true;
      };
  };

  if((String(L1h2) + String(L1h3)) == currentHour) {
        if((String(L1m2) + String(L1m3)) == currentMinute){
            coil1 = true;
          };
    };

  if((String(L2h0) + String(L2h1)) == currentHour) {
        if((String(L2m0) + String(L2m1)) == currentMinute){
            coil2 = false;
          };
    };

        if((String(L2h0) + String(L2h1) + String(L2m0) + String(L2m1)).toInt() <  (String(L2h2) + String(L2h3) + String(L2m2) + String(L2m3)).toInt()){
      if((String(L2h0) + String(L2h1) + String(L2m0) + String(L2m1)).toInt() > (currentHour + currentMinute).toInt() || (String(L2h2) + String(L2h3) + String(L2m2) + String(L2m3)).toInt() < (currentHour + currentMinute).toInt()){
        coil2 = true;
        };
  if((String(L2h0) + String(L2h1) + String(L2m0) + String(L2m1)).toInt() <= (currentHour + currentMinute).toInt()){
    if((String(L2h2) + String(L2h3) + String(L2m2) + String(L2m3)).toInt() > (currentHour + currentMinute).toInt()){
      coil2 = false;
      };
    };
  };
if((String(L2h0) + String(L2h1) + String(L2m0) + String(L2m1)).toInt() >  (String(L2h2) + String(L2h3) + String(L2m2) + String(L2m3)).toInt()){
  if((String(L2h0) + String(L2h1) + String(L2m0) + String(L2m1)).toInt() < (currentHour + currentMinute).toInt() || (String(L2h2) + String(L2h3) + String(L2m2) + String(L2m3)).toInt() > (currentHour + currentMinute).toInt()){
    coil2 = false;
    } else {
      coil2 = true;
      };
  };

  if((String(L2h2) + String(L2h3)) == currentHour) {
        if((String(L2m2) + String(L2m3)) == currentMinute){
            coil2 = true;
          };
    };
  };
 
int lightSensor () {
  int ldr = analogRead(A0);
  return ldr;
  };
  
void L1timeReset () {
  for(int i = 0; i < 8; i++){
      L1timeStart[i] = false;
    };
  };

void L2timeReset () {
  for(int i = 0; i < 8; i++){
      L2timeStart[i] = false;
    };
  };
  
void tempAdjustingReset() {
  l0 = "0";
  l1 = "0";
  tempArray [0] = false;
  tempArray [1] = false;
  };

void tempSet(){
  int temp = (l0+l1).toInt();
  eeprom_write_block(&temp,17,2);
  lampTemp = temp;
  };

void adjusting2() {
  if(program == '3'){
    key = 'A';
    };
  if(program == '1'){
    key = 'A';
    };
  if(program == '2'){
       lcd.setCursor(0,0);
       lcd.print("L2: on  ");
       lcd.setCursor(8,0);
       lcd.print(String(L2h0) + String(L2h1) + ":" + String(L2m0) + String(L2m1) + "           ");
       lcd.setCursor(0,1);
       lcd.print("L2: off ");
       lcd.setCursor(8,1);
       lcd.print(String(L2h2) + String(L2h3) + ":" + String(L2m2) + String(L2m3) + "           ");
       if(L2timeStart[7] != false) {
          L2timeReset();
        };
    }; 
  };

void adjusting() {
  if(program == '1'){
    lcd.setCursor(0,0);
    lcd.print("lampa1:");
    lcd.setCursor(7,0);
    if(coil1 == true) {
      lcd.print("off zal-1");
      } else {
      lcd.print("on  wyl-1");
        };
    lcd.setCursor(0,1);
    lcd.print("lampa2:");
    lcd.setCursor(7,1);
    if(coil2 == true) {
      lcd.print("off zal-2");
      } else {
      lcd.print("on  wyl-2");
        };
    };
    
    if(program == '2'){
       lcd.setCursor(0,0);
       lcd.print("L1: on  ");
       lcd.setCursor(8,0);
       lcd.print(String(L1h0) + String(L1h1) + ":" + String(L1m0) + String(L1m1) + "           ");
       lcd.setCursor(0,1);
       lcd.print("L1: off ");
       lcd.setCursor(8,1);
       lcd.print(String(L1h2) + String(L1h3) + ":" + String(L1m2) + String(L1m3) + "           ");

       if(L1timeStart[7] != false) {
          L1timeReset();
        };
      };
      
    if(program == '3'){
       lcd.setCursor(0,0);
       lcd.print("L1 temp: ");
       lcd.setCursor(9,0);
       lcd.print(String(lampTemp));
       lcd.setCursor(11,0);
       lcd.print("C           ");
       lcd.setCursor(0,1);
       
       if(tempArray[1] == true) {
        lcd.print("Zapisac? przyc#   ");
        }else {
       lcd.print("nowa: ");
       lcd.setCursor(6,1);
       lcd.print(l0 + l1 + "              ");
          };
      };
  };

void reset () {
  h0 = "0";
  h1 = "0";
  m0 = "0";
  m1 = "0";
  timeArray[0] = false;
  timeArray[1] = false;
  timeArray[2] = false;
  timeArray[3] = false;
  };
  
void setTimeCore () {
  String hour = h0 + h1;
  String minute = m0 + m1;
  myRTC.setDS1302Time(00,minute.toInt(),hour.toInt(),6,6,8,2022);
  reset();
  key = 'A';
  };
  
void setTimeLcd () {
  lcd.setCursor(0,0);
  lcd.print("Podaj godzine:    ");
  lcd.setCursor(0,1);
  if(timeArray[3] == false) {
    lcd.print(h0 + h1 + ':' + m0 + m1 + "                  ");
    }else{
    lcd.print("Zapisac? przyc#    ");  
      };
  };

void chooseProgram() {

   lcd.setCursor(0,0);
   lcd.print("Program: ");
   lcd.setCursor(9,0);
   switch(program){
    case '1':
      lcd.print("Reka   ");
      break;
    case '2':
      lcd.print("Godz   ");
      break;
    case '3':
      lcd.print("Auto   ");
      break;
    };
   lcd.setCursor(0,1);
   lcd.print("1-Re  2-Go  3-Au ");
};

void showTimeAndTemperature() {

    myRTC.updateTime();
    lcd.setCursor(0,0);
    lcd.print("Czas: ");
    lcd.setCursor(6,0);
    
    if(myRTC.hours < 10){
      lcd.print('0' + String(myRTC.hours));
      } else {
      lcd.print(myRTC.hours);
        };
        
    lcd.setCursor(8,0);
    lcd.print(':');
    lcd.setCursor(9,0);
    if(myRTC.minutes < 10){
      lcd.print('0' + String(myRTC.minutes) + "       ");
      } else {
      lcd.print(String(myRTC.minutes) + "      ");
        };
       
    dht.read(DHT11, 2);
    lcd.setCursor(0,1);
    lcd.print("tem:");
    lcd.setCursor(4,1);
    lcd.print((dht.celsius /10)-4);
    lcd.setCursor(6,1);
    lcd.print("C ");
    lcd.setCursor(8,1);
    lcd.print("wil:");
    lcd.setCursor(12,1);
    lcd.print((dht.humidity / 10));
    lcd.setCursor(14,1);
    lcd.print("% ");
  };

void setup() {
  Serial.begin(9600);
   pinMode(7, OUTPUT);
   pinMode(8, OUTPUT);
   lcd.init();
   lcd.backlight();
   char eepromProgram = '1';
   int tempEeprom = 25;
   eeprom_read_block(&eepromProgram,0,1);
   program = eepromProgram;
   eeprom_read_block(&eepromProgram,1,1);
   L1h0 = eepromProgram;
   eeprom_read_block(&eepromProgram,2,1);
   L1h1 = eepromProgram;
   eeprom_read_block(&eepromProgram,3,1);
   L1m0 = eepromProgram;
   eeprom_read_block(&eepromProgram,4,1);
   L1m1 = eepromProgram;
   eeprom_read_block(&eepromProgram,5,1);
   L1h2 = eepromProgram;
   eeprom_read_block(&eepromProgram,6,1);
   L1h3 = eepromProgram;
   eeprom_read_block(&eepromProgram,7,1);
   L1m2 = eepromProgram;
   eeprom_read_block(&eepromProgram,8,1);
   L1m3 = eepromProgram;
   eeprom_read_block(&eepromProgram,9,1);
   L2h0 = eepromProgram;
   eeprom_read_block(&eepromProgram,10,1);
   L2h1 = eepromProgram;
   eeprom_read_block(&eepromProgram,11,1);
   L2m0 = eepromProgram;
   eeprom_read_block(&eepromProgram,12,1);
   L2m1 = eepromProgram;
   eeprom_read_block(&eepromProgram,13,1);
   L2h2 = eepromProgram;
   eeprom_read_block(&eepromProgram,14,1);
   L2h3 = eepromProgram;
   eeprom_read_block(&eepromProgram,15,1);
   L2m2 = eepromProgram;
   eeprom_read_block(&eepromProgram,16,1);
   L2m3 = eepromProgram;
   eeprom_read_block(&tempEeprom,17,2);  
   lampTemp = tempEeprom;
}

void loop() {
  if(program == '3') {
    if(((dht.celsius /10)-4) < lampTemp){
      coil1 = false;
      };
      if(((dht.celsius /10)-4)+3 >= lampTemp){
        coil1 = true;
        };
        
    if(lightSensor() > 1000){
      coil2 = true;
      }else{
        coil2 = false;
        };
    };

  if(program == '2') {
    timeLampController ();
    };

  if(coil1 == true) {
    digitalWrite(7,HIGH);
    };
  if(coil1 == false){
    digitalWrite(7, LOW);
    };
      
  if(coil2 == true) {
    digitalWrite(8,HIGH);
    };
  if(coil2 == false){
    digitalWrite(8, LOW);
    };
      
  char getKey = keypad.getKey();
  if(getKey != NO_KEY) {
    if(getKey == 'A' || getKey == 'B' || getKey =='C' || getKey == 'D' || getKey == '*'){
      key = getKey;
      };
    if(key == 'B' && (getKey == '1' || getKey == '2' || getKey == '3')) {
      program = getKey;
      char progEprom = getKey;
      eeprom_write_block(&progEprom,0,1);
      };

    if(key == 'C' && program == '2' && getKey != 'A' && getKey != 'B' && getKey != 'C' && getKey != 'D' && getKey != '*' && getKey != '#') {
          if(L1timeStart[0] == false && (getKey == '0' || getKey == '1' || getKey == '2')) {
               L1timeStart[0] = true;
               L1h0 = getKey;
               char progEprom = getKey;
               eeprom_write_block(&progEprom,1,1);
               return;
            };
          if(L1timeStart[1] == false && L1timeStart[0] != false) {
               if(L1h0 == '2' && (getKey == '0' || getKey == '1' || getKey == '2' || getKey == '3')){
                  L1timeStart[1] = true;
                  L1h1 = getKey;
                  char progEprom = getKey;
                  eeprom_write_block(&progEprom,2,1);
                  return;
                };
                if(L1h0 == '0' || L1h0 == '1') {
                  L1timeStart[1] = true;
                  L1h1 = getKey;
                  char progEprom = getKey;
                  eeprom_write_block(&progEprom,2,1);
                  return;
                }; 
            };
          if(L1timeStart[2] == false && L1timeStart[1] != false && (getKey == '0' || getKey == '1' || getKey == '2' || getKey == '3' || getKey == '4' || getKey == '5' )) {
              L1timeStart[2] = true;
              L1m0 = getKey;
              char progEprom = getKey;
              eeprom_write_block(&progEprom,3,1);
              return;
            };
            
          if(L1timeStart[2] != false && L1timeStart[3] == false) {
              L1timeStart[3] = true;
              L1m1 = getKey;
              char progEprom = getKey;
              eeprom_write_block(&progEprom,4,1);
              return;
            };
          if(L1timeStart[3] != false &&  L1timeStart[4] == false && (getKey == '0' || getKey == '1' || getKey == '2')) {
               L1timeStart[4] = true;
               L1h2 = getKey;
               char progEprom = getKey;
               eeprom_write_block(&progEprom,5,1);
               return;
            };
           if(L1timeStart[4] != false && L1timeStart[5] == false) {
               if(L1h2 == '2' && (getKey == '0' || getKey == '1' || getKey == '2' || getKey == '3' || getKey == '4')){
                  L1timeStart[5] = true;
                  L1h3 = getKey;
                  char progEprom = getKey;
                  eeprom_write_block(&progEprom,6,1);
                  return;
                };
                if(L1h2 == '0' || L1h2 == '1') {
                  L1timeStart[5] = true;
                  L1h3 = getKey;
                  char progEprom = getKey;
                  eeprom_write_block(&progEprom,6,1);
                  return;
                  }; 
            };
           if(L1timeStart[5] != false &&  L1timeStart[6] == false && (getKey == '0' || getKey == '1' || getKey == '2' || getKey == '3' || getKey == '4' || getKey == '5' )) {
              L1timeStart[6] = true;
              L1m2 = getKey;
              char progEprom = getKey;
              eeprom_write_block(&progEprom,7,1);
              return;
            };
           if(L1timeStart[6] != false && L1timeStart[7] == false) {
              L1timeStart[7] = true;
              L1m3 = getKey;
              char progEprom = getKey;
              eeprom_write_block(&progEprom,8,1);
              return;
            };            
      };


      

      if(key == 'D' && program == '2' && getKey != 'A' && getKey != 'B' && getKey != 'C' && getKey != 'D' && getKey != '*' && getKey != '#') {
          if(L2timeStart[0] == false && (getKey == '0' || getKey == '1' || getKey == '2')) {
               L2timeStart[0] = true;
               L2h0 = getKey;
               char progEprom = getKey;
               eeprom_write_block(&progEprom,9,1);
               return;
            };
            
          if(L2timeStart[1] == false && L2timeStart[0] != false) {
               if(L2h0 == '2' && (getKey == '0' || getKey == '1' || getKey == '2' || getKey == '3' || getKey == '4')){
                  L2timeStart[1] = true;
                  L2h1 = getKey;
                  char progEprom = getKey;
                  eeprom_write_block(&progEprom,10,1);
                  return;
                };
                if(L2h0 == '0' || L2h0 == '1') {
                  L2timeStart[1] = true;
                  L2h1 = getKey;
                  char progEprom = getKey;
                  eeprom_write_block(&progEprom,10,1);
                  return;
                }; 
            };
          if(L2timeStart[1] != false && L2timeStart[2] == false && (getKey == '0' || getKey == '1' || getKey == '2' || getKey == '3' || getKey == '4' || getKey == '5' )) {
              L2timeStart[2] = true;
              L2m0 = getKey;
              char progEprom = getKey;
              eeprom_write_block(&progEprom,11,1);
              return;
            };
          if(L2timeStart[2] != false && L2timeStart[3] == false) {
              L2timeStart[3] = true;
              L2m1 = getKey;
              char progEprom = getKey;
              eeprom_write_block(&progEprom,12,1);
              return;
            };
          if(L2timeStart[3] != false && L2timeStart[4] == false && (getKey == '0' || getKey == '1' || getKey == '2')) {
               L2timeStart[4] = true;
               L2h2 = getKey;
               char progEprom = getKey;
               eeprom_write_block(&progEprom,13,1);
               return;
            };
           if(L2timeStart[4] != false && L2timeStart[5] == false) {
               if(L2h2 == '2' && (getKey == '0' || getKey == '1' || getKey == '2' || getKey == '3')){
                  L2timeStart[5] = true;
                  L2h3 = getKey;
                  char progEprom = getKey;
                  eeprom_write_block(&progEprom,14,1);
                  return;
                };
                if(L2h2 == '0' || L2h2 == '1') {
                  L2timeStart[5] = true;
                  L2h3 = getKey;
                  char progEprom = getKey;
                  eeprom_write_block(&progEprom,14,1);
                  return;
                  }; 
            };
           if(L2timeStart[5] != false && L2timeStart[6] == false && (getKey == '0' || getKey == '1' || getKey == '2' || getKey == '3' || getKey == '4' || getKey == '5' )) {
              L2timeStart[6] = true;
              L2m2 = getKey;
              char progEprom = getKey;
              eeprom_write_block(&progEprom,15,1);
              return;
            };
           if(L2timeStart[6] != false && L2timeStart[7] == false) {
              L2timeStart[7] = true;
              L2m3 = getKey;
              char progEprom = getKey;
              eeprom_write_block(&progEprom,16,1);
              return;
            };            
      };
      
    if(key == '*' && (getKey != '*' || getKey != '#' || getKey != 'A' || getKey != 'B' || getKey != 'C' || getKey != 'D')){
      if(timeArray[0] == false && (getKey == '1' || getKey == '0' || getKey == '2')) {
        h0 = String(getKey);
        timeArray[0] = true;
        return;
        };
      if(timeArray[0] == true && timeArray[1] == false && (getKey != '*' || getKey != '#' || getKey != 'A' || getKey != 'B' || getKey != 'C' || getKey != 'D')){
        if(h0 != "2" ){
          h1 = String(getKey);
          timeArray[1] = true;
          return;
          } else {
            if(getKey == '0' || getKey == '1' || getKey == '2' || getKey == '3'){
              h1 = String(getKey);
              timeArray[1] = true;
              return;
              } else {return;};
            };
        };
       if(timeArray[1] == true && timeArray[2] == false && (getKey == '1' || getKey == '0' || getKey == '2' || getKey == '3' || getKey == '4' || getKey == '5')) {
        m0 = String(getKey);
        timeArray[2] = true;
        return;
        };
       if(timeArray[2] == true && timeArray[3] == false && (getKey != '*' || getKey != '#' || getKey != 'A' || getKey != 'B' || getKey != 'C' || getKey != 'D')) {
        m1 = String(getKey);
        timeArray[3] = true;
        return;
        };
      };
      if(key == '*' && getKey == '*') {
        reset();
        };
      if(key == '*' && timeArray[3] == true && getKey == '#') {
        setTimeCore();
        };
       if(key == 'C' && getKey == '1' && program == '1') {
        if(coil1 == false){
          coil1 = true;
          } else {
            coil1 = false;
            };
        };
      if(key == 'C' && getKey == '2' && program == '1') {
        if(coil2 == false){
          coil2 = true;
          } else {
            coil2 = false;
            };
        };
      if(key == 'C' && program == '3' && getKey != '*' && getKey != '#' && getKey != 'A' && getKey != 'B' && getKey != 'C' && getKey != 'D'){
        if(tempArray[0] == false){
          l0 = getKey;
          tempArray[0] = true;
          return;  
          };
          
          if(tempArray[0] == true){
            l1 = getKey;
            tempArray[1] = true;
            return;
            };
        };
       if(key == 'C' && program == '3' && getKey == 'C'){
        tempAdjustingReset();
        };
       if(key == 'C' && program == '3' && getKey == '#' && tempArray[1] == true){
        tempSet();
        tempAdjustingReset();
       };
  };
  
  switch(key) 
   {
   case 'A':
      showTimeAndTemperature();
      break;
   case 'B':
       chooseProgram();
       break;
   case 'C':
       adjusting();
       break;
   case 'D':
       adjusting2();
       break;
   case '*':
       setTimeLcd();
       break;
   default:
       break;
   };
};