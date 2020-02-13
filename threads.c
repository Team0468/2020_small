#include <kipr/botball.h> 
#include <main_functions.h>
#include <threads.h>
#include <variables.h>
#include <run_sections.h>
#include <Tyler_gyro.h>
void lift_arm_up(){
    servo(arm,arm_block,2);
}
void lower_arm(){
    msleep(1000);
    servo(arm,arm_block,fast);
}
void raise_arm(){
    servo(arm,arm_max,fast);
}
void big_block(){
	servo(arm,arm_bigblock,slow);   
}
void gyro(){

    float kp = 0.0004;// start adjusting this (smaller increments = more acurate)
    float ki = 0;
    float kd = 1;

    float currentL = 0;
    float currentR = 0;
    float circ = 5 * 3.141592653589;
	//float baseL = 50;
    //float baseR = 50;
    int base = 60;
    float integralActiveZone = ((1*12/circ)*360);




    while(1){
        float errorL = ((bias * 12 / circ) * 360 ) - gyro_z();
        float errorR = ((bias * 12 / circ) * 360 ) - gyro_z();
        if (errorL < integralActiveZone && errorL != 0){

            errorTl += errorL;

        }
        else{

            errorTl = 0;

        }
        if(errorR < (( integralActiveZone * 12 / circ ) * 360) && errorR != 0){

            errorR += errorR;

        }
        else{

            errorTr = 0;

        }
        if(errorTl > 50 / ki){

            errorTl = 50 / ki;

        }
        if(errorTr > 50 / ki){

            errorTr = 50 / ki;

        }
        if(errorL == 0){

            derivativeL = 0;

        }
        if(errorR == 0){

            derivativeR = 0;

        }

        proportionL = errorL * kp;
        proportionR = errorR * kp;
        integralL = errorTl * ki;
        integralR = errorTr * ki;
        derivativeL = (errorR - lastErrorL) * kd;
        derivativeR = (errorL - lastErrorR) * kd;

        lastErrorL = errorL;
        lastErrorR = errorR;

		

        currentR = proportionR + integralR + derivativeR;
        currentL = proportionL + integralL + derivativeL;

		baseL = base + currentL;
        baseR = base + currentR;

        if (currentL == 0 && currentR == 0){

            currentR = 0;
            currentL = 0;

        }
        if(currentL < 0){

            currentL = 0;

        }
        if(currentR < 0){

            currentR = 0;

        }
        msleep(20);
    }
}
//all thread functions for main and seperate voids and int's