#include <rtthread.h>

/*
 * @brief  rt_list_init 链表初始化
 * @parame rt_list_t    指向链表
*/
rt_inline void rt_list_init(rt_list_t *l)
{
    l->next = l->prev = l;
}

/*
 * @brief rt_list_insert_before 双链表尾插|线程插入
 * @param l                     头结点
 * @param n                     新结点
*/
inline void rt_list_insert_before(rt_list_t *l, rt_list_t *n)
{
		l->next       = n;
		n->prev       = l->prev;
		n->next       = l;
		l->prev       = n;
}

/*
 * @brief lt_list_len_find 线程长度查询
 * @param l                头结点
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
 * @brief  rt_thread_init     线程初始化
 * @return                    线程初始化是否成功
 * @parame rt_thread *thread  线程对应指针
 * @parame entry              线程对应函数
 * @parame parameter          线程形参
 * @parame stack_start        栈区起始地址
 * @intepret                  对线程初始化
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
                                          (void *)((char *)thread->stack_addr + thread->stack_size - 4));/*获取栈顶元素的首地址*/
		
		return RT_EOK;
}

