module Freq_Divider(CLK, RST, CLK_Out);
	parameter Div = 16'd50_000;
	parameter Div2 = 16'd25_000;
	parameter DivW = 16;
	inout CLK, RST;
	output reg CLK_Out;

	reg rCLK_Out;
	reg [DivW-1:0] CLK_Cnt = 0;

	always @( posedge CLK, negedge RST ) begin
		if (!RST)
			CLK_Cnt <= 0;
		else if (CLK_Cnt == Div-1)
			CLK_Cnt <= 0;
		else
			CLK_Cnt <= CLK_Cnt + 1'b1;
	end
	always @( posedge CLK or negedge RST ) begin
		if (!RST)
			CLK_Out <= 0;
		else if (CLK_Cnt <= Div2-1)
			CLK_Out = 0;
		else
			CLK_Out = 1;
	end
endmodule