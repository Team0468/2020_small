#include <kipr/botball.h> 
#include <main_functions.h>
#include <threads.h>
#include <variables.h>
#include <run_sections.h>
#include <filter.h>
#include <Tyler_gyro.h>
//This file was made by Tyler Maenza, Jacob Ross and with help from multiple coders.

void stop_1(){
    move(0,0);
    msleep(60);

}

//main rarely changing functions (driving, arm movement etc.)
//
void servo(int port, int position, int speed){   // Recommend "speed" to be 1-3. Would not advise higher than 4.
    enable_servo(port);
    int current = get_servo_position(port);
    if(position > 2047){position = 2047;} if(position < 0){position = 0;}   // Fail-safe in case of user error.
    while(current <= position-speed || current >= position+speed){   // Value of "speed" alters servo speed and margin of error.
        if(current < position){
            current += speed;
            set_servo_position(port, current);
            msleep(1);
        }
        if(current > position){
            current -= speed;
            set_servo_position(port, current);
            msleep(1);
        }
    }
    set_servo_position(port,position);
    disable_servo(port);
}
//////////////////////////////////////////////////////////////////
/*void slow_arm (int x,int speed)//this funtion slows 
{ 

    enable_servo (lift_arm);
    int desired_position;
    int current_position = get_servo_position(lift_arm);
    if (x > lift_arm_max) {desired_position = lift_arm_max;}
    else if(x < lift_arm_min) {desired_position = lift_arm_min;}
    else {desired_position = x;}
    switch(speed){
        case 1:
            while(current_position <= desired_position-2 || current_position >= desired_position+2)
            {
                if(current_position < desired_position)
                { current_position=current_position +2;
                 set_servo_position(lift_arm, current_position);
                 msleep(1);
                }
                if(current_position > desired_position)
                { current_position=current_position -2;
                 set_servo_position(lift_arm, current_position);

                 msleep(1);
                }
            }
            break;
        case 2:
            while(current_position != desired_position)
            {
                if(current_position < desired_position)
                { current_position=current_position +3;
                 set_servo_position(lift_arm, current_position);
                 msleep(2);
                }
                if(current_position > desired_position)
                { current_position=current_position -3;
                 set_servo_position(lift_arm, current_position);

                 msleep(2);
                }
            }
            break;
    }

    set_servo_position (lift_arm, x);
    msleep(15);
    disable_servo (lift_arm);


}
//////////////////////////////////////////////////////////////////
void slow_claw ( int z, int speed )//this funtion slows hand movements
{ 

    enable_servo (claw);
    int desired_position;
    int current_position = get_servo_position(claw);
    if (z > claw_max) {desired_position = claw_max;}
    else if(z < claw_min) {desired_position = claw_min;}
    else {desired_position = z;}
    switch(speed){
        case 1:
            while(current_position <= desired_position-2 || current_position >= desired_position+2)
            {
                if(current_position < desired_position)
                { current_position=current_position +1;
                 set_servo_position(claw, current_position);
                 msleep(1);

                }
                if(current_position > desired_position)
                { current_position=current_position -1;
                 set_servo_position(claw, current_position);
                 msleep(1);

                }
            }
            break;
        case 2:

            while(current_position != desired_position)
            {
                if(current_position < desired_position)
                { current_position=current_position +3;
                 set_servo_position(claw, current_position);
                 msleep(2);
                }
                if(current_position > desired_position)
                { current_position=current_position -3;
                 set_servo_position(claw, current_position);

                 msleep(2);
                }
            }
            break;
    }
    set_servo_position (claw, z);
    msleep(30);
    disable_servo (claw);

    //^^sets the servo to position to counter act final pos error
}
/////////////////////////////////
void slow_finger ( int z, int speed )//this funtion slows hand movements
{ 

    enable_servo (finger);
    int desired_position;
    int current_position = get_servo_position(finger);
    if (z > finger_max) {desired_position = finger_max;}
    else if(z < finger_min) {desired_position = finger_min;}
    else {desired_position = z;}
    switch(speed){
        case 1:
            while(current_position <= desired_position-2 || current_position >= desired_position+2)
            {
                if(current_position < desired_position)
                { current_position=current_position +1;
                 set_servo_position(finger, current_position);
                 msleep(1);

                }
                if(current_position > desired_position)
                { current_position=current_position -1;
                 set_servo_position(finger, current_position);
                 msleep(1);

                }
            }
            break;
        case 2:

            while(current_position != desired_position)
            {
                if(current_position < desired_position)
                { current_position=current_position +3;
                 set_servo_position(finger, current_position);
                 msleep(2);
                }
                if(current_position > desired_position)
                { current_position=current_position -3;
                 set_servo_position(finger, current_position);

                 msleep(2);
                }
            }
            break;
    }
    set_servo_position (finger, z);
    msleep(30);
    disable_servo (finger);

    //^^sets the servo to position to counter act final pos error
}*/
////////////////////////////////////////////////////////////////
void a_cel(){
    float L_speed;
    float curr_time = seconds(); 
    float init_time = seconds();
    while( (curr_time - init_time) < .2 ){
        curr_time = seconds();   
        L_speed = 6.75 * ((curr_time - init_time) * 1000);
        move(L_speed,L_speed); 
    }
}

//acceleration and deceleration for the perfected Drive function
void de_cel(){


    cmpc(left_motor);
    cmpc(right_motor);
    while(gmpc(left_motor) < 500){

        int R_speed = 2.4 * (500 - gmpc(right_motor) + 150);
        int L_speed = 2.4 * (500 - gmpc(left_motor) + 150);
        move(L_speed,R_speed);

    }
    move(0,0);
}
//////////////////////////////////////////////////////////////////
int speed;
int distance;
float add_fact = 1.920137e-16;
float mult_fact = 0.00004470956;

double theta = 0;
void Drive(int desired,int speed){
    //calibrate_gyro();
    float max_speed = 0;
    cmpc(left_motor);
    cmpc(right_motor);
    if(desired > 0 ){
        a_cel();
        if(desired < speed){
            speed = desired;   
        }
        while( gmpc ( left_motor ) < ( desired - 500 )){
            if( speed > 0 ){
                motor( right_motor,  (( speed - speed * (add_fact + mult_fact * theta))));
                motor( left_motor, (( speed + speed * (add_fact + mult_fact * theta))));
            }
            else{
                motor( right_motor,  (( speed + speed * (add_fact + mult_fact * theta))));
                motor( left_motor,  (( speed - speed * (add_fact + mult_fact * theta))));
            }
            msleep(10);
            theta += ( gyro_z() - bias) * 10;
            (speed + speed * (add_fact + mult_fact * theta)) > max_speed ? max_speed=(speed + speed * (add_fact + mult_fact * theta)) : msleep(1);
        }
        if ( desired > 500 ){
            de_cel();
            printf("%f",max_speed);
            move(0,0);
        }
        else{
            stop_1();   
        }
    }
    else if (desired < 0){
        while( gmpc ( left_motor ) > desired ){
            if( speed > 0 ){
                motor( right_motor,  (( speed - speed * (add_fact + mult_fact * theta))));
                motor( left_motor, (( speed + speed * (add_fact + mult_fact * theta))));
            }
            else{
                motor( right_motor,  (( speed + speed * (add_fact + mult_fact * theta))));
                motor( left_motor,  (( speed - speed * (add_fact + mult_fact * theta))));
            }
            msleep(10);
            theta += ( gyro_z() - bias) * 10;
            (speed + speed * (add_fact + mult_fact * theta)) > max_speed ? max_speed=(speed + speed * (add_fact + mult_fact * theta)) : msleep(1);
        }   
    }
}
//////////////////////////////////////////////////////////////////
void move(int l_speed,int r_speed){//basic moving function thats based off mav



    mav(right_motor,r_speed);
    mav(left_motor,l_speed);

}
//////////////////////////////////////////////////////////////////
int white = 1;
int black = 2;
int physical = 3;
float LIR;
float RIR;
double bias = 0.0;
void square_up(int ending,int speed){
    if(speed > 0 && speed < 600){
        black_speed = speed;
    }
    else{black_speed = 0.25*speed;}
    if(ending == 1 || ending == 2){
        while(1){
            if(analog(left_IR)<analog_white && analog(right_IR)<analog_white){
                move(speed,speed);
            }
            if(analog(right_IR)>analog_white){
                move(speed,(speed*(-.25)));
            }
            if(analog(left_IR)>analog_white){
                move((speed*(-.25)),speed);
            }
            if(analog(left_IR)>analog_white && analog(right_IR)>analog_white) {
                move(stop,stop);
                break;
            }
        }
    }
   
    switch(ending){
        /*case 3:
            {
                while(1){
                    if(digital(digital_right)==0 && digital(digital_left)==0){
                        move(speed,speed);
                    }
                    if(digital(digital_right)==1){
                        move(speed,stop);
                    }
                    if(digital(digital_left)==1){
                        move(stop,speed);
                    }
                    if(digital(digital_right)==1 && digital(digital_left)==1){
                        move(stop,stop);
                        break;
                    }
                }
            }
        case 1:
            {
                while(1){
                    if(analog(left_IR)>analog_white && analog(right_IR)>analog_white){
                        move(black_speed,black_speed);
                    }
                    if(analog(left_IR)<analog_white){
                        move(stop,black_speed);
                    }
                    if(analog(right_IR)<analog_white){
                        move(black_speed,stop);
                    }
                    if(analog(left_IR)<analog_white && analog(right_IR)<analog_white){
                        move(stop,stop);
                        break;
                    }
                }
            }*/
        case 2:
            {
                while(1){
                    if(analog(left_IR)>analog_white && analog(right_IR)>analog_white){
                        move(-1*black_speed,-1*black_speed);
                    }
                    if(analog(left_IR)<analog_white){
                        move(stop,-1*black_speed);
                    }
                    if(analog(right_IR)<analog_white){
                        move(-1*black_speed,stop);
                    }
                    if(analog(left_IR)<analog_white && analog(right_IR)<analog_white){
                        move(stop,stop);
                        break;
                    }
                }
            }
    }
}
//////////////////////////////////////////////////////////////////
double calibrate_gyro(){//gyro calibration through finding gyro setting it to zero then setting theta as that value
    int i = 0;
    double avg = 0;
    while( i < 50){
        avg += gyro_z();
        msleep(1);
        i++;
        //printf("Gyro Z: %d\n",gyro_z());
        //printf("%d\n,%d\n,%d\n",gyro_x(),gyro_y(),gyro_z());
    }
    bias = avg / 50.0;
    printf("New Bias: %f\n", bias);
    return bias;
}
//////////////////////////////////////////////////////////////////
void drive_with_gyro(int speed, double time){//gyro using clock time not distance(much more inaccurate)
    //calibrate_gyro();
    double startTime = seconds();
    double theta = 0;
    while(seconds() - startTime < time){
        calibrate_gyro();
        if (theta < 1000 && theta > -1000){
            mav(right_motor, speed);
            mav(left_motor, speed);
        }
        else if (theta < 1000){
            mav(right_motor, speed + 100);
            mav(left_motor, speed - 100);
        }
        else{
            mav(right_motor, speed - 100);
            mav(left_motor, speed + 100);
        }
        msleep(10);
        theta += (gyro_z() - bias) * 10;
        printf("%f",theta);
    }
    ao();
}
//////////////////////////////////////////////////////////////////
void PID_gyro_drive(int speed, double time){//same thing dont know why there are two versions
    //calibrate_gyro();
    double startTime = seconds();
    double theta = 0;
    while((seconds() - startTime) < time){
        if(speed > 0){
            mav(right_motor, (speed - (speed * (theta/100000))));            
            mav(left_motor, (speed + (speed * theta/100000)));
        }


        else{
            mav(left_motor, (speed - (speed * theta/100000)));            
            mav(right_motor, (speed + (speed * (theta/100000))));
        }
        msleep(10);
        theta += (gyro_z() - bias) * 10;
    }
    move(0,0);
}
//////////////////////////////////////////////////////////////////
void turn_with_gyro(int speed, int deg){//turning using the gyro we use calibrate still to find zero then set theta to a know value instead of 0
    //calibrate_gyro();
    double theta = 0;

    int targetTheta; 
    switch(deg){
        case 45:
            targetTheta = target_theta_45;
            move(speed,speed*-1);
            break;
        case 90:
            //printf("we are running this");
            targetTheta = target_theta_90;
            move(speed,speed*-1);
            break;
        case 180:
            targetTheta = target_theta_180;
            move(speed,speed*-1);
            break;
        case -45:
            targetTheta = target_theta_m45;
            move(speed*-1,speed);
            break;
        case -90:
            targetTheta = target_theta_m90;
            move(speed*-1,speed);
            break;
        case -180:
            targetTheta = target_theta_m180;
            move(speed*-1,speed);
            break;
        default:
            targetTheta = 0;
            break;
    }  
    while(theta < targetTheta){
        msleep(10);
        theta += abs(gyro_z() - bias) * 10;
        printf("Turn Gyro Z: %d\n",gyro_z());
    }
    mav(right_motor, 0);
    mav(left_motor, 0);
    
}
//////////////////////////////////////////////////////////////////
/*void backward_linefollow(int distance)//basic backwards linefollow
{
    cmpc(1);
    cmpc(2);
    while(gmpc(1)<distance)
    {
        mav(left_motor,.55*(analog(front_IR)));
        mav(right_motor,.55*(3400-analog(front_IR)));
    }
    ao();
}*/
//////////////////////////////////////////////////////////////////
/*void PID_gyro_drive_distance(int speed,int distance)//PID drive for distance(ET) instead of time much more accurate
{
    calibrate_gyro();
    double theta = 0;
    while(buffer(ET)< (distance-30) || buffer(ET)>(distance + 30))
    {
        if(buffer(ET) < distance)
        {
            mav(right_motor, (speed - (speed * (theta/100000))));            
            mav(left_motor, (speed + (speed * theta/100000)));
        }
        else
        {
            mav(right_motor, -200);            
            mav(left_motor,-200);
        }
        msleep(10);
        printf("%d/n",buffer(ET));
        theta += (gyro_z() - bias) * 10;
    }
    move(0,0);
}*/
//////////////////////////////////////////////////////////////////
void starting_pos(){
   enable_servo(claw);
    enable_servo(arm);
    servo(arm,arm_min,3);
    servo(claw,claw_max,3);


}

void move_time(int time){

    float elapsed_time;
    float init_time = seconds();

    while(elapsed_time < time){

        gyro();

        mav(right_motor,currentR);
        mav(left_motor,currentL);
        elapsed_time = seconds() - init_time;
    }

}
void work_here(){
//void servo(int port, int position, int speed)
servo(claw,claw_max,3);
    servo(claw,(claw_max-900),3);
}
