#include <camera.h>// sam and coltons code
#include <kipr/botball.h>
int camera_initialize(){
    camera_open_black();
    int a=0;
    while(a<6){
        camera_update();
        a=a+1;
    }
    return 0;
}
int full_check(int c){ 
    int a=0;
    int b=0;
    while(a<30){  
        camera_update();
        if(get_object_count(c)>0){b=b+1;}
        a=a+1;
    }
    if(b>10){printf("i see color");
             return 1;}
    else{printf("i dont see color");
         return 0;}
}
int camera_center(int color){
    camera_initialize();
    if(full_check(color)==1&&get_object_center_x(color,0)==!0){
        while(1){
            mav(0,18.75*(get_object_center_x(color,0)-80));
            mav(3,18.75*(80-(get_object_center_x(color,0))));
        }
        return 1;
    }
    else{return 0;}
}
int y1,y2,y3,g1,g2,g3,g4,r1,r2,r3,r4 = initial;
int block_check(){
    camera_initialize();
    if (full_check(yellow)==1){}
    else {y1=-1;}
    return 0;
}
int check_thread(int color){  //if function = 0 then its not centered, if it = 1 then it is
    int centered=0;
    camera_initialize();
    while(get_object_center_x(color,0)==!79){
        full_check(color);
        centered=0;
    }
    if(get_object_center_x(color,0)==79){centered=1;}
    if(centered==1){return 1;}
    else{return 0;}
}
