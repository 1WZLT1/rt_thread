#include <cpuport.h>

/*
 *@brief  rt_hw_stack_init ջ����ʼ��  
 *@param  tentry           �������
 *@param  parameter        �β�
 *@param  stack_addr       ����4�ֽ����������ҵ���һ�����ݵ��׵�ַ
 *@intepret ��Ҫ���Ƕ�ջ����һ��8�ֽڶ��� Ȼ��ԼĴ�����һ����ʼ�� 
*/
rt_uint8_t *rt_hw_stack_init(void       *tentry,
                             void       *parameter,
                             rt_uint8_t *stack_addr)
{
		struct stack_frame *stack_frame;
    rt_uint8_t         *stk;
    unsigned long       i;

    /* ��ȡջ��ָ��
    rt_hw_stack_init �ڵ��õ�ʱ�򣬴���stack_addr����(ջ��ָ��)*/
    stk  = stack_addr + sizeof(rt_uint32_t);

    /* ��stkָ������8�ֽڶ��� */
    stk  = (rt_uint8_t *)RT_ALIGN_DOWN((rt_uint32_t)stk, 8);

    /* stkָ����������ƶ�sizeof(struct stack_frame)��ƫ�� */
    stk -= sizeof(struct stack_frame);

    /* ��stkָ��ǿ��ת��Ϊstack_frame���ͺ�浽stack_frame */
    stack_frame = (struct stack_frame *)stk;

    /* ��stack_frameΪ��ʼ��ַ����ջ�ռ������sizeof(struct stack_frame)
    ���ڴ��ʼ��Ϊ0xdeadbeef */
    for (i = 0; i < sizeof(struct stack_frame) / sizeof(rt_uint32_t); i ++)
    {
            ((rt_uint32_t *)stack_frame)[i] = 0xdeadbeef;
    }

    /* ��ʼ���쳣����ʱ�Զ�����ļĴ��� */
    stack_frame->exception_stack_frame.r0  = (unsigned long)parameter; /* r0 : argument */
    stack_frame->exception_stack_frame.r1  = 0;                        /* r1 */
    stack_frame->exception_stack_frame.r2  = 0;                        /* r2 */
    stack_frame->exception_stack_frame.r3  = 0;                        /* r3 */
    stack_frame->exception_stack_frame.r12 = 0;                        /* r12 */
    stack_frame->exception_stack_frame.lr  = 0;                        /* lr */
    stack_frame->exception_stack_frame.pc  = (unsigned long)tentry;    /* entry point, pc */
    stack_frame->exception_stack_frame.psr = 0x01000000L;              /* PSR */

    /* �����߳�ջָ�� */
    return stk;                                                    
}

