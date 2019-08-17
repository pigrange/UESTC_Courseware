`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:55:46 06/22/2019 
// Design Name: 
// Module Name:    DATA_MEM 
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
module DATA_MEM(
		input [31:0] datain,
		input [31:0] addr,
		input  ReadWrite , 
		input  Clock,
		output[31:0] dataout
    );

	reg [31:0] ram [0:31];
	
	//ReadWrite为1的时候是写，0的时候是读
	assign dataout = ReadWrite == 0? ram[addr[6:2]] : 0;
	
	always @(posedge Clock)
	    if (ReadWrite) ram[addr[6:2]] = datain;
	
	integer i;
	
	initial begin
			for ( i = 0 ; i <= 31 ; i = i + 1) ram [i] = i * i;
	end		
	
endmodule
