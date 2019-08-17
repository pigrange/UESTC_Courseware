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
`define ADD 3'b000
`define SUB 3'b100
`define AND 3'b001
`define  OR 3'b101
`define XOR 3'b010
`define LUI 3'b110

module ALU(
	input [31:0] A, B,
	input [2:0] ALU_operation,
	output reg [31:0] Result,
	output Zero
    );
	always @(A or B or ALU_operation) 
	begin
	 	case (ALU_operation)
			`ADD :Result = A+B;
			`SUB :Result = A-B;
			`AND :Result = A&B;	
			 default: 
		 endcase
	assign Zero = ~|Result;
endmodule
