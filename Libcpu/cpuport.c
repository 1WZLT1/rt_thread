#include <cpuport.h>

rt_uint32_t rt_interrupt_to_thread;
rt_uint32_t rt_interrupt_from_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;

/*
 *@brief  rt_hw_stack_init 栈区初始化  
 *@param  tentry           函数入口
 *@param  parameter        形参
 *@param  stack_addr       按照4字节向下衍生找到第一个数据的首地址
 *@intepret 主要就是对栈区做一个8字节对齐 然后对寄存器做一个初始化 
*/
rt_uint8_t *rt_hw_stack_init(void       *tentry,
                             void       *parameter,
                             rt_uint8_t *stack_addr)
{
		struct stack_frame *stack_frame;
    rt_uint8_t         *stk;
    unsigned long       i;

    /* 获取栈顶指针
    rt_hw_stack_init 在调用的时候，传给stack_addr的是(栈顶指针) 线程初始化申请的栈区地址*/
    stk  = stack_addr + sizeof(rt_uint32_t);

    /* 让stk指针向下8字节对齐 */
    stk  = (rt_uint8_t *)RT_ALIGN_DOWN((rt_uint32_t)stk, 8);

    /* stk指针继续向下移动sizeof(struct stack_frame)个偏移 */
    stk -= sizeof(struct stack_frame);

    /* 将stk指针强制转化为stack_frame类型后存到stack_frame */
    stack_frame = (struct stack_frame *)stk;

    /* 以stack_frame为起始地址，将栈空间里面的sizeof(struct stack_frame)
    个内存初始化为0xdeadbeef */
    for (i = 0; i < sizeof(struct stack_frame) / sizeof(rt_uint32_t); i ++)
    {
            ((rt_uint32_t *)stack_frame)[i] = 0xdeadbeef;
    }

    /* 初始化异常发生时自动保存的寄存器 */
    stack_frame->exception_stack_frame.r0  = (unsigned long)parameter; /* r0 : argument 存储线程形参*/
    stack_frame->exception_stack_frame.r1  = 0;                        /* r1 */
    stack_frame->exception_stack_frame.r2  = 0;                        /* r2 */
    stack_frame->exception_stack_frame.r3  = 0;                        /* r3 */
    stack_frame->exception_stack_frame.r12 = 0;                        /* r12 */
    stack_frame->exception_stack_frame.lr  = 0;                        /* lr */
    stack_frame->exception_stack_frame.pc  = (unsigned long)tentry;    /* entry point, pc 函数入口*/
    stack_frame->exception_stack_frame.psr = 0x01000000L;              /* PSR */

    /* 返回线程栈指针 */
    return stk;                                                    
}

