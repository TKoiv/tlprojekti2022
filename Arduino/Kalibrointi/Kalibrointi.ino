// Kiihtyvyysanturin kytkentänapojen määrittelyt:
//const int analogInPinX = A0;  // X-kanavan kytkentänapa
//const int analogInPinY = A1;  // Y-kanavan kytkentänapa
//const int analogInPinZ = A2;  // Z-kanavan kytkentänapa

const int VccPin2        = A0;  // Käyttöjännite
const int analogInPinX   = A1;  // x-kanavan mittaus
const int analogInPinY   = A2;  // y-kanava
const int analogInPinZ   = A3;  // z-kanava
const int GNDPin2        = A4;  // laitteen maa-napa

int sensorValueX = 0;        // X-kiihtyvyyttä vastaava sensoriarvo 10 bittisessä järjestelmässä (0 - 1023)
int sensorValueY = 0;        // Y-kiihtyvyyttä vastaava sensoriarvo 10 bittisessä järjestelmässä (0 - 1023)
int sensorValueZ = 0;        // Z-kiihtyvyyttä vastaava sensoriarvo 10 bittisessä järjestelmässä (0 - 1023)
unsigned long aika = 0;      // aikaleima, joka luetaan millisekunteina. Int-tyyppinen määrittely tuottaisi nopean bitti-ylivuodon.
int sisaanmeno = 0;          // testi ollaanko menossa sisään ohjelmaan ensimmäistä kertaa


void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(19200); 

    // Kiihtvyys-anturin napojen määrittely:
  pinMode(VccPin2, OUTPUT);     // Kiihtyvyysanturin käyttöjännite Vcc
  pinMode(GNDPin2, OUTPUT);     // Kiihtyvyysanturin GND

  // Asetetaan syöttöjännite (5V UNO-BOARDILLA, 3.3V Genuino 101:llä) ja maa-arvot (0V):
  digitalWrite(VccPin2, HIGH);
  delayMicroseconds(2);
  digitalWrite(GNDPin2, LOW);
  delayMicroseconds(2);

    while (Serial.available() != 0)
  {
    // Odotellaan että yhteys käynnistyy jos tässä sattuu olemaan viivettä. 0 tarkoittaa että yhteys on.
  }
}

void loop() {
  
  if (sisaanmeno == 0)
  {
     delay(500);                   // Annetaan aikaa käynnistelylle
     Serial.print("Time(ms) ");   // Tulostetaan aluksi tiedot mitä ollaan tulostamassa
     Serial.print("Sens_x");
     Serial.print("\t");
     Serial.print("Sens_y");
     Serial.print("\t");
     Serial.println("Sens_z"); // Tulostus ja rivinvaihto
     sisaanmeno = 1;               // Vaihdetaan tunnistetieto niin tänne ei enää tulla
  }
  
  // Luetaan kanavien antamat sensoriarvot ja aikaleima
  sensorValueX = analogRead(analogInPinX);      
  sensorValueY = analogRead(analogInPinY);  
  sensorValueZ = analogRead(analogInPinZ);  
  aika = millis();         

  // print the results to the serial monitor:                    
  Serial.print(aika);      
  Serial.print("\t ; ");      
  Serial.print(sensorValueX);      
  Serial.print("\t ; ");  
  Serial.print(sensorValueY);      
  Serial.print("\t ; ");  
  Serial.println(sensorValueZ);        

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(100);                         // Nyt ei vielä pyritä kovin nopeaan mittaukseen kun vasta kalibroidaan... 100ms viive.                
}
