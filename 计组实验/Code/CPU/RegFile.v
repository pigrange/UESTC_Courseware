`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:14:29 06/15/2019 
// Design Name: 
// Module Name:    RegFile 
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
module RegFile(
    input [4:0]Rn1,Rn2,Wn,
    input Write,Clock,
    input [31:0]Wd,
    output [31:0]Out1,Out2
    );
	//创建32个长度为32位的数组模拟寄存器堆
	reg [31:0] Register[1:31];
	//Out1输出Rn1信号指定的寄存器
	assign Out1 = (Rn1 == 0) ? 0: Register[Rn1];
	//Out2输出Rn2信号指定的寄存器
	assign Out2 = (Rn2 == 0) ? 0: Register[Rn2];
	//当始处于时钟上升沿并且处于写使能的时候，向寄存器堆里面写入数据
	always @( posedge Clock ) begin
		if ((Write) && (Wn != 0)) Register[Wn] <= Wd;
	end
	//堆寄存器堆里面的数据进行初始化（全0）
	integer i;
	initial begin
		for (i = 1 ; i <= 31; i = i + 1) Register [i] = 0;
	end

endmodule
