// main control unit thant gets 
module mcu(clk, clr, OP, PCWriteCond, PCWrite, IorD, MemRead, MemWrite, MemtoReg, IRWrite, PCSource, ALUOp, ALUSrcB, ALUSrcA, RegWrite, RegDst);
input clk, clr;
input [5:0] OP;
output PCWriteCond, PCWrite, IorD, MemRead, MemWrite, MemtoReg, IRWrite, ALUSrcA, RegWrite, RegDst;
reg PCWriteCond, PCWrite, IorD, MemRead, MemWrite, MemtoReg, IRWrite, ALUSrcA, RegWrite, RegDst;
output [1:0] PCSource, ALUOp, ALUSrcB;
reg [1:0] PCSource, ALUOp, ALUSrcB;

//reg [3:0] current_state;
//reg [3:0] next_state;

integer current_state;
integer next_state;


always @(current_state)
begin
	case(current_state)
	0: 
	begin
		IorD		= 0;
		MemRead		= 1;
		MemWrite	= 0;
		IRWrite		= 1;
		ALUSrcA		= 0;
		ALUSrcB		= 2'b01;
		ALUOp		= 2'b00;
		PCWrite		= 1;
		PCWriteCond	= 0;
		RegWrite	= 0;
		MemtoReg	= 0;
		RegDst		= 0;

		#3;
		PCSource	= 2'b00;
		
	end
		
	1:
		begin	
			ALUSrcA	= 0;
			ALUSrcB	= 2'b11;
			ALUOp	= 2'b00;
			
			IRWrite	= 0;
			MemRead	= 0;

			PCWrite	= #1 0;
		end

	2:
		begin
			ALUSrcA	= 1;
			ALUSrcB	= 2'b10;
			ALUOp	= 2'b00;
		end

	3:
		begin
			IorD	= 1;
			MemRead	= 1;
		end

	4:
		begin
			MemtoReg	= 1;
			RegDst		= 0;
			RegWrite	= 1;
			MemRead		= 0;
		end

	5:
		begin
			IorD		= 1;
			MemWrite	= 1;
		end

	6:
	begin
		ALUSrcA	= 1;
		ALUSrcB	= 2'b00;
		ALUOp	= 2'b10;
	end

	7:
	begin
		RegDst		= 1;
		RegWrite	= 1;
		MemtoReg	= 0;
	end

	8:
	begin
		ALUSrcA		= 1;
		ALUSrcB		= 2'b00;
		ALUOp		= 2'b01;
		PCSource	= 2'b01;
		PCWriteCond	= 1;
	end

	9:
	begin
		PCSource	= 2'b10;
		PCWrite		= 1;
	end

	endcase
end

always @(posedge clk)
begin
	//if (clr	== 1'b0)
	if (clr	== 1'b1)
		current_state	= -1;
	else
		current_state	= next_state;
end

always @(current_state or OP)
begin
	next_state	= -1;
	case (current_state)
	-1: next_state	= 0;
	
	0: next_state	= 1;

	1:
	begin
	case (OP)
	6'b100011: next_state	= 2;
	6'b101011: next_state	= 2;
	0:			next_state	= 6;
	4:			next_state	= 8;
	2:			next_state	= 9;
	endcase
	end
	
	2:
	begin
	case (OP)
	6'b100011: next_state	= 3;
	6'b101011: next_state	= 5;
	endcase
	end

	3: next_state	= 4;
	4: next_state	= 0;
	5: next_state	= 0;
	6: next_state	= 7;
	7: next_state	= 0;
	8: next_state	= 0;
	9: next_state	= 0;

	default:
		next_state	= -1;
	endcase
		
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
