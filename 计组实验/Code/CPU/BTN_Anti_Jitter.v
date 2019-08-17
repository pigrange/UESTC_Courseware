`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:55:30 06/22/2019 
// Design Name: 
// Module Name:    BTN_Anti_Jitter 
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
module BTN_Anti_Jitter(
		input Clock,
		input BTN_IN,
		output reg BTN_Out
    );
	 
	 reg [3:0] cnt;
	 reg BTN_Old;
	 
	 always @ (posedge Clock) begin
			if(BTN_IN != BTN_Old) 
				begin
						cnt <= 4'b0000; BTN_Old <= BTN_IN;
				end
			else 
				begin
					if( cnt == 4'b1111)
						begin
							cnt <= 4'b0000; BTN_Out <= BTN_IN;
						end
					else
							cnt <= cnt + 1'b1;
				end
	 end

endmodule
