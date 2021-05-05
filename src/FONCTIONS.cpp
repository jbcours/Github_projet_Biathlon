#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "FONCTIONS.h"

float VCC=3.3;
#define US 34
#define PIN 22  // Port de sortie des données de la carte ESP-32
#define nombre_LED 240  //nombre de Led dans les 4m du bandeau lumineux
#define led2 2
#define intensite_lum 60

//Serial.begin(9600);  // Initialisation de la vitesse de transmission de la liaison série
//Adafruit_NeoPixel led_strip = Adafruit_NeoPixel(nombre_LED, PIN);


Cible::Cible(Adafruit_NeoPixel strip)
{
    this->led_strip=strip;
    //led_strip.begin();
    led_strip.show();
    this->nb_led_cible=16;
    this->nb_led_cible1=17;
}

void Cible::SetLED(int nv_LED){
    this->LED=nv_LED;

}

void Demo_setup(Adafruit_NeoPixel led_strip)
{
  int LED=11;
  led_strip.setPixelColor(LED, 255, 0, 255); // Permet decontroller led par led la couleur que la led affiche
  led_strip.show();
  //delay(250);
  LED=4;
  led_strip.setPixelColor(LED, 70, 255, 144);
  //delay(250);
  led_strip.show();
  LED=11;
  led_strip.setPixelColor(LED, 0, 0, 0);
  //delay(250);
  LED=4;
  led_strip.setPixelColor(LED, 0, 0, 0);
  //delay(250);
  led_strip.show();
  LED=1;
  led_strip.setPixelColor(LED, 255, 255, 255);
  //delay(500);
  Serial.println("fin du setup");
}

int Cible::allumage_cible(int LED_DEPART, int PAUSE)  // fonction servant à allumer toute les leds de l'anneau (16 led) en blanc pour signaler un tir sur la cible  
{
  int resistance_fixe=10000;
  unsigned long previous_Prog_Millis = millis();
  Serial.println("Debut de la boucle");
  int NbLedCible=16;  // nombre de led par cible
  int NbIteration=1; // permet de démarer le comptage à 1 des leds. 
  int LedActuel=LED_DEPART; // permet d'initialiser la variable LedActuel
  int rouge=intensite_lum;int vert=intensite_lum;int bleu=intensite_lum; // permet d'afficher dans l'anneau de la lumière blanche
  while(NbIteration<NbLedCible+1)   //permet de ne pas dépassr le nombre de led que possède l'anneau
  {
    LedActuel+=1;
    led_strip.setPixelColor(LedActuel,rouge,vert,bleu);  // permet d'afficher dans l'anneaau du blanc
    led_strip.show();  // permet d'actualiser la modification
    NbIteration+=1;
    delay(250); // attend une période à chaque allumage de led de l'anneau
    while ((millis() - previous_Prog_Millis >= PAUSE))
    {
      previous_Prog_Millis=millis();
      if(CalculTir(resistance_fixe, led2, 8000)==1)
      {
        Serial.println("Fin de la boucle tir effectue");
        return 1;
      }
    }
  }
  Serial.println(LedActuel);
  Serial.println("Fin de la boucle allumage de led");
  return 0;
}

int Cible::allumage_cible(int LED_DEPART, int PAUSE, int NbLedCible)  // fonction servant à allumer toute les leds de l'anneau en blanc pour signaler un tir sur la cible  
{
  int resistance_fixe=10000;
  unsigned long previous_Prog_Millis = millis();
  Serial.println("Debut de la boucle");
  int NbIteration=1; // permet de démarer le comptage à 1 des leds. 
  int LedActuel=LED_DEPART; // permet d'initialiser la variable LedActuel
  int rouge=intensite_lum;int vert=intensite_lum;int bleu=intensite_lum; // permet d'afficher dans l'anneau de la lumière blanche
  while(NbIteration<NbLedCible+1)   //permet de ne pas dépassr le nombre de led que possède l'anneau
  {
    LedActuel+=1;
    led_strip.setPixelColor(LedActuel,rouge,vert,bleu);  // permet d'afficher dans l'anneaau du blanc
    led_strip.show();  // permet d'actualiser la modification
    NbIteration+=1;
    delay(250); // attend une période à chaque allumage de led de l'anneau
    while ((millis() - previous_Prog_Millis >= PAUSE))
    {
      previous_Prog_Millis=millis();
      if(CalculTir(resistance_fixe, led2, 8000)==1)
      {
        Serial.println("Fin de la boucle tir effectue");
        return 1;
      }
    }
  }
  Serial.println(LedActuel);
  Serial.println("Fin de la boucle allumage de led");
  return 0;
}

int Cible::eteindre_cible(int LED_DEPART, int PAUSE)  // fonction servant à allumer toute les leds de l'anneau (14 led) en blanc pour signaler un tir sur la cible  
{
  int resistance_fixe=10000;
  unsigned long previous_Prog_Millis = millis();
  Serial.println("Debut de la boucle");
  int NbLedCible=16;  // nombre de led par cible
  int NbIteration=1; // permet de démarer le comptage à 1 des leds. 
  int LedActuel=LED_DEPART+NbLedCible; // permet d'initialiser la variable LedActuel
  int rouge=0;int vert=0;int bleu=0; // permet d'afficher dans l'anneau de la lumière blanche
  Serial.print("Debut de la boucle eteindre valeur de led est ");
  Serial.print(LedActuel-1);
  while(NbIteration<NbLedCible+1)   //permet de ne pas dépassr le nombre de led que possède l'anneau
  {
    LedActuel-=1;
    led_strip.setPixelColor(LedActuel,rouge,vert,bleu);  // permet d'afficher dans l'anneaau du blanc
    led_strip.show();  // permet d'actualiser la modification
    NbIteration+=1;
    delay(250); // attend une période à chaque allumage de led de l'anneau
  }
  Serial.print("Fin de la boucle eteindre valeur de led est ");
  Serial.println(LedActuel);
  Serial.println("Fin de la boucle etteidre  de led");
  return 0;
}

int Cible::eteindre_cible(int LED_DEPART, int PAUSE, int NbLedCible)  // fonction servant à allumer toute les leds de l'anneau en blanc pour signaler un tir sur la cible  
{
  int resistance_fixe=10000;
  unsigned long previous_Prog_Millis = millis();
  Serial.println("Debut de la boucle");
  int NbIteration=1; // permet de démarer le comptage à 1 des leds. 
  int LedActuel=LED_DEPART; // permet d'initialiser la variable LedActuel
  int rouge=0;int vert=0;int bleu=0; // permet d'afficher dans l'anneau de la lumière blanche
  Serial.print("Debut de la boucle eteindre valeur de led est ");
  Serial.print(LedActuel-1);   
  while(NbIteration<NbLedCible+1)   //permet de ne pas dépassr le nombre de led que possède l'anneau
  { 
    LedActuel-=1;
    led_strip.setPixelColor(LedActuel,rouge,vert,bleu);  // permet d'afficher dans l'anneaau du blanc
    led_strip.show();  // permet d'actualiser la modification
    NbIteration+=1;
    delay(250); // attend une période à chaque allumage de led de l'anneau
  }
  /*Serial.print("Fin de la boucle eteindre valeur de led est ");
  Serial.println(LedActuel);
  Serial.println("Fin de la boucle eteindre de led");*/
  return 0;
}

int Cible::calculResistance(int resistance_fixe,int intensite)
{
  int photoresistance=0;
  float valeur_US=0;
  valeur_US=intensite*(0.0001*8.05);
  //Serial.print("Valeur de l'intensite ");
  //Serial.println(valeur_US);
  photoresistance=((VCC*resistance_fixe)/valeur_US)-resistance_fixe;
  return photoresistance;
}



bool Cible::CalculTir(int resistance_fixe, int led_interne, int Valeur_Seuil_Resistance){ // 
  int photoresistance=0,Tension_Us=0;
  bool Tir_Confirmer=false;
  int intervalle_tir=1000; // tir d'une seconde
  Tension_Us = analogRead(US); // US Broche_Cible
  photoresistance=calculResistance(resistance_fixe,Tension_Us);
  unsigned long previous_Prog_Millis = millis();


  if(photoresistance<Valeur_Seuil_Resistance){
    digitalWrite(led_interne,HIGH);
    while ( !(millis() - previous_Prog_Millis >= intervalle_tir))
      {
        Tension_Us = analogRead(US);
        photoresistance=calculResistance(resistance_fixe,Tension_Us);
      }
      while (photoresistance<Valeur_Seuil_Resistance)  // reste prisonnier de la boucle tant que la gachette n'arrete pas de tirer sur la cible
      {
        Tension_Us = analogRead(US);
        photoresistance=calculResistance(resistance_fixe,Tension_Us);
        delay(250);
        Serial.println("boucle fin de tir");
      }
      Serial.println("tir confirme");
      Tir_Confirmer=true;
      previous_Prog_Millis = millis();
      delay(1000);

      digitalWrite(led_interne,LOW);
    return Tir_Confirmer;
  }
  else return false;

}

bool Cible::CalculTir(int resistance_fixe, int led_interne, int Valeur_Seuil_Resistance, int Broche_US){ // 
  int photoresistance=0,Tension_Us=0;
  bool Tir_Confirmer=false;
  int intervalle_tir=1000; // tir d'une seconde
  Tension_Us = analogRead(Broche_US); // US Broche_Cible
  photoresistance=calculResistance(resistance_fixe,Tension_Us);
  unsigned long previous_Prog_Millis = millis();


  if(photoresistance<Valeur_Seuil_Resistance){
    digitalWrite(led_interne,HIGH);
    while ( !(millis() - previous_Prog_Millis >= intervalle_tir))
      {
        Tension_Us = analogRead(Broche_US);
        photoresistance=calculResistance(resistance_fixe,Tension_Us);
      }
      while (photoresistance<Valeur_Seuil_Resistance)  // reste prisonnier de la boucle tant que la gachette n'arrete pas de tirer sur la cible
      {
        Tension_Us = analogRead(Broche_US);
        photoresistance=calculResistance(resistance_fixe,Tension_Us);
        delay(250);
        Serial.println("boucle fin de tir");
      }
      Serial.println("tir confirme");
      Tir_Confirmer=true;
      previous_Prog_Millis = millis();
      delay(1000);

      digitalWrite(led_interne,LOW);
    return Tir_Confirmer;
  }
  else return false;

}







