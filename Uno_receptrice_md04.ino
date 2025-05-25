#include <Arduino.h>
#include <Wire.h>


#define ADDRESS             0x58                    // Address of MD04
#define SOFTREG             0x07                    // Byte to read software
#define CMDBYTE             0x00                    // Command byte
#define SPEEDBYTE           0x02                    // Byte to write to speed register
#define TEMPREG             0x04                    // Byte to read temperature
#define CURRENTREG          0x05          

int k;

//Sens du courant
byte direct = 2; 

//Courant
float i_ini=1.90;
int i_mot = 190;
float i=i_ini;


//Hauteurs
float h_0=75;
float h;


void setup() {
  Serial.begin(115200);
  Wire.begin();                                     // Start I2C connection
  delay(100);
  Serial.println(getData(SOFTREG));
  delay(1000);
}

void loop() {
//char k[5] ;
  if (Serial.available()){
    //char com = Serial.read();
    //char commande[20] = "Hello";
    char buffer[20]="";
    k=0;
    while (k<7){
      float com = Serial.read();
      //Serial.println(com);
      
      int len = strlen(buffer);
      buffer[len] = com;
      //Serial.println(buffer);
      k=k+1;
      
    }
    
    //float h = float(buffer);
    //Serial.println(buffer);
    h=atof(buffer);
    Serial.print("hauteur : ");
    Serial.println(h);
    if (abs(h-h_0)>2){ //incertitude de mesure du capteur et micro vibrations
    calcul_intensite();
    i_mot=i*100;
    i_mot=constrain(i*100,150,250);
  }
  sendData(SPEEDBYTE, i_mot);             // Sets speed to i
  sendData(CMDBYTE, direct);          // Sets motor to direct, a value of 1 runs the motor forward and 2 runs backward
  showData(direct,i_mot);
    delay(210);
    }
}

byte getData(byte reg){                 // function for getting data from MD03
  Wire.beginTransmission(ADDRESS);
  Wire.write(reg);
  Wire.endTransmission();
  
  Wire.requestFrom(ADDRESS, 1);         // Requests byte from MD03
  while(Wire.available() < 1);          // Waits for byte to become available
  byte data = Wire.read();

  return(data);
}

void sendData(byte reg, byte val){      // Function for sending data to MD03
  Wire.beginTransmission(ADDRESS);      // Send data to MD03
    Wire.write(reg);                    // Command like Direction, Speed
    Wire.write(val);                    // Value for the command
  Wire.endTransmission();
}

void showData(byte valdirection, byte valSpeed) {
    Serial.print("Direction: ");
    Serial.print(valdirection);         // Prints current direction (1 or 2)
    Serial.print(" - Speed: ");
    Serial.print(valSpeed);             // Prints current Speed (0-250) tot Serial
   
    //byte current = getData(CURRENTREG); // Get current value (186 = 20 Amp) to Serial
    //delay(10);
    //Serial.print(" - Current: ");       
    //Serial.print(current);              
    
    //byte temp = getData(TEMPREG);       // Get surface temperature of the PCB in degrees centigrade.
    //delay(10);
    //Serial.print(" - Temperature: ");
    //Serial.print(temp);                
    
    Serial.println(".");                // Point at the end of the line and an Enter
}

void calcul_intensite()
{
  i=(h_0/h)*i;
  i=constrain(i,1.5,2.5);
  Serial.print("l'intensité est : ");
  Serial.print(i);
  Serial.println(" A");
}

void correction() {

}