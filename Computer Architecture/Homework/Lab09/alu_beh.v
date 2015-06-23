/* A alu module*/
module ALU(inputA, inputB, ALUop, result, zero);
input [31:0] inputA, inputB;
input [2:0] ALUop; 

output [31:0] result;
reg [31:0] result;
output zero;
reg zero;

/*whenever input or ALUop changes*/
always @(inputA or inputB or ALUop)
begin 
/*it supports AND, OR, ADD, SLT with a zero output*/

	case(ALUop)
		3'b010:	result	=	inputA	+	inputB;
		3'b110:	result	=	inputA	-	inputB;
		3'b001:	result	=	inputA	|	inputB;
		3'b000:	result	=	inputA	&	inputB;
		3'b111:	
		begin
			if(inputA < inputB)
				result	=	1;
			else
				result	=	0;
		end
	endcase

	if (inputA == inputB)
			zero = 1;
	else
			zero = 0;
end 
endmodule

module ALUTestbench;
	reg [31:0] inputA, inputB; 
	reg [2:0] ALUop; 
	wire [31:0] result;
	wire zero;

	ALU UUT(inputA, inputB, ALUop, result, zero);

	initial begin
			#20 inputA = 5;
					inputB = 6;
					ALUop = 3'b000;
			#40 inputA = 5;
					inputB = 6;
					ALUop = 3'b001;
			#40 inputA = 5;
					inputB = 6;
					ALUop = 3'b010;
			#40 inputA = 5;
					inputB = 6;
					ALUop = 3'b110;
			#40 inputA = 5;
					inputB = 6;
					ALUop = 3'b111;
			#40 inputA = 9;
					inputB = 3;
					ALUop = 3'b111;
			#40 inputA = 6;
					inputB = 6;
					ALUop = 3'b001;
			#40 inputA = -8;
					inputB = 6;
					ALUop = 3'b001;
	end

	initial
			#340 $stop;

endmodule
