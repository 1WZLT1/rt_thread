#ifndef __rtthread_h

#include <rtdef.h>
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

#endif

