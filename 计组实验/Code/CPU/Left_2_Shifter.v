`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:29:54 06/15/2019 
// Design Name: 
// Module Name:    Left_2_Shifter 
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
	input [31:0] A,
	output [31:0] B
    );
	assign B = { A[29:0] , 2'b00};

endmodule
