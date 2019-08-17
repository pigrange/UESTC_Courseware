`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:16:38 06/15/2019 
// Design Name: 
// Module Name:    Sign_Extender 
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
module Sign_Extender(
    input [15:0] a,
	 output [31:0] b
	 );
	assign b = {a[15]? 16'hffff: 16'h0, a};

endmodule
