// main control unit thant gets 
module mcu(clk, clr, OP, MemRead, MemWrite, MemtoReg, ALUOp, ALUSrc, RegWrite, RegDst, Branch, JumpSignal);
input clk, clr;
input [5:0] OP;
output MemRead, MemWrite, MemtoReg, ALUSrc, RegWrite, RegDst, Branch, JumpSignal;
reg MemRead, MemWrite, MemtoReg, ALUSrc, RegWrite, RegDst, Branch, JumpSignal;
output [1:0] ALUOp;
reg [1:0] ALUOp;


always @(OP)
begin
	case (OP)
	6'b100011:	//	lw
	begin
		MemRead		=	1;
		MemWrite	=	0;
		MemtoReg	=	1;
		ALUOp		=	2'b00;
		ALUSrc		=	1;
		RegWrite	=	1;
		RegDst		=	0;
		Branch		=	0;
		JumpSignal	=	0;
	end

	6'b101011: //	sw
	begin
		MemRead		=	0;
		MemWrite	=	1;
		MemtoReg	=	0;
		ALUOp		=	2'b00;
		ALUSrc		=	1;
		RegWrite	=	0;
		Branch		=	0;			
		JumpSignal	=	0;	
	end

	0:	// add or sub
	begin
		MemRead		=	0;
		MemWrite	=	0;
		MemtoReg	=	0;
		ALUOp		=	2'b10;
		ALUSrc		=	0;
		RegWrite	=	1;
		RegDst		=	1;
		Branch		=	0;		
		JumpSignal	=	0;
	end

	4:	// beq
	begin
		MemRead		=	0;
		MemWrite	=	0;
		ALUOp		=	2'b01;
		ALUSrc		=	0;
		RegWrite	=	0;
		Branch		=	1;	
		JumpSignal	=	0;			
	end

	2:	// j
	begin
		MemRead		=	0;
		MemWrite	=	0;
		RegWrite	=	0;
		Branch		=	0;		
		JumpSignal	=	1;	
	end

	3:	// nop
	begin		
		MemRead		=	0;
		MemWrite	=	0;
		RegWrite	=	0;
		Branch		=	0;
		JumpSignal	=	0;
	end
	endcase
	
end

initial
begin
	MemRead		=	0;
	MemWrite	=	0;
	RegWrite	=	0;
	Branch		=	0;
	JumpSignal	=	0;	
end
endmodule

module acu(funct, ALUOp, ALUcontrol);
input [5:0] funct;
input [1:0] ALUOp;
output [2:0] ALUcontrol;

reg [2:0] ALUcontrol;

always @(funct or ALUOp)
begin
	case(ALUOp)
		2'b00: ALUcontrol	= 3'b010;
		2'b01: ALUcontrol	= 3'b110;
		2'b10:
		begin
		case(funct)
			6'b100000: ALUcontrol	= 3'b010;
			6'b100010: ALUcontrol	= 3'b110;
			6'b100100: ALUcontrol	= 3'b000;
			6'b100101: ALUcontrol	= 3'b001;
			6'b101010: ALUcontrol	= 3'b111;
		endcase
		end
	endcase
end

endmodule
