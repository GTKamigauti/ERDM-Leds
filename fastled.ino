#include <FastLED.h>

#define NUM_LEDS 54

#define DATA_PIN 8 //pino led

#define BUTTON_PIN 6 //botão pino

#define POT_PINLUZ A5 //Potenciometro de luminosidade

#define Pot_PINVELO A3 //Potenciopmetro de velocidade

int PotValueLUZ;

int PotValueVELO;

int lastclick = HIGH; //botão estado inicial

int click = HIGH; //var de botão

bool state = false;
// Define the array of leds

long velocidade = 2000;

float decre = 30000;

long n = 0;

bool passou;

int dot;

int dist;

CRGB leds[NUM_LEDS];

void setup(){ 

    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical
    LEDS.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);

    pinMode(BUTTON_PIN, INPUT_PULLUP); //assignar o pino do bot]ao para pullup

    FastLED.setBrightness(0);

    pinMode(LED_BUILTIN, OUTPUT);

    pinMode(POT_PINLUZ, INPUT);

    pinMode(Pot_PINVELO, INPUT);
}

void loop(){


    PotValueLUZ = analogRead(POT_PINLUZ); //está lendo o potenciometro
    PotValueLUZ = map(PotValueLUZ, 0, 1023, 0, 255); //mapeando os 1023 para 255

    FastLED.setBrightness(PotValueLUZ);

    PotValueVELO = analogRead(Pot_PINVELO);
    PotValueVELO = map(PotValueVELO, 0, 1023, 0, 2000); //2000 velo de agr

    click = digitalRead(BUTTON_PIN);
    
    if (click == LOW && lastclick == HIGH){ //rotina de botão
        if (state == true){
            state = false;
        }
        else {
            state = true;
        }
    }
    lastclick = click;
    
    if(state == true){ //rotina de led
        dot = 0; //inicializa o led no 0
        for(int count = 1; count < (NUM_LEDS*2)-1; count++){ //rotina do led que faz ir e voltar
            passou = false; //booleano que define se o led passou
            while (state == true && passou == false){
                n++;

                if (n > PotValueVELO){ // condicional que define a velocidade dos leds no lugar de um delay
                    if(count > NUM_LEDS-1){ //condicional que faz o led ir e voltar
                        dot--;
                    }
                    else{
                        dot++;
                    }
                    leds[dot] = CRGB::MediumSpringGreen; // BlueViolet
                    FastLED.show();
                    // clear this led for the next time around the loop
                    leds[dot] = CRGB::Black;
                    
                    n = 0;
                    passou = true;
                }
                click = digitalRead(BUTTON_PIN); // leitura do botão para sair da rotina de led

                if (click == LOW && lastclick == HIGH){
                    if (state == true){
                        state = false;
                    }
                    else{
                        state = true;
                    }
                }
                lastclick = click;
            }
            if (state == false){ //depois de apertar o botão para parar, se aplica um efeito de suavisação
                n = 0;
                while(dot < (NUM_LEDS/2)){ //faz o led avançar para o centro lentamente 
                    n++;
                    if (n > (PotValueVELO)+(decre/((NUM_LEDS/2)-dot))){
                        dot ++;
                    leds[dot] = CRGB::MediumSpringGreen; // BlueViolet
                    FastLED.show();
                    // clear this led for the next time around the loop
                    leds[dot] = CRGB::Black;
                    }
                }
                while(dot > (NUM_LEDS/2)){ //faz o led voltar para o centro lentamente
                    n++;
                    if (n > (PotValueVELO)+(decre/(dot-(NUM_LEDS/2)))){
                        dot --;
                    leds[dot] = CRGB::MediumSpringGreen; // BlueViolet
                    FastLED.show();
                    // clear this led for the next time around the loop
                    leds[dot] = CRGB::Black;
                    }
                }
                break;
            }
        }
    }
    else{ //apaga os leds
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
    }
            //leds[dot] = CRGB::MediumSpringGreen; // BlueViolet
            //FastLED.show();
            // clear this led for the next time around the loop
            //leds[dot] = CRGB::Black;
            //delay(20); //200 = vel 8
}

void flag() {
    digitalWrite(LED_BUILTIN, HIGH);   
    delay(1000);                       
    digitalWrite(LED_BUILTIN, LOW);   
    delay(1000);
}