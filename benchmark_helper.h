#include <time.h>
#include <math.h>

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

#define GET_TIME_95(context) ({ \
    double time[100]; \
    double time_sum = 0.0, power_sum = 0.0, average = 0.0, SD = 0.0, num; \
    for(int i =0; i<100; ++i){ \
        time[i] = GET_TIME(context); \
        time_sum += time[i]; \
        power_sum += pow(time[i], 2); \
    } \
    average = time_sum / 100; \
    SD = sqrt(power_sum / 100 - pow(average, 2)); \
    time_sum = 0, num = 100; \
    for(int i=0; i<100; ++i) { \
        if (time[i] > (average - 1.645 * SD) && time[i] < (average + 1.645 * SD)) \
            time_sum += time[i]; \
        else \
            --num; \
    } \
    time_sum / num; \
})

#define PRINT_TIME_95(format, context) do {\
        double time = GET_TIME_95(context); \
        printf(format, time); \
    }while(0)
