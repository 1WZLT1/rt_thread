#ifndef __rtthread_h

#include <rtdef.h>
#include <rttype.h>
#include <cpuport.h>

#ifdef RT_DEBUGING_ASSERT
void rt_assert_handler(const char *ex, const char *func, rt_size_t line);
#define RT_ASSERT(EX)                                                         \
if (!(EX))                                                                    \
{                                                                             \
    rt_assert_handler(#EX, __FUNCTION__, __LINE__);                           \
}
#else
#define RT_ASSERT(EX)
#endif /* RT_DEBUGING_ASSERT */


rt_err_t rt_thread_init(rt_thread *thread,\
												void (*entry)(void *parameter),\
												void 	*parameter,\
												void  *stack_start,\
												rt_uint32_t  stack_size
                        );
void rt_list_insert_before(rt_list_t *l, rt_list_t *n);
int lt_list_len_find(rt_list_t *l);
#endif

