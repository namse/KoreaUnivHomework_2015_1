`include "mem_beh.v"
`include "regfile_beh.v"
`include "components.v"
`include "control_units.v"
`include "alu_beh.v"
`include "mux2to1_beh.v"


module kustar;
reg clock, clear;
wire [31:0] MuxtoPC, PCtoMux, MuxtoMem, MemtoInstReg, SigntoShift, ShifttoMux, MemdatatoMux, MuxtoWriteData;
wire [31:0] RegtoA, RegtoB, AtoMux, BtoMux, AMuxtoALU, BMuxtoALU, ALUtoALUOut, ALUOuttoMux , ShifttoConcat, ConcattoMux;
wire Zero;
wire [5:0] Op ;
wire [4:0] Rs, Rt, MuxtoWriteReg;
wire [15:0] AddrorConst ;
wire PCWriteCond, PCWrite, IorD, MemRead, MemWrite, MemtoReg, IRWrite,	ALUSrcA, RegWrite, RegDst;
wire [1:0] PCSource, ALUOp, ALUSrcB;
wire [2:0] ALUcontrol;


reg	[31:0] four;
reg	yesItAlwaysTure;
reg	yesItAlwyasFalse;
reg	[31:0] unused;

single_register		PC				(MuxtoPC, PCtoMux, clock, clear, (Zero&PCWriteCond)|PCWrite);

mux2to1				PostPCMux		(PCtoMux, ALUOuttoMux, MuxtoMem, IorD);

mem					Memory			(MuxtoMem, RegtoB, MemtoInstReg, MemWrite, MemRead, clock);

single_register 	InstReg			(MemtoInstReg, {Op[5:0], Rs[4:0], Rt[4:0], AddrorConst[15:0]}, clock, clear, IRWrite);
single_register 	MemDataReg		(MemtoInstReg, MemdatatoMux, clock, clear, MemRead);

mux2to1for5bit		WriteRegMux		(Rt, AddrorConst[15:11], MuxtoWriteReg, RegDst);
mux2to1				PreWriteDataMux	(ALUOuttoMux, MemdatatoMux, MuxtoWriteData, MemtoReg);
registerfile		Registers		(Rs, RegtoA, Rt, RegtoB, MuxtoWriteReg, MuxtoWriteData, clock, yesItAlwyasFalse, RegWrite);

signextd			SignExtend		(AddrorConst, SigntoShift);
shiftleft2			ShiftSign		(SigntoShift, ShifttoMux);

mux2to1				AMux			(PCtoMux, RegtoA, AMuxtoALU, ALUSrcA);
mux4to1				BMux			(RegtoB, four, SigntoShift, ShifttoMux, BMuxtoALU, ALUSrcB);

ALU					YesThisIsALU	(AMuxtoALU, BMuxtoALU, ALUcontrol, ALUtoALUOut, Zero);
single_register		ALUOut			(ALUtoALUOut, ALUOuttoMux, clock, clear, yesItAlwaysTure);

shiftleft2			PCShift			({Op[5:0], Rs[4:0], Rt[4:0], AddrorConst[15:0]}, ShifttoConcat);
concatenate4to28	PCConcat		(ShifttoConcat, PCtoMux, ConcattoMux);

mux4to1				PCMux			(ALUtoALUOut, ALUOuttoMux, ConcattoMux, unused, MuxtoPC, PCSource);

mcu					YesThisIsMCU	(clock, clear, Op, PCWriteCond,
									PCWrite, IorD, MemRead, MemWrite, MemtoReg, IRWrite, PCSource, ALUOp, ALUSrcB, ALUSrcA, RegWrite, RegDst);

acu					YesThisIsACU	(AddrorConst[5:0], ALUOp, ALUcontrol);


/*

module acu(funct, ALUOp, ALUcontrol);
input [5:0] funct;
input [1:0] ALUOp;
output [2:0] ALUcontrol;

-------------------------------------------------------

module mcu(clk, clr, OP, PCWriteCond, PCWrite, IorD, MemRead, MemWrite, MemtoReg, IRWrite, PCSource, ALUOp, ALUSrcB, ALUSrcA, RegWrite, RegDst);
input clk, clr;
input [5:0] OP;
output PCWriteCond, PCWrite, IorD, MemRead, MemWrite, MemtoReg, IRWrite, ALUSrcA, RegWrite, RegDst;
output [1:0] PCSource, ALUOp, ALUSrcB;


-------------------------------------------------------------
// concatenate pcin[31-28] with datain[27-0] to form a jump address
module concatenate4to28(datain, pcin, pcout);
input [31:0] datain, pcin;
output [31:0] pcout;
-------------------------------------------------------------
module ALU(inputA, inputB, ALUop, result, zero);
input [31:0] inputA, inputB;
input [2:0] ALUop; 

output [31:0] result;
output zero;
---------------------------------------------------------------
module mux4to1(datain0, datain1, datain2, datain3, dataout, select);
input [31:0] datain0, datain1, datain2, datain3;
input[1:0] select;
output [31:0] dataout; 
-------------------------------------------
module shiftleft2(datain, dataout);
input [31:0] datain;
output [31:0] dataout;
-----------------------------------------------------------
module signextd(datain, dataout);
input [15:0] datain;
output [31:0] dataout;
------------------------------------------------------------
module registerfile(ADDA, DATAA, ADDB, DATAB, ADDC, DATAC, clk, clr, WE);
    input [4:0]  ADDA,ADDB, ADDC;
    input [31:0] DATAC;
    input clk, clr, WE;
    output [31:0] DATAA, DATAB;

---------------------------------------------
module single_register(datain, dataout, clk, clr, WE);
		input [31:0] datain;
		output [31:0] dataout;
		input clk, clr, WE;
		----------------

module mem(addr,datain,dataout, MemWrite, MemRead, clk);
input clk;

input [31:0] addr, datain;
output [31:0] dataout; 
input	MemWrite, MemRead; 
------------------------------

module mux2to1(datain0,datain1, dataout, select);
input [31:0] datain0, datain1;
input select;
output [31:0] dataout; 
*/

initial
	forever #50 clock = ~clock;
  
initial
begin
	four = 4;
	yesItAlwaysTure = 1;
	yesItAlwyasFalse = 0;
	clock = 0;
	clear = 1;
	/* we may not connect clear to register file and memory because we don't want our initial data get cleared*/
	#10 clear = 0;
end

initial 
#10000 $stop;

endmodule
