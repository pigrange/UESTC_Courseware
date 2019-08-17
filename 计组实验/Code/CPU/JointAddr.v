`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:47:26 06/22/2019 
// Design Name: 
// Module Name:    JointAddr 
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
module Joint_Addr(

	input [31:0]PC,
	input [31:0]Instruction,
	output [31:0]O
    );
	 
	 assign O = { PC[31:28], Instruction[25:0], 2'b00}; 


endmodule
