#include <kipr/botball.h>
#include <filter.h>
thread af_zero,af_one,af_two,af_three,af_three,af_four,af_five;
int filt_distribute=0;
float filter_out[6];

const int a_filter_ports[6]={0,1,1,0,0,0};

void moving_win(){
    int port = filt_distribute;
    filt_distribute++;
    int length = 40;
    if(length < 20){length=20;}//if length is lower than min allowed, set to min
    if(length > 100){length=100;}//if length is higher the max allowed, set to max
    int pos,i;
    float total,average,win[length];
    while(1){
        win[pos]=analog(port);
        i=0;
        total=0;
        while(i<length){
            total=total+win[i];
            i++;
        }
        average=total/length;
        pos++;
        if(pos>=length){pos=0;}//reset pos when it reaches length
        filter_out[port]=average;//"return" the average of the total stored data
    }
}
void csf_threads(){
    af_zero=thread_create(moving_win);
    af_one=thread_create(moving_win);
    af_two=thread_create(moving_win);
    af_three=thread_create(moving_win);
    af_four=thread_create(moving_win);
    af_five=thread_create(moving_win);
   	//create all filter threads
    if(a_filter_ports[0]){thread_start(af_zero);msleep(50);}else{filt_distribute++;}
    if(a_filter_ports[1]){thread_start(af_one);msleep(50);}else{filt_distribute++;}
    if(a_filter_ports[2]){thread_start(af_two);msleep(50);}else{filt_distribute++;}
    if(a_filter_ports[3]){thread_start(af_three);msleep(50);}else{filt_distribute++;}
    if(a_filter_ports[4]){thread_start(af_four);msleep(50);}else{filt_distribute++;}
    if(a_filter_ports[5]){thread_start(af_five);msleep(50);}else{filt_distribute++;}
    //start selected threads
}
void kf_threads(){
    if(a_filter_ports[0]){thread_destroy(af_zero);}
    if(a_filter_ports[1]){thread_destroy(af_one);}
    if(a_filter_ports[2]){thread_destroy(af_two);}
    if(a_filter_ports[3]){thread_destroy(af_three);}
    if(a_filter_ports[4]){thread_destroy(af_four);}
    if(a_filter_ports[5]){thread_destroy(af_five);}
}
