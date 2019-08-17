`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    16:10:41 06/28/2019 
// Design Name: 
// Module Name:    Extender 
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
module Extender(
    input [15:0] a,
	 input ExtOP,
	 output [31:0] b
	 );
	assign b = ExtOP ? {a[15]? 16'hffff: 16'h0, a}:{a[15]? 16'h0000: 16'h0, a};
endmodule
