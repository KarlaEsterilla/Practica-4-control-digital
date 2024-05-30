#include <Arduino.h>
#include <math.h>
#include <interrupcion.h>



void interrupcion (bool flag_seq, bool state_led ){
    switch (flag_seq){
        case 0:
            static float seq =0;
            digitalWrite(arreglo_leds.leds[(int)floor(seq)],state_led);
            //Serial.println((int)floor(seq));
            if (seq >= (arreglo_leds.numero_leds-0.5)){
                seq=0;
            }else{
                seq=seq+0.5;
            }
        break;
        case 1:
            static float seq1 =(arreglo_leds.numero_leds-0.5);
            //Serial.println(seq1);
            digitalWrite(arreglo_leds.leds[(int)floor(seq1)],state_led);
            if (seq1 == (0)){
                seq1=(arreglo_leds.numero_leds-0.5);
            }else{
                seq1=seq1-0.5;
            } 
        break;
        default:
            break;
        }
}