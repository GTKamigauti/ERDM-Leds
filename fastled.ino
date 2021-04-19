#include <FastLED.h>

#define NUM_LEDS 60

#define DATA_PIN 8

#define BUTTON_PIN 6 //botão pino

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

    FastLED.setBrightness(1);

    pinMode(LED_BUILTIN, OUTPUT);
}

void loop(){

    click = digitalRead(BUTTON_PIN);
    
    if (click == LOW && lastclick == HIGH){
        if (state == true){
            state = false;
        }
        else {
            state = true;
        }
    }
    lastclick = click;
    
    if(state == true){ //botão solto faz firu firu
        dot = 0;
        for(int count = 1; count < (NUM_LEDS*2)-1; count++){ 
            passou = false;
            while (state == true && passou == false){
                n++;

                if (n > velocidade){
                    if(count > NUM_LEDS-1){
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
                click = digitalRead(BUTTON_PIN);

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
            if (state == false){
                n = 0;
                while(dot < 30){
                    n++;
                    if (n > (velocidade)+(decre/(30-dot))){
                        dot ++;
                    leds[dot] = CRGB::MediumSpringGreen; // BlueViolet
                    FastLED.show();
                    // clear this led for the next time around the loop
                    leds[dot] = CRGB::Black;
                    }
                }
                while(dot > 30){
                    n++;
                    if (n > (velocidade)+(decre/(dot-30))){
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
    else{
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