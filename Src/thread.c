#include <rtthread.h>

/*
 * @brief  rt_list_init �����ʼ��
 * @parame rt_list_t    ָ������
*/
rt_inline void rt_list_init(rt_list_t *l)
{
    l->next = l->prev = l;
}

/*
 * @brief rt_list_insert_before ˫����β��|�̲߳���
 * @param l                     ͷ���
 * @param n                     �½��
*/
inline void rt_list_insert_before(rt_list_t *l, rt_list_t *n)
{
		l->next       = n;
		n->prev       = l->prev;
		n->next       = l;
		l->prev       = n;
}

/*
 * @brief lt_list_len_find �̳߳��Ȳ�ѯ
 * @param l                ͷ���
*/
inline int lt_list_len_find(rt_list_t *l)
{	
	rt_list_t *a;
	int len = 0;
	a = l;
	
	if(l->next == RT_NULL)return 10;
	
	while(a->next != l)
	{
		len += 1;
		a = a->next;
	}
	
	return len;
}	

/*
 * @brief  rt_thread_init     �̳߳�ʼ��
 * @return                    �̳߳�ʼ���Ƿ�ɹ�
 * @parame rt_thread *thread  �̶߳�Ӧָ��
 * @parame entry              �̶߳�Ӧ����
 * @parame parameter          �߳��β�
 * @parame stack_start        ջ����ʼ��ַ
 * @intepret                  ���̳߳�ʼ��
*/
rt_err_t rt_thread_init(rt_thread *thread,\
												void (*entry)(void *parameter),\
												void 	*parameter,\
												void  *stack_start,\
												rt_uint32_t  stack_size
                        )
                 
{
		RT_ASSERT(thread      != RT_NULL);
		RT_ASSERT(stack_start != RT_NULL);
		RT_ASSERT(entry       != RT_NULL);
	
		rt_list_init(&thread->tlist);
		thread->entry      = (void *)entry;
		thread->parameter  = parameter;
		thread->stack_addr = stack_start;
		thread->stack_size = stack_size;
	
		thread->sp = (void *)rt_hw_stack_init(thread->entry,
																					thread->parameter,
                                          (void *)((char *)thread->stack_addr + thread->stack_size - 4));/*��ȡջ��Ԫ�ص��׵�ַ*/
		
		return RT_EOK;
}

