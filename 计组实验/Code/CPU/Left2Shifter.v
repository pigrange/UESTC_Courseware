`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:41:35 06/22/2019 
// Design Name: 
// Module Name:    Left2Shifter 
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
module Left_2_Shifter(
	input [31:0] addr,
	output [31:0] addr1
    );

	assign addr1 = { addr[29:0], 2'b00 };
endmodule
