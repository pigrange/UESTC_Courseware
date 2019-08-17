`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    13:21:16 06/23/2019 
// Design Name: 
// Module Name:    Ext 
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

//(ÎÞ)·ûºÅÀ©Õ¹Æ÷
module Ext(Ext_imm,br_addr,br_addr_ex);
input Ext_imm;
input [15:0] br_addr;
output [31:0] br_addr_ex;

wire [15:0]addr_fill;

assign addr_fill = (Ext_imm & br_addr[15])? 16'hFFFF:16'h0;
assign br_addr_ex[31:16]=addr_fill;
assign br_addr_ex[15:0]=br_addr;

endmodule
