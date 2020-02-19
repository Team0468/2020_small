#ifndef __VARIABLES_h__
#define __VARIABLES_h__
#define right_motor 1
#define left_motor 2
#define claw 1
#define arm 2
#define target_theta_45 277750 //numbers for wallaby-4188
#define target_theta_90 555500
#define target_theta_180 1061500

int target_theta_m45;
int target_theta_m90;
int target_theta_m180;


thread af_zero,af_one,af_two,af_three,af_three,af_four,af_five;

int filt_distribute;
float filter_out[6];
const int a_filter_ports[6];
void moving_win();
void csf_threads();
void kf_threads();
	float baseL;
    float baseR;
    int base ;
void starting_pos();
int stop;
int right_IR;
int left_IR;
int slow;
int fast;
int digital_right;
int digital_left;
int black_speed;
int analog_white;
int arm_max;
int arm_block;
int arm_bigblock;
int claw_max;
int drive;
int square;
int turn;
int target_theta;
\
int speed_l;
int speed_r;
////////////////////////////////////////////////////////////////////////
#define arm_min 0 //placeholder number                           //
#define claw_min 450                                                //
                                                                      //
////////////////////////////////////////////////////////////////////////
#endif