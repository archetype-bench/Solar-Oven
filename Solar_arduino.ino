/* SOLAR OVEN CODE
    Date:29/3/2020  Update #1:  Adding Sensors     :completed
                                Bluetooth Config   :completed    note: keep delay rate of arduino code less than timer refresh rate of app
                                SD Card            :completed
                                RTC module connect :completed


*/

/* header files */
#include <SPI.h>      //SD card
#include <SD.h>       //SD card

#include <Wire.h>     //RTC
#include <RTClib.h>


RTC_DS3231 rtc;
DateTime now;

int prim=0,aux1=0,aux2=0,aux3=0; //sensor variables declaration 
const int chipSelect = 4;        //SD.CS pin on D4
int count=0;




void setup() {  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  
  Serial.print("Initializing SD card...");                    //SD card Check

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");

  if (rtc.begin())
    Serial.println("RTC connected.");  
  else if (! rtc.begin()) 
  {
    Serial.println("Couldn't find RTC Module");
    while (1);
  }

  if (rtc.lostPower()) 
  {
    Serial.println("RTC lost power, lets set the time!");
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    //rtc.adjust(DateTime(2020, 1, 28, 21,14 , 0));
  }
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}
  



void loop() {  // put your main code here, to run repeatedly:
        
        /* Read values from sensors A0 to A3*/
        prim=(5.0 * analogRead(A0) *100.0)/1024;
        aux1=(5.0 * analogRead(A1) *100.0)/1024;
        aux2=(5.0 * analogRead(A2) *100.0)/1024;
        aux3=(5.0 * analogRead(A3) *100.0)/1024;

        
        Serial.println(String(prim)+"|"+String(aux1)+"|"+String(aux2)+"|"+String(aux3)+"|");   //sending via bluetooth and serial monitor
        
        //------------------------- bluetooth upload completed ... sd card storage started -----------------------------------------

    if(count>=4)               //stores valuesa fter 20secs... increase count to suit time ... 1 = 5sec , 4= 20sec
    {    
          
          
         String dataString = "";


         now = rtc.now();


         dataString = String(now.day());
         dataString += "-";
         dataString += String(now.month());
         dataString += "-";
         dataString += String(now.year());
         dataString += ",";
         
         dataString += String(now.hour());
         dataString += ":";
         dataString += String(now.minute());
         dataString += ":";
         dataString += String(now.second());
         dataString += ",";
        // read three sensors and append to the string:
  for (int analogPin = 0; analogPin < 4; analogPin++) {
    int sensor = (5.0 * analogRead(analogPin)*100.0)/1024;
    dataString += String(sensor);
    if (analogPin < 3) {
      dataString += ",";
    }
  }

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
    count=0;
        // --------------------------- SD card save completed ----------------------------------------
    }    


      
        delay(5000);
        count++;
        
}
