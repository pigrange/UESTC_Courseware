`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:11:31 06/15/2019 
// Design Name: 
// Module Name:    ADD32 
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
module ADD32(
	input [31:0] A,
   input [31:0] B,
   output [31:0] C
    );
	assign C = A + B;

endmodule
