`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   17:06:39 06/24/2019
// Design Name:   SOC
// Module Name:   D:/Codes/Verilog/CPU/TestSOC.v
// Project Name:  CPU
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: SOC
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module TestSOC;

	// Inputs
	reg Clock;
	reg Reset;

	// Outputs
	wire [7:0] DISP_Seg;
	wire [5:0] AN;
	wire [23:0] Test_signal;
	wire [31:0] ALU_Result;
	wire [31:0] Ext_imm;
	wire [31:0] addr;
	wire [31:0] Out1,Out2,Instruction;
	wire MemWr,MemtoReg;

	// Instantiate the Unit Under Test (UUT)
	SOC uut (
		.Clock(Clock), 
		.Reset(Reset), 
		.DISP_Seg(DISP_Seg), 
		.AN(AN), 
		.Test_signal(Test_signal), 
		.ALU_Result(ALU_Result), 
		.Ext_imm(Ext_imm), 
		.addr(addr), 
		.MemWr(MemWr), 
		.Out1(Out1),
		.Out2(Out2),
		.Instruction(Instruction),
		.MemtoReg(MemtoReg)
	);

	initial begin
		Reset = 1;
		Clock = 0;
		#200;
      Reset = 0;  
	end
	
	always begin
		#100;
		Clock = ~Clock;
	end	
      
endmodule

