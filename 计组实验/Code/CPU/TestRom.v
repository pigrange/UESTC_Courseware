`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   15:02:23 06/24/2019
// Design Name:   INST_ROM
// Module Name:   D:/Codes/Verilog/CPU/TestRom.v
// Project Name:  CPU
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: INST_ROM
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module TestRom;

	// Inputs
	reg [31:0] addr;

	// Outputs
	wire [31:0] inst;

	// Instantiate the Unit Under Test (UUT)
	INST_ROM uut (
		.addr(addr), 
		.inst(inst)
	);

	initial begin
		// Initialize Inputs
		addr = 0;
		// Add stimulus here
	end
	
	always begin 
		#100;
		addr = addr + 4;
   end
   
endmodule

