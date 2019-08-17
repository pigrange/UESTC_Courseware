`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:17:51 06/15/2019 
// Design Name: 
// Module Name:    ALU 
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

module ALU(
	input [31:0] A, B,
	input [2:0] ALU_operation,
	output [31:0] Result,
	output Zero
    );
	 // 000 -> addu
	assign Result = (ALU_operation == 3'b000) ? A + B:
	//100 -> subu
	(ALU_operation == 3'b100) ? A - B:
	//001 -> add
	(ALU_operation == 3'b001) ? A & B:
	//101 -> sub
	(ALU_operation == 3'b101) ? A | B:
	//010 -> or
	(ALU_operation == 3'b010) ? A ^ B:
	//110 -> sltu
	(ALU_operation == 3'b110) ? {B[15:0], 16'h0}:32'hxxxxxxxx;
	assign Zero = ~|Result;
endmodule
