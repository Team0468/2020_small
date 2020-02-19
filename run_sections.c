#include <kipr/botball.h> 
#include <main_functions.h>
#include <threads.h>
#include <variables.h>
#include <run_sections.h>
#include <timer.h>
//time/sections of the run as a whole for ease of finding the section desired
#define back  (-70)
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
    reset_timer(5);
    
    while (digital(left_motor) ==0 || digital(right_motor)==0){//original
        digital(left_motor)==0 ? left_motor_move(back) : left_motor_move(stop);
        digital(right_motor)==0 ? right_motor_move(back) : right_motor_move(stop);
      if(timer(5)> 2){break;}  
    }
    

    while(digital(back_port) == 0 ){//dropping arm
        if(digital(back_port) == 0){
            motor(back_port,back);
        }
        else if (digital(back_port) == 1){


            break;
        }
    }
    off(back_port);

    cmpc(back_claw);
    reset_timer(1);
    
    while(gmpc(back_claw) < 280 && timer(1) < 2){//closing back claw

        hand(down*(-1));

    }
    
    hand(stop);
    cmpc(back_port);
    reset_timer(2);
    while(analog(back_bound) < 2000 && timer(2) < 2){
        back_arm_move(forward);

    }

    back_arm_move(stop);
    off(back_port);
	off(back_claw);
    msleep(300);
    hand(stop);
    return water_contain();   


}
int extraction_2()
{
    reset_timer(5);
    while (digital(left_motor) ==0 || digital(right_motor)==0){//original
        digital(left_motor)==0 ? left_motor_move(back) : left_motor_move(stop);
        digital(right_motor)==0 ? right_motor_move(back) : right_motor_move(stop);
        if(timer(5)>2){break;}
    }
    move(0,0);

    while(digital(back_port) == 0 ){//dropping arm

        if(digital(back_port) == 0){
            motor(back_port,back);
        }
        else if (digital(back_port) == 1){
            break;
        }
    }
    off(back_port);
    hand(stop);
    cmpc(back_claw);
    reset_timer(1);
    while(gmpc(back_claw) < 280 && timer(1) < 2){//closing back claw

        hand(down*(-1));

    }
    hand(stop);
    cmpc(back_port);
    reset_timer(2);
    while(analog(back_bound) < 2000 && timer(2) < 2){
        back_arm_move(forward);

    }
    back_arm_move(stop);
    off(back_claw);
    off(back_port);
    msleep(300);
    hand(stop);
    return delivery();


}
int extraction_3()
{
    reset_timer(5);
    while (digital(left_motor) ==0 || digital(right_motor)==0){//original
        digital(left_motor)==0 ? left_motor_move(back) : left_motor_move(stop);
        digital(right_motor)==0 ? right_motor_move(back) : right_motor_move(stop);
        if(timer(5)>2){break;}
    }
    move(0,0);

    while(digital(back_port) == 0 ){//dropping arm

        if(digital(back_port) == 0){
            motor(back_port,back);
        }
        else if (digital(back_port) == 1){
            break;
        }
    }
    off(back_port);
    cmpc(back_claw);
    reset_timer(1);
    while(gmpc(back_claw) < 280 && timer(1) < 2){//closing back claw

        hand(down*(-1));

    }
    hand(stop);
    
    cmpc(back_port);
    reset_timer(2);
    while(analog(back_bound) < 2000 && timer(2) < 2){
        back_arm_move(forward);
    }

    back_arm_move(stop);
    off(back_claw);
    msleep(300);
    hand(stop);
    
    off(back_port);
    return delivery_2();


}
int left_motor_move(int speed){motor(left_motor,speed); return 1;}
int right_motor_move(int speed){motor(right_motor,speed); return 1;}
int back_arm_move(int speed){motor(back_port,speed); return 1;};
int hand(int speed){motor(back_claw,speed); return 1;};

int water_contain(){

    Drive(3600,80);
    stop_1();
    move(0,900);
    msleep(500);
    stop_1();
    servo(claw,claw_min,slow+1);
    stop_1();
    move(0,-600);
    msleep(950);
    
    
    stop_1();
    square_up(white,-600);
    stop_1();

    return place_block_and_go();
}
int place_block_and_go(){
    thread openc;
    openc = thread_create(claw_open);
    thread_start(openc);
    Drive(-2750,-80);

    stop_1();
    turn_with_gyro(800,-90);
    stop_1();
    Drive(900,80);
    stop_1();
    hand(stop);
    while(digital(back_port) ==0 ){//dropping arm  THIS IS THE TIMER
        digital(back_port)==0 ? back_arm_move(down) :back_arm_move(stop);}
    off(back_port);
    cmpc(back_claw);
    cmpc(back_claw);
    float start_time=seconds();
    float elapsed;
    while(gmpc(back_claw) > -230 && elapsed < 2 ){//closing back claw THIS IS THE TIMER
        gmpc(back_claw) > -230 ? hand(back) : off(back_claw); elapsed=seconds()-start_time;}
    off(back_claw);
    move(-600,-600);
    msleep(600);
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
    thread_destroy(openc);
    return block_2andstack();
}

int block_2andstack(){
    thread lift_up1;
    lift_up1 = thread_create(lift_arm_up);
    thread_start(lift_up1);
    stop_1();
    Drive(1400,80);
    stop_1();
    servo(claw,claw_min,slow);
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

    move(650,650);
    msleep(1300);
    stop_1();
    turn_with_gyro(800,-90);
    stop_1();
    square_up(black,-600);
    stop_1();
    move(800,800);
    msleep(650);
    stop_1();
    hand(stop);
    while(digital(back_port) ==0 ){//dropping arm
        digital(back_port)==0 ? back_arm_move(down) :back_arm_move(stop);}
    off(back_port);
    cmpc(back_claw);
    cmpc(back_claw);
    while(gmpc(back_claw) > -230 ){//closing back claw
        gmpc(back_claw) > -230 ? hand(back) : off(back_claw); }
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
    square_up(black,-800);
    thread_start(block);
    move(450,0);
    msleep(300);
    stop_1();
    servo(claw,claw_min + 400,slow);
   servo(arm,arm_max,fast);
    
    stop_1();
    move1("d",square,black,-800);


    thread_destroy(raise);

    return blocks_2();
}
int blocks_2(){
    thread lower2;
    	lower2 = thread_create(lower_arm_2);
    thread raise1;
    	raise1 = thread_create(block_raise);
    
    stop_1();
	turn_with_gyro(800,-90);
    stop_1();
    move(-600,-600);
    msleep(500);
    stop_1();
    thread_start(lower2);
    turn_with_gyro(800,-90);
    stop_1();
    square_up(black,-800);
    Drive(1350,80);
    stop_1();
    servo(arm,arm_min+300,slow+1);
    servo(claw,claw_min,slow);
    servo(arm,arm_min+370,slow+1);
    stop_1();
    move1("d",drive,2800,80);
    stop_1();
    servo(arm,arm_min+300,slow);
    servo(claw,claw_min+400,slow);
	stop_1();
    move1("d",drive,-2650,-80);
    servo(arm,arm_max,fast);
    servo(claw,claw_max,fast);
    stop_1();
    move(600,-600);
    msleep(500);
    stop_1();
    servo(arm,arm_block-28,slow+1);
    servo(claw,claw_min-10,slow);
    servo(arm,arm_block+200,fast);
    stop_1();
    move(-600,600);
    msleep(500);
    stop_1();
    servo(arm,arm_min+370,slow+1);
    move1("d",drive,1800,80);
    stop_1();
    thread_start(raise1);
    move1("d",turn,800,90);
    
    
    thread_destroy(raise1);
    thread_destroy(lower2);
    return extraction_3();   
}
int delivery_2(){
    thread lower2;
    lower2 = thread_create(lower_arm_2);
    thread block2;
    block2 = thread_create(big_block2);
    thread copen2;
    copen2 = thread_create(claw_open2);
    thread lower3;
    	lower3 = thread_create(block_lower);
    move(650,650);
    msleep(900);
    stop_1();
    thread_start(lower3);
    turn_with_gyro(800,-90);
    stop_1();
    move(-600,600);
    msleep(300);
    stop_1();
    Drive(-1700,-80);
    stop_1();
    servo(arm,arm_max,fast);
    move(-400,400);
    msleep(700);
    stop_1();
    move1("d",square,black,-800);
    stop_1();
    move1("d",drive,-800,-80);
    stop_1();
    hand(stop);
    while(digital(back_port) ==0 ){//dropping arm
        digital(back_port)==0 ? back_arm_move(down) :back_arm_move(stop);}
    off(back_port);
    cmpc(back_claw);
    cmpc(back_claw);
    while(gmpc(back_claw) > -230 ){//closing back claw
        gmpc(back_claw) > -230 ? hand(back) : off(back_claw); }
    off(back_claw);
    move(800,800);
    msleep(400);
    stop_1();
    reset_timer(2);
    while(analog(back_bound) < 2000 && timer(2) < 2){
        back_arm_move(forward);

    }

    back_arm_move(stop);
    off(back_port);
    servo(arm,arm_max,fast);
    stop_1();
    move1("d",turn,800,90);
    stop_1();
    move1("d",turn,800,90);
    stop_1();
    move1("d",square,black,-800);
    thread_start(block2);
    stop_1();
    move(400,0);
    msleep(300);
    move(600,600);
    msleep(400);
    stop_1();
    servo(claw,claw_min+400,slow);
    servo(arm,arm_bigblock+200,fast);
    servo(claw,claw_min,slow);
    servo(arm,arm_max,fast);
    stop_1();
    move(0,-800);
    msleep(1000);
    move(-800,-800);
    msleep(400);
    stop_1();
    servo(arm,arm_bigblock-100,slow+1);
    servo(claw,claw_min+400,fast);
    servo(arm,arm_max,fast);
    stop_1();
    move(0,800);
    msleep(1000);
    stop_1();
    move1("d",square,black,-800);
    
    
    

	thread_destroy(lower3);
	thread_destroy(copen2);
    thread_destroy(block2);
    thread_destroy(lower2);
    return water_collect();   
}
int water_collect(){
    thread copen3;
    	copen3 = thread_create(claw_open2);
    thread arm2;
    	arm2 = thread_create(arm_water);
    thread arm3;
    	arm3 = thread_create(arm_water2);
    thread clawC;
    	clawC = thread_create(claw_waterC);
	stop_1();
    move1("d",square,black,-800);
    stop_1();
    move1("d",turn,800,-45);
    stop_1();
    move(600,-600);
    msleep(150);
    stop_1();
    servo(claw,claw_max,fast);
    stop_1();
    
    move(-600,-600);
    msleep(700);
    
    stop_1();
    servo(arm,arm_min+40,slow);
    move(600,600);
    msleep(1300);
    stop_1();
    servo(claw,claw_min,slow);
    stop_1();
    move(-500,-500);
    msleep(2000);
    stop_1();
    move(-600,-50);
    msleep(1900);
    stop_1();
    move(50,600);
    msleep(3000);
    move(800,800);
    msleep(400);
    stop_1();
    thread_start(arm2);
    thread_start(copen3);
    move(-1000,-1000);
    msleep(600);
    move(0,800);
    msleep(800);
    thread_start(arm3);
    move(400,400);
    msleep(850);
    stop_1();
    thread_start(clawC);
    stop_1();
    msleep(500);
    servo(arm,arm_max,slow);
    move(-400,-400);
    msleep(850);
    move(600,-600);
    msleep(550);
    stop_1();
    servo(arm,arm_min+570,fast);
    servo(claw,claw_min+400,fast);
    msleep(100000);
    thread_destroy(clawC);
    thread_destroy(arm3);
    thread_destroy(arm2);
    thread_destroy(copen3);
	return 0;
}