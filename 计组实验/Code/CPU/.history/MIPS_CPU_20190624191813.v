`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:22:01 06/15/2019 
// Design Name: 
// Module Name:    MIPS_CPU 
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
module MIPS_CPU(
	input [31:0]Instruction,
	input Reset, Clock,
	//准备写在CPU寄存器里面的数据
	input [31:0] DataToWd,
	output [31:0] ALU_result, Ext_Imm, addr, Out1,Out2,
	output MemWrite,MemtoReg);
	 
	wire RegDst,RegWrite, ALUSrc, Branch, Zero,Jump;
	wire [2:0] ALU_op;
	wire [4:0] Wn;
	wire[31:0] Out1, Out2, ALU_B;
	
	//取指电路
	Fetch Fetch(Reset,Clock,Jump,Branch,Zero,Ext_Imm,Instruction,addr);
	
	//控制单元
	Control_Unit ControlUnit(.op(Instruction[31:26]), .func(Instruction[5:0]),
	.RegDst(RegDst), .RegWrite(RegWrite), .ALUSrc(ALUSrc),
	.MemWrite(MemWrite), .MemtoReg(MemtoReg),
	.Branch(Branch), .Jump(Jump),.ALU_op(ALU_op));
	
	//Wn处的5位2选一选择器
	MUX5_2_1 MUX5_2_1(Instruction[20:16], Instruction[15:11], RegDst, Wn);
	
	//寄存器堆
	RegFile RegFile(Instruction[25:21], Instruction[20:16], Wn, RegWrite,Clock,DataToWd, Out1, Out2);
	
	//立即数的符号扩展器
	Sign_Extender Sign_Extender(Instruction[15:0], Ext_Imm);
	
	//ALU 前面的32位2选1选择器
	MUX32_2_1 MUX32_2_1(Out2, Ext_Imm, ALUSrc, ALU_B);
	
	//ALU
	ALU ALU(Out1, ALU_B, ALU_op, ALU_result, Zero);
	
endmodule
