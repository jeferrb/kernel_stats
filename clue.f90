#define TRACE_POINT(NAME) CALL log_event(NAME, mype)

CALL start_file(mype)

TRACE_POINT("mainIteration_start")