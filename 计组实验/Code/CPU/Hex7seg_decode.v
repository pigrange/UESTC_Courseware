`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:56:07 06/22/2019 
// Design Name: 
// Module Name:    Hex7seg_decode 
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
module Hex7seg_decode(
		input wire [23:0] disp_num,	// 待显示的24位二进制数或点阵
		input wire[2:0] Scanning,	// 显示扫描信号，用时钟分频获得。
		output wire [7:0] SEGMENT,	// 7段码显示编码
		output  [5:0] AN			// 4位7段码共阳控制端，用于扫描显示控制
    );

	wire [3:0] digit;

	
	assign AN = (Scanning == 3'b000) ? 6'b000001 : 
	            (Scanning == 3'b001) ? 6'b000010 : 
					(Scanning == 3'b010) ? 6'b000100 : 
					(Scanning == 3'b011) ? 6'b001000 : 
					(Scanning == 3'b100) ? 6'b010000 : 6'b100000 ;
	
	assign digit = (AN == 6'b000001) ? disp_num[3:0] : 
	               (AN == 6'b000010) ? disp_num[7:4] : 
						(AN == 6'b000100) ? disp_num[11:8] : 
						(AN == 6'b001000) ? disp_num[15:12] : 
						(AN == 6'b010000) ? disp_num[19:16] : disp_num[23:20] ;
	
	assign SEGMENT = (digit == 4'h0) ? 8'b00111111 : 
	                   (digit == 4'h1) ? 8'b00000110 : 
							 (digit == 4'h2) ? 8'b01011011 : 
							 (digit == 4'h3) ? 8'b01001111 : 
							 (digit == 4'h4) ? 8'b01100110 : 
							 (digit == 4'h5) ? 8'b01101101 : 
							 (digit == 4'h6) ? 8'b01111101 : 
							 (digit == 4'h7) ? 8'b00000111 : 
							 (digit == 4'h8) ? 8'b01111111 : 
							 (digit == 4'h9) ? 8'b01101111 : 
							 (digit == 4'hA) ? 8'b01110111 : 
							 (digit == 4'hB) ? 8'b01111100 : 
							 (digit == 4'hC) ? 8'b00111001 : 
							 (digit == 4'hD) ? 8'b01011110 : 
							 (digit == 4'hE) ? 8'b01111001 : 8'b01110001 ;

endmodule

