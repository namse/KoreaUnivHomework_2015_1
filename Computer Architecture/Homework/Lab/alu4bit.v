`include "alu1bit.v"

module alu4bit(A, B, CarryIn, Binvert, Operation, CarryOut, Result);
	input [3:0] A, B;
	input CarryIn, Binvert;
	input [1:0]Operation;
	output wire [3:0]Result;
	output wire CarryOut;
	
	wire LessWire;
	wire [2:0]CarryOutWire;

	alu1bit alu1_0 ( A[0], B[0], CarryIn, Binvert, Operation, LessWire, Result[0], CarryOutWire[0]);
	alu1bit alu1_1 ( A[1], B[1], CarryOutWire[0], Binvert, Operation, 0, Result[1], CarryOutWire[1]);
	alu1bit alu1_2 ( A[2], B[2], CarryOutWire[1], Binvert, Operation, 0, Result[2], CarryOutWire[2]);
	alu1bit alu1_3 ( A[3], B[3], CarryOutWire[2], Binvert, Operation, 0, Result[3], LessWire);
	
	assign CarryOut = LessWire;
endmodule;