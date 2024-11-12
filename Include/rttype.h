#ifndef __rttype_h
#define __rttype_h

#include <rtdef.h>

typedef struct rt_list_node
{
	 struct rt_list_node *next;              /* 指向后一个节点 */
   struct rt_list_node *prev;              /* 指向前一个节点 */	
}rt_list_t;

typedef struct 
{
    void        *sp;               /* 线程栈指针 */
    void        *entry;            /* 线程入口地址 */
    void        *parameter;        /* 线程形参 */
    void        *stack_addr;       /* 线程起始地址 */
    rt_uint32_t stack_size;        /* 线程栈大小，单位为字节 */

    rt_list_t   tlist;             /* 线程链表节点 */
}rt_thread,*rt_thread_t;

#endif 


