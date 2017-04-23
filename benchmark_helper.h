#include <time.h>

#define CLOCK_ID CLOCK_MONOTONIC_RAW
#define ONE_SEC 1000000000.0


#define __TIMER_INIT__() struct timespec _timer_start = {0, 0}, _timer_end = {0, 0}

#define __TIMER_START__() clock_gettime(CLOCK_ID, &_timer_start)
#define __TIMER_END__() clock_gettime(CLOCK_ID, &_timer_end)
#define __TIMER_GET_TIME__() (double) (_timer_end.tv_sec - _timer_start.tv_sec) + (_timer_end.tv_nsec - _timer_start.tv_nsec) / ONE_SEC
#define __TIMER_PRINT__(format) printf(format, __TIMER_GET_TIME__())




#define GET_TIME(context) ({\
                        __TIMER_INIT__(); \
                        __TIMER_START__(); \
                        context \
                        __TIMER_END__(); \
                        __TIMER_GET_TIME__(); \
                    })


#define PRINT_TIME(format, context) ({\
                        __TIMER_INIT__(); \
                        __TIMER_START__(); \
                        context \
                        __TIMER_END__(); \
                        __TIMER_PRINT__(format); \
                        __TIMER_GET_TIME__(); \
                    })


