#ifndef FONCTION
#define FONCTION
class Cible
{
private:
    int nb_led_cible;
    int nb_led_cible1;
    int LED;
    Adafruit_NeoPixel led_strip;

public:
    Cible(Adafruit_NeoPixel strip);
    void SetLED(int LED);
    int allumage_cible(int LED_DEPART, int PAUSE);
    int allumage_cible(int LED_DEPART, int PAUSE, int NbLedCible);
    int eteindre_cible(int LED_DEPART, int PAUSE);
    int eteindre_cible(int LED_DEPART, int PAUSE, int NbLedCible);
    int calculResistance(int resistance_fixe,int intensite);
    bool CalculTir(int resistance_fixe, int led_interne, int Valeur_Seuil_Resistance);
    bool CalculTir(int resistance_fixe, int led_interne, int Valeur_Seuil_Resistance, int Broche_US);
};

#endif FONCTION