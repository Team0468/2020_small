#include <kipr/botball.h> 
#include <main_functions.h>
#include <threads.h>
#include <variables.h>
#include <run_sections.h>

int target_theta_m45 = target_theta_45;
int target_theta_m90 = target_theta_90;
int target_theta_m180 = target_theta_180;
int arm_max = arm_min + 1222;
int arm_block = arm_min + 550;
int arm_bigblock = arm_min + 730;
int claw_max = claw_min + 800;
int left_IR = 2;
int right_IR = 1;
int slow = 1;
int fast = 3;
int stop = 0;
int digital_right = 1;
int digital_left = 2;
int analog_white = 2000;
int drive = 1;
int square = 2;
int turn = 3;
//where global variables will be held