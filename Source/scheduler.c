#include <scheduler.h>

rt_list_t rt_thread_priority_table[RT_THREAD_PRIORITY_MAX];
rt_thread *rt_current_thread;

/*(type *)0 �൱�ھ��ǰ�0 ���ɵ�ַȥת��*/
#define rt_container_of(ptr, type, member) \
					((type *)((char *)(ptr) - (unsigned long)(&((type *)0)->member)))

#define rt_list_entry(node, type, member)  \
					rt_container_of(node, type, member)

/*
 * @brief rt_system_scheduler_init ��������ʼ��
*/

void rt_system_scheduler_init()
{
	register rt_base_t offset;
	
	for(offset = 0;offset < RT_THREAD_PRIORITY_MAX; offset++)
	{
			rt_list_init(&rt_thread_priority_table[offset]);
	}
}

extern void rt_hw_context_switch_to(rt_uint32_t);
void rt_system_scheduler_start()
{
	 register rt_thread *to_thread;
	
	 /*��һ���̶߳�Ӧ�Ĵ����ĵ�ַ*/
   to_thread = rt_list_entry(rt_thread_priority_table[0].next,\
                             rt_thread,\
                             tlist);
	
	  rt_current_thread = to_thread;

		rt_hw_context_switch_to((rt_uint32_t)&to_thread->sp);
}

rt_thread rt_thread_test;
rt_uint8_t rt_thread_test_stack[1024];/*bss�����ڴ���Ϊ�߳�ջ*/
void rt_thread_test_funtion(void *parameter)
{
	while(1)
	{
	
	}
}
int len = 0;
void Test()
{
	rt_system_scheduler_init();//��ʼ�� ͷ�ڵ�ָ���Լ�
	
	rt_thread_init(&rt_thread_test,\
								 &rt_thread_test_funtion,\
								 RT_NULL,\
								 &rt_thread_test_stack[0],\
								 sizeof(rt_thread_test_stack)\
								 );
	/*
				rt_thread_test�д洢��ֵ����Ҫ
	*/
								 
	rt_list_insert_before(&rt_thread_priority_table[0],&(rt_thread_test.tlist));/*��rt_thread_priority_table����һ�����*/
//	len = lt_list_len_find(&rt_thread_priority_table[0]);
								 
	 rt_system_scheduler_start();
}
