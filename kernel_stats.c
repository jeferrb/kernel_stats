#include "kernel_stats.h"

struct timeval global_init_time, last_start_loop, last_end_loop;
unsigned int max_steps = 1, started = 0;

void init_paramount_monitoring_(const char* id_str, int *id_num){
	gettimeofday(&global_init_time, NULL);
	gettimeofday(&last_end_loop, NULL);
	long int initTime=(global_init_time.tv_sec * 1000000 + global_init_time.tv_usec);
	int id_i = *id_num;
	printf("%s %s id_int: %d id_str: %s initTime: %ld (ms)\n", PREFIX_TIME_MSG, PREFIX_INIT_ITERATION_MSG, id_i, id_str, initTime);
	started=1;
}

void begin_paramount_iteration_(const char* id_str, int *id_num){
	if (!started) init_paramount_monitoring_(id_str, id_num);
	gettimeofday(&last_start_loop, NULL);
	long int deltaInit = (last_start_loop.tv_sec * 1000000 + last_start_loop.tv_usec) - (global_init_time.tv_sec * 1000000 + global_init_time.tv_usec);
	long int deltaTime = (last_start_loop.tv_sec * 1000000 + last_start_loop.tv_usec) - (last_end_loop.tv_sec * 1000000 + last_end_loop.tv_usec);
	int id_i = *id_num;
	printf("%s %s id_int: %d id_str: %s deltaInit: %ld deltaTime: %ld (ms)\n", PREFIX_TIME_MSG, PREFIX_BEGIN_ITERATION_MSG, id_i, id_str, deltaInit, deltaTime);
}

void end_paramount_iteration_(const char* id_str, int *id_num, int *maxsteps){
	gettimeofday(&last_end_loop, NULL);
	long int deltaInit = (last_end_loop.tv_sec * 1000000 + last_end_loop.tv_usec) - (global_init_time.tv_sec * 1000000 + global_init_time.tv_usec);
	long int deltaTime = (last_end_loop.tv_sec * 1000000 + last_end_loop.tv_usec) - (last_start_loop.tv_sec * 1000000 + last_start_loop.tv_usec);
	int id_i = *id_num;
	printf("%s %s id_int: %d id_str: %s deltaInit: %ld deltaTime: %ld (ms)\n", PREFIX_TIME_MSG, PREFIX_END_ITERATION_MSG, id_i, id_str, deltaInit, deltaTime);
	
	int max_steps = *maxsteps;
	if (++max_steps > max_steps)
	{
		printf("%s %s id_int: %d id_str: %s iteration_number: %d\n", PREFIX_TIME_MSG, PREFIX_EXIT_ITERATION_MSG, id_i, id_str, max_steps);
		exit (0);
	}
}

void  print_paramount_current_stats_(const char* id_str, int *id_num){
	int id_i = *id_num;
	struct timeval time_now;
	gettimeofday(&time_now, NULL);
	long int deltaInit = (time_now.tv_sec * 1000000 + time_now.tv_usec) - (global_init_time.tv_sec * 1000000 + global_init_time.tv_usec);
	printf("%s %s id_int: %d id_str: %s deltaInit: %ld (ms)\n", PREFIX_TIME_MSG, PREFIX_PRINT_ITERATION_MSG, id_i, id_str, deltaInit);
}

FILE * GlobalFD = NULL;

void start_file_(uint16_t * processId){
	char buf[256];
	sprintf(buf, "timeTraceOut%d.out", *processId);
	GlobalFD = fopen(buf, "w+");
}

void log_event_(char * pointName, uint16_t * processId){
	struct timeval time_now;
	gettimeofday(&time_now, NULL);
	fprintf(GlobalFD, "%lu,%s,%hu\n", (time_now.tv_sec * 1000000 + time_now.tv_usec), pointName, *processId);
}