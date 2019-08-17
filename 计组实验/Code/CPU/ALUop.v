`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    19:54:19 06/15/2019 
// Design Name: 
// Module Name:    ALUop 
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
module ALUop(
    input [5:0] func,
	output [2:0] ALU_op);
	
	assign ALU_op[0] = 0;
	assign ALU_op[1] = 0;
	assign ALU_op[2] = func[1];
endmodule
