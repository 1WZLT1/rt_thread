#ifndef __scheduler_h
#define __scheduler_h

#include <rttype.h>
#include <rtdef.h>
#include <rtthread.h>

void Test(void);

#define RT_THREAD_PRIORITY_MAX 32
extern rt_list_t rt_thread_priority_table[RT_THREAD_PRIORITY_MAX];

#endif


