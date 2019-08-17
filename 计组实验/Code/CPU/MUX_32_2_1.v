`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:05:20 06/22/2019 
// Design Name: 
// Module Name:    MUX_32_2_1 
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
module MUX32_2_1(
	input [31:0] A, B,
	input sel,
	output [31:0] O
    );
	assign O = sel? B: A;
endmodule
