#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "WiFi.h"
#include "ESPAsyncWebServer.h"

#include "FONCTIONS.h"

// port utilise ESP-32 34(cible3), 35(cible2)



float vcc=3.3;
unsigned long previousMillis;
int nb_tir=0;

const char* ssid="ESP32AP";
const char* password ="devkit1234";
int http_req=0;

#define US 34
#define Us_Cible2 35
#define vcc 3.3
#define led2 2
#define intensite_lum 60

#define PIN 22  // Port de sortie des données de la carte ESP-32
#define nombre_LED 240  //nombre de Led dans les 4m du bandeau lumineux

// Permet d'initialiser une cible qui à 14 Led paramètre définie suite à des test 
int LED=11;
int touch_sensor_connected=0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(nombre_LED, PIN); // Permet d'initialiser l'objet strip de la classe Adafruit_NeoPixel avec les paramères définies
//strip.begin();

AsyncWebServer server(80);

Cible cible1 = Cible(strip);


void setup() {
  Serial.begin(9600);  // Initialisation de la vitesse de transmission de la liaison série
  pinMode(22,OUTPUT);  // Met le port 22 servant pour la transmission des données aux bandeaux lumineux en sortie
  strip.begin();
  //strip.begin();  // Initialise la liaison neopixel
  //strip.show(); // Initialise tout les pixels à l'état éteint
  previousMillis = millis();
  /*Serial.println("debut");
  strip.setPixelColor(LED, 255, 0, 255); // Permet decontroller led par led la couleur que la led affiche
  strip.show();
  delay(250);
  LED=4;
  strip.setPixelColor(LED, 70, 255, 144);
  delay(250);
  strip.show();
  LED=11;
  strip.setPixelColor(LED, 0, 0, 0);
  delay(250);
  LED=4;
  strip.setPixelColor(LED, 0, 0, 0);
  delay(250);
  strip.show();
  LED=1;
  strip.setPixelColor(LED, 255, 255, 255);
  delay(500);
  Serial.println("fin du setup");
  */
  /*Serial.println("Mode connecte appuyer sur la touche tactile ");
  while ((touch_sensor_connected==0) && (millis()<= 5000))
  {
    if (touch_sensor_connected!=touchRead(T4) && touch_sensor_connected!=1){
      touch_sensor_connected=1;
      Serial.println("mode connecte");
    }
    delay(500);
  }*/
  //digitalWrite(CIBLE, HIGH);  
  Serial.println("Creation du point d'acces ...");
  WiFi.softAP(ssid, password);

  Serial.print("Adresse IP:");
  Serial.println(WiFi.softAPIP());
  Serial.println("Serveur demarrer");
  
            server.on("/cible/on", HTTP_POST, [](AsyncWebServerRequest *request){      //Alumer CIBLE   fini
            http_req=1;
            cible1.allumage_cible(1,50,17);
        });

          server.on("/cible/off", HTTP_POST, [](AsyncWebServerRequest *request){     //Eteindre CIBLE fini
            http_req=0;
            cible1.eteindre_cible(1,25,17);
        });


          server.on("/cible1/on", HTTP_POST, [](AsyncWebServerRequest *request){      //Alumer CIBLE1  fini
            http_req=1;
            cible1.allumage_cible(18,25,17);
        });

          server.on("/cible1/off", HTTP_POST, [](AsyncWebServerRequest *request){     //Eteindre CIBLE1 fini
            http_req=0;
            cible1.eteindre_cible(18,25,17);
        });



        server.on("/cible2/on", HTTP_POST, [](AsyncWebServerRequest *request){      //Alumer CIBLE2   fini
            http_req=1;
            cible1.allumage_cible(34,25,17);
         });

        server.on("/cible2/off", HTTP_POST, [](AsyncWebServerRequest *request){     //Eteindre CIBLE2 fini
            http_req=0;
            cible1.eteindre_cible(34,25,17);
        });



        /*server.on("/cible3/on", HTTP_POST, [](AsyncWebServerRequest *request){      //Alumer CIBLE3  fini
        digitalWrite(CIBLE2, HIGH);
        
         });

        server.on("/cible3/off", HTTP_POST, [](AsyncWebServerRequest *request){     //Eteindre CIBLE3 fini
        digitalWrite(CIBLE2, LOW);
          });



        server.on("/cible4/on", HTTP_POST, [](AsyncWebServerRequest *request){      //Alumer CIBLE4   fini
        digitalWrite(CIBLE2, HIGH);
        });

        server.on("/cible4/off", HTTP_POST, [](AsyncWebServerRequest *request){     //Eteindre CIBLE4 fini
        digitalWrite(CIBLE2, LOW);
         });*/

         /*if(digitalRead(LED) == HIGH){ //---------------Etat LED---------------------
          server.on("/relay/test", HTTP_POST, [](AsyncWebServerRequest *request){
          request-> send (200, "text / plain", String ("Salut"));
          });
          }

          if(digitalRead(LED) == HIGH){ //---------------Etat LED---------------------
          server.on("/relay/test", HTTP_POST, [](AsyncWebServerRequest *request){
          request-> send (200, "text / plain", "test");
          });
          }
          */



    /*server.on ("/rand", HTTP_POST, [](AsyncWebServerRequest *request) {     // Mode ludique a finir
    int f = random(2);
    if(f==1){
        digitalWrite(CIBLE, HIGH);
        delay(2000);
        digitalWrite(CIBLE, LOW);
    }
    if(f==2){
        digitalWrite(CIBLE1, HIGH);
        delay(2000);
        digitalWrite(CIBLE1, LOW);
    }
  });*/



  server.begin();


  
}

void loop() {
  Serial.println("Corruption avant ou apres cible1");
  //strip.setPixelColor(0, 255, 255, 255); //led exerne 
  int NumCibleTir=3;
  int nb_led_cible=16;
  int nb_led_cible1=17;
  int Broche_Cible=34;
  LED=0; //première cible
  //allumage_cible(LED,250);    définie que la led de la cible sélectionné est ici de 0 et que la pause via l'instruction delay 
  //entre chaque led est de 250 ms et donc que le temps minimum que prend la fonction est de 3.5s car 14*0.25=3.5 */
  cible1.allumage_cible(LED,1000,nb_led_cible1);  // allumage_cible(LED,1000,nb_led_cible1)
  LED+=nb_led_cible1; //saute la première serie
  cible1.SetLED(LED);
  Serial.print("Derniere led de la premiere serie ");
  Serial.println(LED);  
  //strip.setPixelColor(17, 0, 0, 0); //fin première série
  LED+=1;
  cible1.SetLED(LED);
  Serial.print("Première led de la deuxième serie ");
  Serial.println(LED);
  //delay(3000);
  cible1.allumage_cible(LED,1000); // fonctionnement confirmé de allumage_cible  // allumage_cible(LED,1000)
  LED+=nb_led_cible;
  cible1.SetLED(LED);
  Serial.println("Dernière led de la série");
  Serial.println(LED);
  LED-=nb_led_cible;
  cible1.SetLED(LED);
  //strip.setPixelColor(33, 0, 0, 0); //dernière led de la deuxième série
  delay(1000);
  cible1.eteindre_cible(LED,1000);  // eteindre_cible(LED,1000)
  cible1.eteindre_cible(LED,1000,nb_led_cible1); //  eteindre_cible(LED,1000,nb_led_cible1)
  LED-=nb_led_cible1;
  LED-=1;
  cible1.SetLED(LED);
  delay(3000);
  Serial.println("avant la corruption");
}







