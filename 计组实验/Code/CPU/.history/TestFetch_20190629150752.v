`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   21:47:38 06/23/2019
// Design Name:   Fetch
// Module Name:   D:/Codes/Verilog/CPU/TestFetch.v
// Project Name:  CPU
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: Fetch
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module TestFetch;

	// Inputs
	reg Reset;
	reg Clock;
	reg Jump;
	reg Branch;
	reg Zero;
	reg [31:0] br_imm;
	reg [31:0] Instruction;
	// Outputs
	wire [31:0] addr;
	

	// Instantiate the Unit Under Test (UUT)
	Fetch uut (
		.Reset(Reset), 
		.Clock(Clock), 
		.Jump(Jump), 
		.Branch(Branch), 
		.Zero(Zero), 
		.br_imm(br_imm), 
		.Instruction(Instruction),
		.addr(addr)
	);
	
	//这里外挂一个ROM进行测试
	wire [31:0]inst;
	INST_ROM ROM(addr,inst);

	//由于没有ControlUnit，因此这里需要手动将控制信号初始化
	initial begin
		Reset = 1;
		Clock = 1;
		Jump = 1;
		Branch = 0;
		Zero = 0;
		br_imm = 0;
		Instruction = 32'b000010_00000_00000_0000_0000_0000_0101;  

		#100;
		Reset=0;
		#100;
		Jump = 0;
	end
	
	always begin
	 #100;
	 Clock = ~Clock;
	 Instruction = inst;	
   end
   
endmodule

