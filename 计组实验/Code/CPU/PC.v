`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    11:05:54 06/23/2019 
// Design Name: 
// Module Name:    PC 
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
module PC(Clock,Reset,next_pc,PC);
	input Clock,Reset;
	input [31:0] next_pc;
	output [31:0] PC;
	reg [31:0] PC_reg;
	assign PC = PC_reg;

	always @(posedge Clock) begin
		if (Reset == 1)	PC_reg = 32'h0;
		else					PC_reg = next_pc;
    end

endmodule
