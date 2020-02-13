#include <kipr/botball.h> 
#include <main_functions.h>
#include <threads.h>
#include <variables.h>
#include <run_sections.h>
#include <filter.h>
#include <Tyler_gyro.h>
void main_gyro(int distance){
    float kp = 0;// start adjusting this (smaller increments = more acurate)
    float ki = 0;
    float kd = 0;

      float currentL = 0;
    float currentR = 0;
    float circ = 5 * 3.141592653589;
    int base = 60;
    float integralActiveZone = ((1*12/circ)*360);
 
    

    while(gmpc(left_motor) < (distance-500)){

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
void gyro_drive_T(int desired){
    calibrate_gyro();
    cmpc(left_motor);
    cmpc(right_motor);
    main_gyro(desired);
   // move(currentL,currentR);
    msleep(2000);
}

