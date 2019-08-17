`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    16:54:33 06/24/2019 
// Design Name: 
// Module Name:    SOC 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////

module SOC(Clock, Reset,
					DISP_Seg, //数码管显示：PC（高2管），ALU运算结果（低4管）
					AN,  		 //数码选择信号
					Test_signal,
					ALU_Result, Ext_imm, addr,Out1,Out2,Instruction,
					MemWr,MemtoReg);
					
	input Clock, Reset;
	output [7:0] DISP_Seg;
	output [5:0] AN;
	
	output [31:0] ALU_Result, Ext_imm, addr,Out1,Out2,Instruction;
	output MemWr,MemtoReg;
	
	output [23:0] Test_signal;
	reg [31:0] ClockNum = 0;
	
	wire MemWr,Step;
	wire [31:0] ALU_Result, Ext_imm,DataToWd,addr,MemOutData;
	
	assign Test_signal = {addr[9:2],ALU_Result[15:0]};
	assign LED0 = Step;
	
	always @(posedge Clock) ClockNum <= ClockNum + 1;
	
	//数码管显示
	Hex7seg_decode seg(Test_signal,ClockNum[2:0],DISP_Seg,AN);
	
	//主存，用来存取数据
	DATA_MEM RAM(Out2,ALU_Result,MemWr,Clock,MemOutData);
	
	//ALU的计算结果或者Ram中读取的值进行二选一，准备输出到寄存器堆的Wd里
	MUX32_2_1 mux1 (ALU_Result, MemOutData,MemtoReg, DataToWd);
								
	//ROM，通过地址从ROM中获取指令							
	INST_ROM ROM(addr,Instruction);
	
	//CPU,第一个参数为指令，第二个参数为是否重设PC，准备写到Wd里面的值
	MIPS_CPU cpu(Instruction,Reset,Clock,DataToWd,
	//ALU计算输出的值，立即数符号扩展的输出值,PC,寄存器读出的out2（datatoMem）
	ALU_Result,Ext_imm,addr,Out1,Out2,
	//MEM的两个信号
	MemWr,MemtoReg);

endmodule
