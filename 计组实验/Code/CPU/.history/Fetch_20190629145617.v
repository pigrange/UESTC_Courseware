`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:05:37 06/15/2019 
// Design Name: 
// Module Name:    Fetch 
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
module Fetch(
	input Reset,Clock,Jump,Branch,Zero,
	input [31:0] br_imm,Instruction,
	output [31:0]addr);
	 
	wire[31:0] pc_plus4,br_imm_ext,br_addr_extra,br_addr_result,jump_addr_result,next_pc;	
	wire [1:0] select;
	
   assign select = (Jump) ?  2'b10 :(Branch & Zero) ?  2'b01 : 2'b00;//选择信号
   
	Left_2_Shifter Left2Shifter(br_imm, br_addr_extra);//br_imm_ext乘4变成地址
	
	ADD32 PCAdder(4,addr,pc_plus4);//pc + 4得到下一条
	
	ADD32 BrachAddrGetter(pc_plus4,br_addr_extra,br_addr_result);//执行pc + 4 + imm * 4得到Brach指令的地址
	
	Joint_Addr JumpAddrGetter (addr,Instruction,jump_addr_result);//执行PC高四位和Ins的低26位相加获取Jump指令的地址
	
	MUX32_4_1 NextPcGetter(pc_plus4,br_addr_result,jump_addr_result,32'h0,select,next_pc);//选择执行哪一种指令，select=11的情况不存在
	
	PC PC(Clock,Reset,next_pc,addr);//PC的输出模块

endmodule
