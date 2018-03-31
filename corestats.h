#include <pthread.h>
#include "PerfUtils/timetrace_wrapper.h"


typedef struct {
   char threadName[50];
   int cpuID;
} coreStats;

extern pthread_key_t corestats_key;
extern pthread_mutex_t corestats_tid_lock;
extern int corestats_count;
extern coreStats* corestats;

void assign_corestats(const char* thread_name);
void log_corestats(void);

#define GET_CORESTATS() ((coreStats*)pthread_getspecific(corestats_key))

extern pthread_mutex_t threadCounterLock;
extern int nextThreadId;
extern char* coreStatsPrefix;
