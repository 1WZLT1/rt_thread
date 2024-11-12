#include <scheduler.h>

rt_list_t rt_thread_priority_table[RT_THREAD_PRIORITY_MAX];

rt_thread rt_thread_test;
rt_uint8_t rt_thread_test_stack[1024];
void rt_thread_test_funtion(void *parameter)
{
	while(1)
	{
	
	}
}
int len = 0;
void Test()
{
	rt_thread_init(&rt_thread_test,\
								 &rt_thread_test_funtion,\
								 RT_NULL,\
								 &rt_thread_test_stack[0],\
								 sizeof(rt_thread_test_stack)\
								 );
								 
	rt_list_insert_before(&rt_thread_priority_table[0],&(rt_thread_test.tlist));
	len = lt_list_len_find(&rt_thread_priority_table[0]);
}
