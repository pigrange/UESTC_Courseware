`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:01:10 06/15/2019 
// Design Name: 
// Module Name:    Control_Unit 
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
module Control_Unit(
	input [5:0] op, func,
	output RegDst, RegWrite, ALUSrc,
	output MemWrite,MemtoReg,
	output Branch,Jump,ExtOP,
	output [2:0] ALU_ctr);

	wire [2:0] ALU_op1;
	wire [2:0] ALU_op2;
	wire R_type;

	Control U0(.op(op),.RegDst(RegDst),.RegWrite(RegWrite),
		.ALUSrc(ALUSrc),.MemWrite(MemWrite),.MemtoReg(MemtoReg),
		.Branch(Branch),.Jump(Jump),.ExtOP(ExtOP),.ALU_op(ALU_op1),
		.R_type(R_type));
		
	ALUop U1(.func(func),.ALU_op(ALU_op2));
	
	assign ALU_ctr = R_type? ALU_op2:ALU_op1;

endmodule
