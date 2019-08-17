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
	output Branch,Jump,
	output [2:0] ALU_ctr
    );
	wire [1:0] ALUctr;
	Control U0(.op(op),
		.RegDst(RegDst),
		.RegWrite(RegWrite),
		.ALUSrc(ALUSrc),
		.MemWrite(MemWrite),
		.MemtoReg(MemtoReg),
		.Branch(Branch),
		.Jump(Jump),
		.ALUctr(ALUctr)
		);
	ALUop U1(.func(func), .ALUctr(ALUctr), .ALU_op(ALU_ctr));

endmodule
