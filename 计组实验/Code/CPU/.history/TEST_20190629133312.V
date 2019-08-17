initial begin
		A = 32'h000000ff;
		B = 32'h000000cc;
		ALU_Ctr = 111;//初始为111，此时返回全0
		#100;
		ALU_Ctr = 3'b000;//测试加法
		#100;
		ALU_Ctr = 3'b100;//测试减法
		#100;
		ALU_Ctr = 3'b001;//测试与
		#100;
		ALU_Ctr = 3'b101;//测试或
		#100;
		ALU_Ctr = 3'b010;//测试异或
		#100;
		ALU_Ctr = 3'b110;//测试B的左移16位
		#100;
		B = 32'h000000ff;
		ALU_Ctr = 3'b100;//测试0标志位
end