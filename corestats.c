#include "corestats.h"

#include <string.h>
#include <stdio.h>

#include "PerfUtils/timetrace_wrapper.h"

pthread_key_t corestats_key; // Store per-thread coreStats struct key
pthread_mutex_t corestats_tid_lock = PTHREAD_MUTEX_INITIALIZER; // For allocating coreStats to each thread
char* coreStatsPrefix;
int corestats_count = 0;
coreStats* corestats;

// Assign numbers to each thread; this lives here instead of threadpool.c
// because multiple copies of threadpool.c are generated and linked together.
pthread_mutex_t threadCounterLock = PTHREAD_MUTEX_INITIALIZER;
int nextThreadId = 1;

void assign_corestats(const char* thread_name) {
    coreStats *coreStat = GET_CORESTATS();
    if (coreStat != NULL) {
        return;
    }
    pthread_mutex_lock(&corestats_tid_lock);
    pthread_setspecific(corestats_key, &corestats[corestats_count]);
    sprintf(corestats[corestats_count].threadName,"%s%s", coreStatsPrefix, thread_name);
    corestats[corestats_count].cpuID = -1;
    fprintf(stderr, "Setup core stats %d to thread %s \n", corestats_count,
            corestats[corestats_count].threadName);
    corestats_count++;
    pthread_mutex_unlock(&corestats_tid_lock);
    log_corestats(); // Record the initial core
}

void log_corestats() {
    coreStats* coreStat = GET_CORESTATS();
    if (coreStat == NULL) { return; }
    int cpuId = sched_getcpu();
    if (cpuId != coreStat->cpuID) {
        timetrace_record("[%s] cpuid: %02d", coreStat->threadName, cpuId);
        coreStat->cpuID = cpuId;
    }
}
