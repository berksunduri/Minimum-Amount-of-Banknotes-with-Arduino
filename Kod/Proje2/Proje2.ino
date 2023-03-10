#include <SPI.h>
#include <SD.h>
#include <ezButton.h>

File myFile;


const int ledRed = 2;
const int ledGreen = 3;


ezButton button1(9);
ezButton button2(8);
ezButton button3(7);
ezButton button4(6);
ezButton button5(5);
ezButton button6(4);
ezButton button7(A0);


int paraMiktar5 = 0;
int paraMiktar10 = 0;
int paraMiktar20 = 0;
int paraMiktar50 = 0;
int paraMiktar100 = 0;
int atilanPara, harcananPara, flagPara;
int para5 = 5, para10 = 10, para20 = 20, para50 = 50, para100 = 100;

int hizmetFiyat[4] = {15, 10, 5, 50};
char *HizmetAd[] = {"Kopukleme", "Yikama", "Kurulama", "Cilalama"};
int kopuklemeAdet = 0, flagKopukleme;
int yikamaAdet = 0, flagYikama;
int kurulamaAdet = 0, flagKurulama;
int cilalamaAdet = 0, flagCilalama;

bool hasRun = false;
bool islem = false;


void paraMenu()
{
  Serial.println(F("1. 5TL Yukle"));
  Serial.println(F("2. 10TL Yukle"));
  Serial.println(F("3. 20TL Yukle"));
  Serial.println(F("4. 50TL Yukle"));
  Serial.println(F("5. 100TL Yukle"));
  Serial.println(F("6. Hizmet Menusune Gec"));
}
void hizmetMenu()
{
  Serial.println(F("1.Kopukleme"));
  Serial.println(F("2.Yikama"));
  Serial.println(F("3.Kurulama"));
  Serial.println(F("4.Cilalama"));
  Serial.println(F("5.Reset"));
  Serial.println(F("7.Bitir"));
  
}


void setup() {

  Serial.begin(9600);
  Serial.println(F("SD Card okunuyor..."));
  if (!SD.begin())
  {
    Serial.println(F("SD Card okunamadi!"));
    while (1);
  }

  myFile = SD.open("test.txt", FILE_READ);
  if (myFile)
  {
    while (myFile.available())
    {
      paraMiktar5 = myFile.parseInt();
      paraMiktar10 = myFile.parseInt();
      paraMiktar20 = myFile.parseInt();
      paraMiktar50 = myFile.parseInt();
      paraMiktar100 = myFile.parseInt();

      kopuklemeAdet = myFile.parseInt();
      yikamaAdet = myFile.parseInt();
      kurulamaAdet = myFile.parseInt();
      cilalamaAdet = myFile.parseInt();
    }
    myFile.close();
  }
  Serial.println();
  /*Serial.println((String)"5TL Adedi:" + paraMiktar5);
  Serial.println((String)"10TL Adedi:" + paraMiktar10);
  Serial.println((String)"20TL Adedi:" + paraMiktar20);
  Serial.println((String)"50TL Adedi:" + paraMiktar50);
  Serial.println((String)"100TL Adedi:" + paraMiktar100);

  Serial.println((String)"Kalan Kopukleme:" + kopuklemeAdet);
  Serial.println((String)"Kalan Yikama:" + yikamaAdet);
  Serial.println((String)"Kalan Kurulama:" + kurulamaAdet);
  Serial.println((String)"Kalan Cilalama:" + cilalamaAdet);*/
  flagKopukleme = kopuklemeAdet;
  flagYikama = yikamaAdet;
  flagKurulama = kurulamaAdet;
  flagCilalama = cilalamaAdet;
  button1.setDebounceTime(50);
  button2.setDebounceTime(50);
  button3.setDebounceTime(50);
  button4.setDebounceTime(50);
  button5.setDebounceTime(50);
  button6.setDebounceTime(50);
  button7.setDebounceTime(50);

  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);

  paraMenu();

}

void loop() {


  button1.loop();
  button2.loop();
  button3.loop();
  button4.loop();
  button5.loop();
  button6.loop();
  button7.loop();

  if (islem == false)
  {
    if (button1.isPressed())
    {
      atilanPara += para5;
      paraMiktar5++;
      digitalWrite(ledGreen, HIGH);
      Serial.println(F("5TL Yuklendi"));
      Serial.println((String)"Yuklenen Miktar:" + atilanPara);
      delay(500);
      digitalWrite(ledGreen, LOW);
    }

    if (button2.isPressed())
    {
      digitalWrite(ledGreen, HIGH);
      atilanPara += para10;
      paraMiktar10++;
      Serial.println(F("10TL Yuklendi"));
      Serial.println((String)"Yuklenen Miktar:" + atilanPara);
      delay(500);
      digitalWrite(ledGreen, LOW);
    }

    if (button3.isPressed())
    {
      digitalWrite(ledGreen, HIGH);
      atilanPara += para20;
      paraMiktar20++;
      Serial.println(F("20TL Yuklendi"));
      Serial.println((String)"Yuklenen Miktar:" + atilanPara);
      delay(500);
      digitalWrite(ledGreen, LOW);
    }

    if (button4.isPressed())
    {
      digitalWrite(ledGreen, HIGH);
      atilanPara += para50;
      paraMiktar50++;
      Serial.println(F("50TL Yuklendi"));
      Serial.println((String)"Yuklenen Miktar:" + atilanPara);
      delay(500);
      digitalWrite(ledGreen, LOW);
    }

    if (button5.isPressed())
    {
      digitalWrite(ledGreen, HIGH);
      atilanPara += para100;
      paraMiktar100++;
      Serial.println(F("100TL Yuklendi"));
      Serial.println((String)"Yuklenen Miktar:" + atilanPara);
      delay(500);
      digitalWrite(ledGreen, LOW);
    }

    if (button6.isPressed())
    {
      Serial.println();
      if (atilanPara == 0)
      {
        Serial.println(F("Para atmadiniz."));
      }
      else
      {
        Serial.println(F("Hizmet Menusune Geciliyor..."));
        flagPara = atilanPara;
        
        SD.remove("test.txt");
      myFile = SD.open("test.txt", FILE_WRITE);
      if (myFile)
      {
        char text[100];
        sprintf(text, "%d,%d,%d,%d,%d %d,%d,%d,%d", paraMiktar5, paraMiktar10, paraMiktar20, paraMiktar50, paraMiktar100, kopuklemeAdet, yikamaAdet, kurulamaAdet, cilalamaAdet);
        myFile.print(text);
      }
      myFile.close();
      
        islem = true;
        delay(200);
      }
    }
  }

  if (islem == true)
  {
    if (hasRun == false)
    {
      hizmetMenu();
      Serial.println((String)"Yuklenen Miktar:" + atilanPara);
      hasRun = true;
    }
    
    if (button1.isPressed())
    {
      Serial.println(F("Kopukleme islemini sectiniz"));

      Serial.println(F("Ucret 15TL"));
      atilanPara -= hizmetFiyat[0];
      harcananPara += hizmetFiyat[0];
      kopuklemeAdet--;
      delay(200);
      Serial.println((String)"Kalan Miktar:" + atilanPara);
      
      SD.remove("test.txt");
      myFile = SD.open("test.txt", FILE_WRITE);
      if (myFile)
      {
        char text[100];
        sprintf(text, "%d,%d,%d,%d,%d %d,%d,%d,%d", paraMiktar5, paraMiktar10, paraMiktar20, paraMiktar50, paraMiktar100, kopuklemeAdet, yikamaAdet, kurulamaAdet, cilalamaAdet);
        myFile.print(text);
      }
      myFile.close();
    }
    
    if (button2.isPressed())
    {
      Serial.println(F("Yikama islemini sectiniz"));

      Serial.println(F("Ucret 10TL"));
      atilanPara -= hizmetFiyat[1];
      harcananPara += hizmetFiyat[1];
      yikamaAdet--;
      delay(200);
      Serial.println((String)"Kalan Miktar:" + atilanPara);
      
      SD.remove("test.txt");
      myFile = SD.open("test.txt", FILE_WRITE);
      if (myFile)
      {
        char text[100];
        sprintf(text, "%d,%d,%d,%d,%d %d,%d,%d,%d", paraMiktar5, paraMiktar10, paraMiktar20, paraMiktar50, paraMiktar100, kopuklemeAdet, yikamaAdet, kurulamaAdet, cilalamaAdet);
        myFile.print(text);
      }
      myFile.close();
    }
    
    if (button3.isPressed())
    {
      Serial.println(F("Kurulama islemini sectiniz"));

      Serial.println(F("Ucret 5TL"));
      atilanPara -= hizmetFiyat[2];
      harcananPara += hizmetFiyat[2];
      kurulamaAdet--;
      delay(200);
      Serial.println((String)"Kalan Miktar:" + atilanPara);
      Serial.println((String)"Kurulama:" + kurulamaAdet);
      
      SD.remove("test.txt");
      myFile = SD.open("test.txt", FILE_WRITE);
      if (myFile)
      {
        char text[100];
        sprintf(text, "%d,%d,%d,%d,%d %d,%d,%d,%d", paraMiktar5, paraMiktar10, paraMiktar20, paraMiktar50, paraMiktar100, kopuklemeAdet, yikamaAdet, kurulamaAdet, cilalamaAdet);
        myFile.print(text);
      }
      myFile.close();
    }
    
    if (button4.isPressed())
    {
      Serial.println(F("Cilalama islemini sectiniz"));

      Serial.println(F("Ucret 50TL"));
      atilanPara -= hizmetFiyat[3];
      harcananPara += hizmetFiyat[3];
      cilalamaAdet--;
      delay(200);
      Serial.println((String)"Kalan Miktar:" + atilanPara);
      
      SD.remove("test.txt");
      myFile = SD.open("test.txt", FILE_WRITE);
      if (myFile)
      {
        char text[100];
        sprintf(text, "%d,%d,%d,%d,%d %d,%d,%d,%d", paraMiktar5, paraMiktar10, paraMiktar20, paraMiktar50, paraMiktar100, kopuklemeAdet, yikamaAdet, kurulamaAdet, cilalamaAdet);
        myFile.print(text);
      }
      myFile.close();
    }
    
    if (button5.isPressed())
    {
      Serial.println(F("Reset Islemini sectiniz"));
      Serial.println(F("Yaptiginiz islemler resetlendi"));
      atilanPara = flagPara;
      kopuklemeAdet = flagKopukleme;
      yikamaAdet = flagYikama;
      kurulamaAdet = flagKurulama;
      cilalamaAdet = flagCilalama;
      harcananPara = 0;
      hizmetMenu();
      
      SD.remove("test.txt");
      myFile = SD.open("test.txt", FILE_WRITE);
      if (myFile)
      {
        char text[100];
        sprintf(text, "%d,%d,%d,%d,%d %d,%d,%d,%d", paraMiktar5, paraMiktar10, paraMiktar20, paraMiktar50, paraMiktar100, kopuklemeAdet, yikamaAdet, kurulamaAdet, cilalamaAdet);
        myFile.print(text);
      }
      myFile.close();
    }
    if (button7.isPressed())
    {
      int randNumber = random(4);
      if (randNumber == 2)
      {
        Serial.println();
        Serial.println(F("Paraniz sikisti."));
        digitalWrite(ledRed, HIGH);
        delay(1000);
        digitalWrite(ledRed, LOW);
        Serial.println();
      }
      else
      {
        Serial.println((String)"Harcadiginiz Para:" + harcananPara);
        int amt = flagPara - harcananPara;
        int total;
        Serial.println();
        Serial.println();
        Serial.println((String)"Atilan Para:" + flagPara + " Harcanan Para:" + harcananPara + " Change:" + amt);

        total = (int)amt / 100;
        if (paraMiktar100 >= total)
        {
          paraMiktar100--;
          amt -= (total * 100);
          Serial.println((String)total + "Tane 100luk");
        }

        total = (int)amt / 50;
        if (paraMiktar50 >= total)
        {
          paraMiktar50--;
          amt -= (total * 50);
          Serial.println((String)total + "Tane 50lik");
        }

        total = (int)amt / 20;
        if (paraMiktar20 >= total)
        {
          paraMiktar20--;
          amt -= (total * 20);
          Serial.println((String)total + "Tane 20lik");
        }

        total = (int)amt / 10;
        if (paraMiktar10 >= total)
        {
          paraMiktar10--;
          amt -= (total * 10);
          Serial.println((String)total + "Tane 10luk");
        }

        total = (int)amt / 5;
        if (paraMiktar5 >= total)
        {
          paraMiktar5--;
          amt -= (total * 5);
          Serial.println((String)total + "Tane 5lik");
        }
        else
        {
          Serial.println(F("Kasada yeterli para yok"));
        }
        
        SD.remove("test.txt");
        myFile = SD.open("test.txt", FILE_WRITE);
        if (myFile)
        {
          char text[100];
          sprintf(text, "%d,%d,%d,%d,%d %d,%d,%d,%d", paraMiktar5, paraMiktar10, paraMiktar20, paraMiktar50, paraMiktar100, kopuklemeAdet, yikamaAdet, kurulamaAdet, cilalamaAdet);
          myFile.print(text);

        }
        myFile.close();
      }
    }
    /*
   

      SD.remove("test.txt");
      myFile = SD.open("test.txt", FILE_WRITE);
      if (myFile)
      {
        char text[100];
        sprintf(text, "%d,%d,%d,%d,%d %d,%d,%d,%d", paraMiktar5, paraMiktar10, paraMiktar20, paraMiktar50, paraMiktar100, kopuklemeAdet, yikamaAdet, kurulamaAdet, cilalamaAdet);
        myFile.print(text);
        Serial.println(F("Dosya tekrar yazildi"));
      }
      myFile.close();
      */
  }

}
