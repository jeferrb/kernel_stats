#include "kernel_stats_cpp.h"


struct timeval global_init_time, last_start_loop, last_end_loop;
unsigned int max_steps = 1, started = 0;

void kernel_stats::init_timestep_(){
	
}
void kernel_stats::begin_timestep_(){
	
}

void kernel_stats::end_timestep_(int maxsteps){
	
}
void kernel_stats::print_timestep_(const char* prefix){
	
}

/*
 int main_example(){
 	for (int i = 0; i < 100; ++i)
 	{
 		begin_timestep_();
 		for (int i = 0; i < 100000; ++i)
 		{
 			printf("aslkdfalskdf\n");
 		}
 		end_timestep_(3);
 	}
 	return 0;
 }
*/