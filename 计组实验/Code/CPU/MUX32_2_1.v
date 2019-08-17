`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:09:38 06/15/2019 
// Design Name: 
// Module Name:    MUX32_2_1 
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
module MUX32_4_1(
	 input [31:0]A,B,C,D
    input [1:0]select,
    output [31:0]out
    );
	assign out = (Sel == 2'b00) ? A : 
					 (Sel == 2'b01) ? B : 
					 (Sel == 2'b10) ? C : D;

endmodule
