//Librerias para el sensor DS18B20
#include <OneWire.h>
#include <DallasTemperature.h>

//Libreria para la pantalla lcd
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

//Se define el pin para el sensor DS18B20
const int PINSENSOR = 3;

//Se definen los dos objetos para el sensor
OneWire oneWireObjeto(PINSENSOR);
DallasTemperature sensor(&oneWireObjeto);

//Se define la pantalla
LiquidCrystal_I2C lcd (0x27, 20, 4);

//Variables para la temperatura
float temp;
const int TEMP_IDEAL = 56;

//RGB
const int RED = 9;
const int GREEN = 10;
const int BLUE = 11;

//Buzzer
const int BUZZER = 6;

//Contador
int contador = 0;

void setup(void)
{
  //Se inicia el sensor
  sensor.begin();

  //Se inicia la pantalla
  lcd.init();
  lcd.clear();
  lcd.backlight();

  //Se inicia el RGB
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  
  //Se inicia el buzzer
  pinMode(BUZZER, OUTPUT);
}

void loop(void)
{
  sensor.requestTemperatures(); //Se lee la temperatura
  temp = sensor.getTempCByIndex(0); //Se obtiene la temperatura en ºC
  showHeader();
  checkTemperatureAndShowInfo(temp);

  while(temp <= TEMP_IDEAL){
    if(contador == 0){
      marioLevelCompleteTheme();
    }
    contador++;
    flashingLight();
  }
  contador = 0;
  delay(1000);
}

void checkTemperatureAndShowInfo(float temperature){
  if(temperature > 76){
    showInfo(20, 3, " Cuidado que quema  ", temperature);
  } else if(temperature > 72){
    showInfo(40, 6, " Esta muy caliente  ", temperature);
  } else if(temperature > 68){
    showInfo(50, 10, "   Sigue caliente   ", temperature);
  } else if(temperature > 60){
    showInfo(60, 13, "Se empieza a enfriar", temperature);
  } else if(temperature > TEMP_IDEAL){
    showInfo(80, 16, "   Ya falta poco    ", temperature);
  } else{
    showInfo(100, 20, " Infusion lista!!!  ", temperature);
  }
}

void showInfo(int percent, int position, String message, float temperature){
  //Print second row
    lcd.setCursor(0, 1);
    lcd.print("   ");
    lcd.print(percent);
    lcd.print("% completado");
  //Print third row
    lcd.setCursor(0, 2);
    for(int i = 0; i < position; i++){
      lcd.write(0xFF); //Imprime todos los puntos de la cuadricula
    }
  //Print fourth row
    lcd.setCursor(0,3);
    lcd.print(message);
  //Select led color
    showRgb(temperature);
}

void showHeader(){
  lcd.setCursor(0, 0);
  lcd.print("Temperatura = ");
  lcd.print(sensor.getTempCByIndex(0));
  lcd.print(char(223)); //Para imprimir el signo de lo grados
}

void ledColor(int redValue, int greenValue, int blueValue){
  analogWrite(RED, redValue);
  analogWrite(GREEN, greenValue);
  analogWrite(BLUE, blueValue);
}

void showRgb(float temperature){
  if(temperature > 68){
    ledColor(255, 0, 0);
  } else if(temperature > 56){
    ledColor(0, 0, 255);
  } else {
    ledColor(0, 255, 0);
  }
}

void flashingLight(){
  ledColor(0, 255, 0);
  delay(500);
  ledColor(0, 0, 0);
  delay(500);
}

void marioLevelCompleteTheme() {
  //Clave de Fa
  int Sol_FA = 196;
  int LAb_FA = 208;
  int SiB_FA = 233;
  
  //Clave de Do
  int C4 = 262;
  int CS4 = 277;
  int D4 = 294;
  int DS4 = 311;
  int E4 = 330;
  int F4 = 349;
  int G4 = 392;
  int GS4 = 415;
  int AS4 = 466;
  int C5 = 523;
  int D5 = 587;
  int DS5 = 622;
  int E5 = 659;
  int F5 = 698;
  int G5 = 784;
  int GS5 = 831;
  int AS5 = 932;
  int C6 = 1047;
  
  tone(BUZZER, Sol_FA);
  delay(166);
  tone(BUZZER, C4);
  delay(166);
  tone(BUZZER, E4);
  delay(166);
  
  tone(BUZZER, G4);
  delay(166);
  tone(BUZZER, C5);
  delay(166);
  tone(BUZZER, E5);
  delay(166);

  tone(BUZZER, G5);
  delay(500);

  tone(BUZZER, E5);
  delay(500);

  ////////////////////////

  tone(BUZZER, LAb_FA);
  delay(166);
  tone(BUZZER, C4);
  delay(166);
  tone(BUZZER, DS4);
  delay(166);
  
  tone(BUZZER,GS4);
  delay(166);
  tone(BUZZER, C5);
  delay(166);
  tone(BUZZER, DS5);
  delay(166);

  tone(BUZZER, GS5);
  delay(500);

  tone(BUZZER, DS5);
  delay(500);

  /////////////////////////

  tone(BUZZER, SiB_FA);
  delay(166);
  tone(BUZZER, D4);
  delay(166);
  tone(BUZZER, F4);
  delay(166);
  
  tone(BUZZER, AS4);
  delay(166);
  tone(BUZZER, D5);
  delay(166);
  tone(BUZZER, F5);
  delay(166);

  tone(BUZZER, AS5);
  delay(400);
  noTone(BUZZER);
  delay(100);

  tone(BUZZER, AS5);
  delay(120);
  noTone(BUZZER);
  delay(46);
  tone(BUZZER, AS5);
  delay(120);
  noTone(BUZZER);
  delay(46);
  tone(BUZZER, AS5);
  delay(120);
  noTone(BUZZER);
  delay(46);

  tone(BUZZER, C6);
  delay(1000);
  noTone(BUZZER);
  delay(1000);
}
