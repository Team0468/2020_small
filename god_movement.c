#include <stdio.h>
#include <stdarg.h>
#include <kipr/botball.h> 
#include <main_functions.h>
#include <threads.h>
#include <variables.h>
#include <run_sections.h>
void move1(const char* pointer, ...)
{
    va_list mov_type;
    va_start(mov_type, pointer);

    while (*pointer != '\0') 
    {
        if (*pointer == 'd' || *pointer == 'D') 
        {
            int drive_type = va_arg( mov_type, int);
            ++pointer;
            int var1 = va_arg(mov_type, int );
            ++pointer;
            int var2 = va_arg( mov_type, int );
            switch(drive_type)
            {
                case 1:
                    {
                        Drive(var1,var2);
                        //DRIVE(var1, var2);
                    }
                case 2:
                    {
                        square_up(var1,var2);
                        //SQUARE_UP(var1, var2);
                    }
                case 3:
                    {
                        turn_with_gyro(var1,var2);
                        //TURN(var1, var2);
                    }
            }

            //DRIVE
            //SQUARE_UP
            //TURN

        }
        va_end(mov_type);

    }
}