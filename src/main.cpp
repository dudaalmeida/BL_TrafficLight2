#include "mbed.h"

enum states{RED,GREEN,YELLOW,A,O};
int state = RED, last;
DigitalOut lights[] = {(p6),(p7),(p8)};
InterruptIn btn (p5);
float times[] = {10.0, 20.0, 4.0};
int on = 1,aux, c=0, off1 = 0;
Timeout t,b;

void btnFall();
void btnRise();
void clear_all();
void off();
void blink();
void nextState();
void allert();
void lightsOn();
void tempo();

int main() {
        lights[state] = 1;
        btn.rise(&btnRise);
        btn.fall(&btnFall);
        t.attach(nextState, times[state]);
     }

void btnRise(){
    on = 1;
    tempo();
   
}

void btnFall(){
    on = 0;
     
    if(off1 == 0 && c<3 && state != GREEN) c=0;
    if(off1 == 0 && c<3 && state == GREEN){
        c=0;
        nextState(); 
    }                                                         // t<3
    if(off1 == 0 && c>=3 && c<=10){
        c=0;
        allert();            
    }                                                         // t>=3 e t<=10
    if(off1 == 0 && c>10){
        c=0;
        off(); 
    }                                                         // t>10
    if(off1 == 1 && c>10) {
        c=0;
        lightsOn(); 
    }                                                         // Já desligado e t>10
    
}

void tempo(){
    if(on){
        c++;
        printf("%i \n", c);
        b.attach(&tempo,1);
    }
}

void clear_all(){
    int j;
    for(j=0;j<3;j++){
        lights[j] = 0;
    }
}

void off(){
    clear_all();
    off1 = 1;
   
}

void lightsOn(){
        off1 = 0;
        nextState();
}

void nextState(){
    clear_all();
    if(state < 2){
        state++;
    }else{
        state = RED;
    }
    lights[state] = 1;
    last = state;
    t.attach(&nextState, times[state]);
}

void blink(){
    lights[YELLOW] = !lights[YELLOW];
    t.attach(&blink, 0.5);
}

void allert(){
        clear_all();
        if(state != A){
            state = A;
            blink();
        }else{
            state = last - 1;
            nextState();
        }
}
