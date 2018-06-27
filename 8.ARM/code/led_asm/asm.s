
.text
.globl _start
_start:
	nop
loop:
	#LED3  GPX1_0 亮
	ldr r0,=0x11000c20			@准备地址
	ldr r1,[r0]					@读取片上外设寄存器值到cpu
	bic r1,r1,#0x0000000f		@对应位清零
	orr r1,r1,#0x00000001		@设置对应值
	str r1,[r0]					@写回到片上外设 寄存器

	ldr r0,=0x11000c24
	ldr r1,[r0]
	orr r1,r1,#0b00000001
	str r1,[r0]

	#延时
	bl asm_delay

	#LED3  GPX1_0 灭
	ldr r0,=0x11000c20			@准备地址
	ldr r1,[r0]					@读取片上外设寄存器值到cpu
	bic r1,r1,#0x0000000f		@对应位清零
	#orr r1,r1,#0x00000001		@设置对应值
	str r1,[r0]					@写回到片上外设 寄存器

	ldr r0,=0x11000c24
	ldr r1,[r0]
	bic r1,r1,#0b00000001
	str r1,[r0]

	bl asm_delay

	#LED4 GPF3_4
	ldr r0,=0x114001E0			@准备地址
	ldr r1,[r0]					@读取片上外设寄存器值到cpu
	bic r1,r1,#0x000F0000		@对应位清零
	orr r1,r1,#0x00010000		@设置对应值
	str r1,[r0]					@写回到片上外设 寄存器

	ldr r0,=0x114001E4
	ldr r1,[r0]
	orr r1,r1,#0b00010000
	str r1,[r0]


	#LED5 GPF3_5
	ldr r0,=0x114001E0			@准备地址
	ldr r1,[r0]					@读取片上外设寄存器值到cpu
	bic r1,r1,#0x00F00000		@对应位清零
	orr r1,r1,#0x00100000		@设置对应值
	str r1,[r0]					@写回到片上外设 寄存器

	ldr r0,=0x114001E4
	ldr r1,[r0]
	orr r1,r1,#0b00100000
	str r1,[r0]


	b loop;


_stop:
	b _stop


a:
	.word



