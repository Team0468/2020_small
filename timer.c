float init_time;//put these floats as global variables
float elapsed;
int timer_reset()//put this above the while loop
{
    init_time=seconds();
}
int time_calc()//put this at the end of the while loop ex.  while(){ your_code time_calc}
{
    elapsed = seconds()-init_time;
    return elapsed;
}