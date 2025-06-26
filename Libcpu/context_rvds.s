SCB_VTOR        EQU     0xE000ED08;存储中断向量表地址
NVIC_INT_CTRL   EQU     0xE000ED04;ICSR寄存器对应地址可以触发pendsv中断触发
NVIC_SYSPRI2    EQU     0xE000ED20;设置pendsv 与 sysctick 中断优先级 	
NVIC_PENDSV_PRI EQU     0x00FF0000;pendsv优先级
NVIC_PENDSVSET  EQU     0x10000000 
	
 AREA |.text|, CODE, READONLY, ALIGN=2
 THUMB
 REQUIRE8;八字节对齐
 PRESERVE8
 
 EXPORT rt_hw_context_switch_to
 IMPORT rt_interrupt_to_thread
 IMPORT rt_interrupt_from_thread
 IMPORT rt_thread_switch_interrupt_flag
	
rt_hw_context_switch_to

	LDR r1,=rt_interrupt_to_thread
	STR r0,[r1] ;我理解的是把形参的指给r1 也就是sp指针对应的地址
	
	LDR r1,=rt_interrupt_from_thread;表示其不是第一次进入线程
	MOV r0,#1
	STR r0,[r1]

	LDR r1,=rt_thread_switch_interrupt_flag
	MOV r0,#1
	STR r0,[r1]
	
	LDR r0,=NVIC_SYSPRI2
	LDR r1,=NVIC_PENDSV_PRI
	LDR r2,[r0,#0x00]
	ORR r1,r1,r2
	STR r1,[r0]
	
	LDR r0,=NVIC_INT_CTRL
	LDR r1,=NVIC_PENDSVSET;挂起pendsv
	LDR r1,[r0]
	
	CPSIE   F
	CPSIE   I
	
	ALIGN   4
 END
	
	