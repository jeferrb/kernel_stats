/* Measure kernel iterations based on 'Cross-Platform Performance Prediction of
Parallel Applications Using Partial Execution' paper */

#ifndef KERNEL_STATS_H
#define KERNEL_STATS_H 1

#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


#ifndef PREFIX_TIME_MSG
#define PREFIX_TIME_MSG "PARAMOUNT_TIME "
#endif
#ifndef PREFIX_INIT_ITERATION_MSG
#define PREFIX_INIT_ITERATION_MSG "ParamountInitMonitoring "
#endif
#ifndef PREFIX_BEGIN_ITERATION_MSG
#define PREFIX_BEGIN_ITERATION_MSG "ParamountItBegin "
#endif
#ifndef PREFIX_END_ITERATION_MSG
#define PREFIX_END_ITERATION_MSG "ParamountItEnd "
#endif
#ifndef PREFIX_EXIT_ITERATION_MSG
#define PREFIX_EXIT_ITERATION_MSG "ParamountExit "
#endif
#ifndef PREFIX_PRINT_ITERATION_MSG
#define PREFIX_PRINT_ITERATION_MSG "ParamountCurrentStatus "
#endif

#ifdef __cplusplus
class kernel_stats
{
public:
	kernel_stats();
	~kernel_stats();
#endif //__cplusplus
	
	/* This is an optional call to time-stamp the beginning of an execution. For
	applications with large start-up overhead, e.g., due to reading large data sets
	from secondary storage, this call may be used to separate the initialization
	overhead from subsequent regular timesteps */ 
	void init_paramount_iteration_(const char* id_str, int *id_num);

	/* This call identifies the beginning of a timestep and allows counters for
	metrics to be reset between timesteps */ 
	void begin_paramount_iteration_(const char* id_str, int *id_num);

	/* This call indicates the end of a timestep and logs metrics pertinent to the
	timestep work. The parameter maxsteps specifies the total number of timesteps
	before partial execution prematurely terminates the program's execution */
	void end_paramount_iteration_(const char* id_str, int *id_num, int *maxsteps);

	/* This function prints a number and a prefix */
	void  print_paramount_current_stats_(const char* id_str, int *id_num);

	void start_file_(uint16_t * processId);
	void log_event_(char * pointName, uint16_t * processId);

#ifdef __cplusplus

};
#endif //__cplusplus

#endif // KERNEL_STATS_H
