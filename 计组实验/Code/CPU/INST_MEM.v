`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:57:11 06/22/2019 
// Design Name: 
// Module Name:    INST_MEM 
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
module INST_ROM( addr , inst);
    input  [31:0] addr ; 
    output [31:0] inst ;
    
	 wire [31:0] rom [0:31];
	 
	 
	 assign rom[5'h00] = 32'b000010_00000_00000_0000_0000_0000_0101; //j 5H
	 assign rom[5'h01] = 32'hAAA0 ; // Not use
	 assign rom[5'h02] = 32'hAAA1 ; // Not use
	 assign rom[5'h03] = 32'hAAA2 ; // Not use
	 assign rom[5'h04] = 32'hAAA3 ; // Not use
	 assign rom[5'h05] = 32'b001101_00000_00001_0001_0010_0011_0100; //ori R1 , R0 , 1234H  
	 assign rom[5'h06] = 32'b001101_00000_00010_0101_0110_0111_1000; //ori R2 , R0 , 5678H  
	 assign rom[5'h07] = 32'b001101_00001_00011_1111_1111_0000_0000; //ori R3 , R1 , FF00H
	 assign rom[5'h08] = 32'b000000_00001_00010_00100_00000_100000;  //add R4 , R1 , R2
	 assign rom[5'h09] = 32'b000000_00001_00010_00101_00000_100010;  //sub R5 , R1 , R2
	 assign rom[5'h0A] = 32'b000000_00001_00010_00110_00000_100011;  //subu R6 , R1 , R2
	 assign rom[5'h0B] = 32'b000000_00001_00010_00111_00000_101010;  //slt R7 , R1 , R2
	 assign rom[5'h0C] = 32'b000000_00010_00001_01000_00000_101011;  //sltu R8 , R2 , R1
	 assign rom[5'h0D] = 32'b101011_00000_00100_0000_0000_0000_0100; //sw R4 , R0 , 4H 
	 assign rom[5'h0E] = 32'b100011_00000_01001_0000000000000100; //lw R9 ,   R0 , 4H
	 assign rom[5'h0F] = 32'b000000_00001_01001_10010_00000_100000; //add R10 , R1 , R9 
	 assign rom[5'h10] = 32'b000100_00001_00010_0001_0010_0011_0100; //beq R1 , R2 , 1234H
	 assign rom[5'h11] = 32'b000100_00001_00001_1111_1111_1110_1110; //beq R1 , R1 , FFEEH
	 assign rom[5'h12] = 32'h0 ; // Not use
	 assign rom[5'h13] = 32'h0 ; // Not use
	 assign rom[5'h14] = 32'h0 ; // Not use
	 assign rom[5'h15] = 32'h0 ; // Not use
	 assign rom[5'h16] = 32'h0 ; // Not use
	 assign rom[5'h17] = 32'h0 ; // Not use
	 assign rom[5'h18] = 32'h0 ; // Not use
	 assign rom[5'h19] = 32'h0 ; // Not use
	 assign rom[5'h1A] = 32'h0 ; // Not use
	 assign rom[5'h1B] = 32'h0 ; // Not use
	 assign rom[5'h1C] = 32'h0 ; // Not use
	 assign rom[5'h1D] = 32'h0 ; // Not use
	 assign rom[5'h1E] = 32'h0 ; // Not use
	 assign rom[5'h1F] = 32'h0 ; // Not use
	 
	 assign inst = rom[addr[6:2]];
endmodule 