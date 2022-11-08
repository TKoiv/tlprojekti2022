// Kiihtyvyysanturi projekti

const int analogInPinX = A0;                 // X-kanavan kytkentänapa
const int analogInPinY = A1;                 // Y-kanavan kytkentänapa
const int analogInPinZ = A2;                 // Z-kanavan kytkentänapa

int sensorValueX = 0;                        // X-kiihtyvyyttä vastaava sensoriarvo 10 bittisessä järjestelmässä (0 - 1023)
int sensorValueY = 0;                        // Y-kiihtyvyyttä vastaava sensoriarvo 10 bittisessä järjestelmässä (0 - 1023)
int sensorValueZ = 0;                        // Z-kiihtyvyyttä vastaava sensoriarvo 10 bittisessä järjestelmässä (0 - 1023)
unsigned long aika = 0;                      // aikaleima, joka luetaan millisekunteina. Int-tyyppinen määrittely tuottaisi nopean bitti-ylivuodon.
int sisaanmeno = 0;                          // testi ollaanko menossa sisään ohjelmaan ensimmäistä kertaa


float Ax = 0.0;
float Ay = 0.0;
float Az = 0.0;
float A = 0.0;

float AngleX = 0.0;
float AngleY = 0.0;
float AngleZ = 0.0;

float AngleX_2 = 0.0;
float AngleY_2 = 0.0;
float AngleZ_2 = 0.0;


void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
}

void loop() {
  
  if (sisaanmeno == 0)
  {
     delay(500);                             // Annetaan aikaa käynnistelylle
     Serial.print("(ms)");                   // Tulostetaan aluksi tiedot monitoriin otsikoksi.
     Serial.print("\tA_x");
     Serial.print("\tA_y");
     Serial.print("\tA_z");
     Serial.print("\tA");;
     Serial.print("\tAnX"); 
     Serial.print("\tAnX_2");
     Serial.print("\tAnY"); 
     Serial.print("\tAnY_2");
     Serial.print("\tAnZ"); 
     Serial.println("\tAnZ_2");     
     sisaanmeno = 1;                         // Vaihdetaan tunnistetieto niin tulostetaan nämä vain kertaalleen.
  }
  
  sensorValueX = analogRead(analogInPinX);   // Luetaan muuttujiin arvot analogisista sisääntuloista     
  sensorValueY = analogRead(analogInPinY);  
  sensorValueZ = analogRead(analogInPinZ);  

  Ax = 0.1443*sensorValueX-48.617;           // X-akselin kiihtyvyys kaavasta 
  Ay = 0.1453*sensorValueY-48.18;            // Y-akselin kiihtyvyys kaavasta
  Az = 0.1453*sensorValueX-49.073;           // Z-akselin kiihtyvyys kaavasta
  A= sqrt(Ax*Ax+Ay*Ay+Az*Az);                // Kiihtyvyys kaavasta 
  if (A < -9.81){                            // Rajataan kiihtyvyys alueelle -9.81...9.81                         
    A = -9.81 ;
  }
  if (A > 9.81){
    A = 9.81 ;
  }

  AngleX = 1.3235*sensorValueX-446.02;      // X-akselin kulma suhteessa vaakatasoon 
  if (AngleX < 0.0){                        // X-akselin kulma, kun akseli osoittaa alaspäin näyttää muuten -merkkistä lukemaa, mutta tulostetaan se muotoon 0-90 
    AngleX = (AngleX*(-1.0)) ;
  }
  if (AngleX > 90.0){                       // Rajataan X-akselin kulma, että se ei voi olla yli 90 astetta suhteessa vaakatasoon
    AngleX = 90.0 ;
  }
  AngleX_2 = (180.0-AngleX);                // X-akseli vastakkainen kulma saadaan, kun vähennetään 180 asteesta tiedossa oleva kulma
  

  AngleY = 1.2857*sensorValueY-424,29;      // Y-akselin kulma suhteessa vaakatasoon 
  if (AngleY < 0.0){                        // Y-akselin kulma, kun akseli osoittaa alaspäin näyttää muuten -merkkistä lukemaa, mutta tulostetaan se muotoon 0-90 
    AngleY = (AngleY*(-1.0)) ;
  }
  if (AngleY > 90.0){                       // Rajataan Y-akselin kulma, että se ei voi olla yli 90 astetta suhteessa vaakatasoon
    AngleY = 90.0 ;
  }
  AngleY_2 = (180.0-AngleY);                // Y-akseli vastakkainen kulma saadaan, kun vähennetään 180 asteesta tiedossa oleva kulma

  AngleZ = 1.3433*sensorValueZ-454.03;      // Y-akselin kulma suhteessa vaakatasoon 
  if (AngleZ < 0.0){                        // Z-akselin kulma, kun akseli osoittaa alaspäin näyttää muuten -merkkistä lukemaa, mutta tulostetaan se muotoon 0-90 
    AngleZ = (AngleZ*(-1.0)) ;
  }
  if (AngleZ > 90.0){                       // Rajataan Z-akselin kulma, että se ei voi olla yli 90 astetta suhteessa vaakatasoon
    AngleZ = 90.0 ;
  }
  AngleZ_2 = (180.0-AngleZ);                // Z-akseli vastakkainen kulma saadaan, kun vähennetään 180 asteesta tiedossa oleva kulma
  
  aika = millis();         

  
  Serial.print(aika);         // Tulosteaan aika      
  Serial.print("\t;");                     
  Serial.print(Ax);           // Tulostetaan X-akselin kiihtyvyys -9.81...9.81                        
  Serial.print("\t;");  
  Serial.print(Ay);           // Tulostetaan Y-akselin kiihtyvyys -9.81...9.81
  Serial.print("\t;");  
  Serial.print(Az);           // Tulostetaan Z-akselin kiihtyvyys -9.81...9.81
  Serial.print("\t;");
  Serial.print(A);            // Tulostetaan kiihtyvyys -9.81...9.81      
  Serial.print("\t;");
  Serial.print(AngleX);       // Tulostetaan X-akselin kulma suhteessa vaakatasoon (Pienempi kulma)
  Serial.print("\t;");
  Serial.print(AngleX_2);     // Tulostetaan X-akselin kulma suhteessa vaakatasoon (Suurempi kulma)
  Serial.print("\t;");
  Serial.print(AngleY);       // Tulostetaan Y-akselin kulma suhteessa vaakatasoon (Pienempi kulma)
  Serial.print("\t;");
  Serial.print(AngleY_2);     // Tulostetaan Y-akselin kulma suhteessa vaakatasoon (Suurempi kulma)
  Serial.print("\t;");
  Serial.print(AngleZ);       // Tulostetaan Z-akselin kulma suhteessa vaakatasoon (Pienempi kulma)
  Serial.print("\t;");
  Serial.println(AngleZ_2);   // Tulostetaan Z-akselin kulma suhteessa vaakatasoon (Suurempi kulma)
  delay(100);                                       
}
