#include <kipr/botball.h> 
#include <main_functions.h>
#include <threads.h>
#include <variables.h>
#include <run_sections.h>
#include <filter.h>
#include <Tyler_gyro.h>
int main()
{
    
    calibrate_gyro();
    
    //csf_threads();
  
    /*int n;
    while( n < 4){
        turn_with_gyro(600,-90);
        stop_1();
        n = n +1;
    }*/
   //turn_with_gyro(800,90);
    //diagnostics();
    starting_pos();
    extraction();
    
    return 0;
}
