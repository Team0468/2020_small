#include <kipr/botball.h> 
#include <main_functions.h>
#include <threads.h>
#include <variables.h>
#include <run_sections.h>

void lift_arm_up(){
    servo(arm,arm_block+120,fast);
}
void lower_arm(){
    msleep(1500);
    servo(arm,arm_min,fast);
}
void raise_arm(){
    servo(arm,arm_max,fast);
}
void big_block(){
	servo(arm,arm_bigblock-150,slow+1);   
}
void claw_open(){
    msleep(1275);
    servo(claw,claw_max,fast);
}
void claw_close_pull(){
    msleep(500);
    servo(claw,claw_min,slow);
}
void lower_arm_2(){
 servo(arm,arm_min,fast);   
}
void claw_open2(){
    servo(claw,claw_max,fast);
}
void big_block2(){
    servo(arm,arm_bigblock,slow);
}
void arm_water(){
    msleep(400);
    servo(arm,arm_max,slow+1);
    
}
void arm_water2(){
    servo(arm,arm_max-286,slow);
}
void claw_waterC(){
    servo(claw,claw_min+10,slow);
}
void block_raise(){
    msleep(600);
    servo(arm,arm_block+70,slow);
}
void block_lower(){
   
    servo(arm,arm_min+358,slow+1);
}
//all thread functions for main and seperate voids and int's