#include <kipr/botball.h> 
#include <main_functions.h>
#include <threads.h>
#include <variables.h>
#include <run_sections.h>
int main()
{
    
    calibrate_gyro();
   
    //csf_threads();
    //turn_with_gyro(800,90);
    //diagnostics();
    starting_pos();
    shut_down_in(119);
    extraction();
    //water_collect();
   
    //servo(arm,arm_bigblock,fast);
    //servo(claw,claw_min+400,fast);
    //water_collect();
    return 0;
}
