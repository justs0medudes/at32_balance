#include "time_utils.h"

#include <sys_delay.h>

void _delay(unsigned long ms){
    delay_ms(ms);
}


unsigned long _micros(){
    return micros();
}
