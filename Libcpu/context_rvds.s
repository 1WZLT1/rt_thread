SCB_VTOR        EQU     0xE000ED08;�洢�ж��������ַ
NVIC_INT_CTRL   EQU     0xE000ED04;ICSR�Ĵ�����Ӧ��ַ���Դ���pendsv�жϴ���
NVIC_SYSPRI2    EQU     0xE000ED20;����pendsv �� sysctick �ж����ȼ� 	
NVIC_PENDSV_PRI EQU     0x00FF0000;pendsv���ȼ�
NVIC_PENDSVSET  EQU     0x10000000 
	
 AREA |.text|, CODE, READONLY, ALIGN=2
 THUMB
 REQUIRE8;���ֽڶ���
 PRESERVE8
 
 EXPORT rt_hw_context_switch_to
 IMPORT rt_interrupt_to_thread
 IMPORT rt_interrupt_from_thread
 IMPORT rt_thread_switch_interrupt_flag
	
rt_hw_context_switch_to

	LDR r1,=rt_interrupt_to_thread
	STR r0,[r1] ;�������ǰ��βε�ָ��r1 Ҳ����spָ���Ӧ�ĵ�ַ
	
	LDR r1,=rt_interrupt_from_thread;��ʾ�䲻�ǵ�һ�ν����߳�
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
	LDR r1,=NVIC_PENDSVSET;����pendsv
	LDR r1,[r0]
	
	CPSIE   F
	CPSIE   I
	
	ALIGN   4
 END
	
	