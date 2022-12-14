# Tietoliikenteen sovellusprojekti 2022 / Tauno Koivisto

## Tavoitteet​

Tavoitteena oli koodata Arduinolle client, joka mittaa kiihtyvyysanturin dataa ja lähettää sen 433Mhz radiorajapinnan yli IoT-reitittimelle (Rasberry pi) tallennettavaksi MySQL tietokantaan. Tämän jälkeen Pythonilla koodattiin ohjelma joka hakee datan tietokannasta HTTP Api:n kautta ja välittää sen K-Means algoritmille. K-Means algoritmi tämän jälkeen luetteloi datan kuuteen eri joukkoon. Näiden pisteiden perusteella Arduinolle tehtiin oma K-Means malli, joka vertaa anturidataa malliin ja kertoo anturin asennon.

![image](https://user-images.githubusercontent.com/93557178/207564651-7f8b26a0-7168-423b-8675-2191ff46dd35.png)

## Metodit​

Projektissa oli käytössä ohjelmointikielinä Python ja C++ Mikrokontrollerina käytössä oli Arduino Uno yhdessä  kiihtyvyysanturi(GY61), radiolähettin(WS-433) ja vastaan-ottimen(RWS-371) kanssa. Versionhallinnassa käytössä oli Git ja sen jatkeena GitHub edistymisen tarkkailuun ja tehtyjen töiden tallentamiseen.​

## 3D Data ennen luokittelua (Valmiilla datalla neljällä pisteellä)
![image](https://user-images.githubusercontent.com/93557178/203951259-a6bc63ca-6363-4339-9c3c-35d18c3cb0cf.png)

## Arvatut datapisteet ensin ja iteroidut datapisteet jälkimmäisessä (Omalla datalla kuudella pisteellä)
![kMeans6_arvottu](https://user-images.githubusercontent.com/93557178/205661188-0e8c70c1-c5c7-4e01-ab23-3cb629390201.png)
![kMeans6_iteroitu](https://user-images.githubusercontent.com/93557178/205661243-d2391e5d-0a9d-4f7a-9998-90a67437cb40.png)

## Confusion matrixin tulos
![image](https://user-images.githubusercontent.com/93557178/207534017-e5046e42-c242-4fb4-b329-62eecdb4fa36.png)

## Lopputulos

Mitatun datan siirto onnistui radio-rajapinnan yli tietokantaan. Tästä datasta K-means algoritmilla tehty malli implementoitiin Arduinoon, joka osasi onnistuneesti luokitella anturidatan perusteella asennot oikein.​

## Johtopäätökset

Projekti oli haastava, mutta opettava, koska K-Means –algoritmi tehtiin itse alusta alkaen. Ennen projektia opiskeltu teoreettinen osaaminen vahvistui projektin aikana käytännön osaamisella, ja ymmärrys koneoppimisesta syventyi.​



