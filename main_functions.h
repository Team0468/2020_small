//for any functions in here reference the .c for the actual function guts...
int min_accel_x;
int max_accel_y;
//used for reading accelerometer^^^
void stop_1();
/*(void slow_arm (int x,int speed);
	void slow_claw ( int z, int speed );
	void slow_finger ( int z, int speed );*/
//slowed down versions of set servo^^^
void servo(int port, int position, int speed);
void move(int l_speed,int r_speed);

//basic move function using mav^^^
int extraction();
int white;
int black;
float RIR;
float LIR;
int physical;
int black_speed;
void square_up(int ending,int speed);
//square up function and integers^^^

double bias;
float add_fact;
float mult_fact;
double calibrate_gyro();
int i;
double avg ;
//gyro calibrate(only use once at the begginning of code)^^^

void drive_with_gyro(int speed, double time);//{
//calibrate_gyro();
double startTime;
double theta;
//basic drive gyro function no accel decel included(reference Drive function)^^^

void PID_gyro_drive(int speed, double time);
//calibrate_gyro();
double startTime;
double theta ;
//another gyro function no clue why this one is here^^^

void turn_with_gyro(int speed, int deg);
//calibrate_gyro();
double theta ;
int targetTheta; 
//base turn gyro function^^^

void backward_linefollow(int distance);
//just a linefollow

void PID_gyro_drive_distance(int speed, int distance);
//running the PID drive function but based off tick count instead of time


void Drive(int desired,int speed);

void a_cel();

void de_cel();
void work_here();
