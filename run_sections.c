#include <kipr/botball.h> 
#include <main_functions.h>
#include <threads.h>
#include <variables.h>
#include <run_sections.h>
#include <Tyler_gyro.h>
//time/sections of the run as a whole for ease of finding the section desired
#define back  (-50)
#define forward 70
int counter = 0;
int stop, back_claw = 0;
int left_motor_move();
int right_motor_move();
int back_port =3;
int back_bound = 5;
int back_arm_move();
int down = .5*back;
int hand();
int extraction()
{
    while (digital(left_motor) ==0 || digital(right_motor)==0){//original
        digital(left_motor)==0 ? left_motor_move(back) : left_motor_move(stop);
        digital(right_motor)==0 ? right_motor_move(back) : right_motor_move(stop);
    }
    while (digital(left_motor) ==0 || digital(right_motor)==0){//secondary
        digital(left_motor)==0 ? left_motor_move(back) : left_motor_move(stop);
        digital(right_motor)==0 ? right_motor_move(back) : right_motor_move(stop);

    }
    move(0,0);

    while(digital(back_port) ==0 ){//dropping arm
        digital(back_port)==0 ? back_arm_move(down) : back_arm_move(stop);}

    cmpc(back_claw);
    while(gmpc(back_claw) < 267 ){//closing back claw
        digital(back_claw)==0 ? hand(down*(-1)) : off(back_claw); }
    off(back_claw);
    cmpc(back_port);
    while(analog(back_bound) < 2000){
        back_arm_move(forward);

    }

    back_arm_move(stop);


    return water_contain();   

}
int extraction_2()
{
    while (digital(left_motor) ==0 || digital(right_motor)==0){//original
        digital(left_motor)==0 ? left_motor_move(back) : left_motor_move(stop);
        digital(right_motor)==0 ? right_motor_move(back) : right_motor_move(stop);
    }
    while (digital(left_motor) ==0 || digital(right_motor)==0){//secondary
        digital(left_motor)==0 ? left_motor_move(back) : left_motor_move(stop);
        digital(right_motor)==0 ? right_motor_move(back) : right_motor_move(stop);

    }
    move(0,0);

    while(digital(back_port) ==0 ){//dropping arm
        digital(back_port)==0 ? back_arm_move(down) : back_arm_move(stop);}

    cmpc(back_claw);
    while(gmpc(back_claw) < 269 ){//closing back claw
        digital(back_claw)==0 ? hand(down*(-1)) : off(back_claw); }
    off(back_claw);
    cmpc(back_port);
    while(analog(back_bound) < 2000){
        back_arm_move(forward);

    }

    back_arm_move(stop);
    return delivery();

}
int left_motor_move(int speed){motor(left_motor,speed); return 1;}
int right_motor_move(int speed){motor(right_motor,speed); return 1;}
int back_arm_move(int speed){motor(back_port,speed); return 1;};
int hand(int speed){motor(back_claw,speed); return 1;};

int water_contain(){

    Drive(3550,80);

    stop_1();
    PID_gyro_drive(800,.2);
    stop_1();
    move(0,900);
    msleep(500);
    stop_1();
    servo(claw,claw_min,fast);
    msleep(500);
    move(0,-900);
    msleep(500);
    stop_1();
    square_up(white,-800);
    stop_1();

    return place_block_and_go();
}
int place_block_and_go(){
    Drive(-1700,-80);
    stop_1();
    servo(claw,claw_max,fast);
    Drive(-1000,-80);
    stop_1();
    turn_with_gyro(800,-90);
    stop_1();
    Drive(900,80);
    stop_1();
    while(digital(back_port) ==0 ){//dropping arm  THIS IS THE TIMER
        digital(back_port)==0 ? back_arm_move(down) :back_arm_move(stop);}
    off(back_port);
    cmpc(back_claw);
    cmpc(back_claw);
    float start_time=seconds();
    float elapsed;
    while(gmpc(back_claw) > -280 ||elapsed<2.5 ){//closing back claw THIS IS THE TIMER
        gmpc(back_claw) > -280 ? hand(back) : off(back_claw); elapsed=seconds()-start_time;}
    off(back_claw);
    move(-600,-600);
    msleep(220);
    move(400,400);
    msleep(400);
    stop_1();
    while(analog(back_bound) < 2000){
        back_arm_move(forward);   
    }

    back_arm_move(stop);
    off(back_port);
    stop_1();
    square_up(white,800);
    return block_2andstack();
}

int block_2andstack(){
    thread lift_up1;
    lift_up1 = thread_create(lift_arm_up);
    thread_start(lift_up1);
    stop_1();
    Drive(1400,80);
    stop_1();
    servo(claw,claw_min-200,slow);
    stop_1();
    servo(arm,arm_max,slow);
    move(-500,-500);
    msleep(450);

    stop_1();
    turn_with_gyro(800,90);
    stop_1();
    thread_destroy(lift_up1);
    return extraction_2();
}
int delivery(){
    thread block;
    	block = thread_create(big_block);
    thread raise;
    	raise = thread_create(raise_arm);
    thread lower;
    	lower = thread_create(lower_arm);
    move(650,650);
    msleep(1050);
    stop_1();
    thread_start(lower);
    turn_with_gyro(800,-90);
    stop_1();
    square_up(black,-600);
    stop_1();
    move(800,800);
    msleep(650);
    stop_1();
    while(digital(back_port) ==0 ){//dropping arm
        digital(back_port)==0 ? back_arm_move(down) :back_arm_move(stop);}
    off(back_port);
    cmpc(back_claw);
    cmpc(back_claw);
    while(gmpc(back_claw) > -280 ){//closing back claw
        gmpc(back_claw) > -280 ? hand(back) : off(back_claw); }
    off(back_claw);
    move(800,800);
    msleep(400);
    stop_1();
    while(analog(back_bound) < 2000){
        back_arm_move(forward);   
    }

    back_arm_move(stop);
    off(back_port);
    stop_1();
    thread_start(raise);
    turn_with_gyro(800,90);
    stop_1();
    turn_with_gyro(800,90);
    stop_1();
    thread_start(block);
    move(450,0);
    msleep(500);
    stop_1();
    servo(claw,claw_min + 400,slow);
    stop_1();
    servo(arm,arm_bigblock+160,slow);
    servo(claw,claw_min-200,slow);
    servo(arm,arm_bigblock+170,fast);
    move(-800,-800);
    msleep(500);
    stop_1();
    servo(arm,arm_bigblock,fast);
    servo(claw,claw_min+400,fast);
    thread_destroy(raise);
    thread_destroy(lower);
    return 0;
}