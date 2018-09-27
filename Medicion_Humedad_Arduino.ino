//Codigo By. Ivan Gustin
#include <SPI.h>
#include <SD.h>

int sensorPin = A0;    // select the input pin for the potentiometer
int sensor = 0;  // variable to store the value coming from the sensor
int cont = 0;
unsigned long tiempo;
unsigned long tmuestra = 1000000;
const int chipSelect = 10;


void setup() {
  pinMode(sensorPin, INPUT);

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(10, OUTPUT);

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
}

void loop () {
  float humedad;
  int cont=0;
  tiempo = millis();
  float analoga1=0;  
  // make a string for assembling the data to log:
  String dataString = "";
  // read three sensors and append to the string:
  for (int analogPin = 0; analogPin < 1; analogPin++) {
    cont=cont+1;

//    Serial.println(sensor);
//    float voltage = sensor * 5;
//    voltage /= 1024.0;
//    float humedad = (voltage) * 0.34 - 0.14814815;
    float sensor = analogRead(analogPin);
    float voltage = 0.001918*(sensor*sensor) + 5.172*sensor ; 
    humedad = 0.000029*(voltage*voltage) + 0.0159336537*voltage - 7;

    if (humedad < 0)
    {
      dataString += String(humedad * 0);
    }
    else
    {
      dataString += String(humedad );
    }

//    if (analogPin < 2) {
//      dataString += ",";
//    }
  }
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
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
  delay(300000);
}



