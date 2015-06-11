`include "mem_beh.v"
`include "regfile_beh.v"
`include "components.v"
`include "control_units.v"
`include "alu_beh.v"
`include "mux2to1_beh.v"


module kustar;
reg clock, clear;
wire Zero;


// Signal //
/*
//Ex
[8:7]	ALUOp
[6]	ALUSrc
[5]	RegDst, 

//M
[4]	Branch
[3]	MemRead
[2]	MemWrite

//WB
[1]	RegWrite
[0]	MemtoReg
*/

//	IF_ID
reg	[31:0]	IF_ID_AddedPC;
reg	[31:0]	IF_ID_Inst;


//	ID_EX
reg	[31:0]	ID_EX_AddedPC;
reg	[31:0]	ID_EX_ReadData1;
reg	[31:0]	ID_EX_ReadData2;
reg	[31:0]	ID_EX_ExtendedAddr;
reg	[4:0]	ID_EX_Inst20_16;
reg	[4:0]	ID_EX_Inst15_11;
reg	[8:0]	ID_EX_Signal;

//	EX_MEM
reg	[31:0]	EX_MEM_AddedPC;
reg			EX_MEM_Zero;
reg	[31:0]	EX_MEM_ALU_Result;
reg	[31:0]	EX_MEM_ReadData2;
reg	[4:0]	EX_MEM_RegWriteDst;
reg	[4:0]	EX_MEM_Signal;


//	MEM_WB
reg	[31:0]	MEM_WB_MemReadData;
reg	[31:0]	MEM_WB_ALU_Result;
reg	[4:0]	MEM_WB_RegWriteDst;
reg	[2:0]	MEM_WB_Signal;

wire [31:0] MuxToPC, PCToInstMem, AddToIF_ID, InstMemToIF_ID, IF_ID_AddedPC_To_ID_EX;
wire [31:0]	RegtoA, RegtoB, MuxtoWriteData, ExtendToID_EX, ShifttoConcat, JumpAddress;
wire [31:0] EX_MEM_TO_PC_MUX;

wire [4:0] MuxToRegDst;
wire [31:0] MuxToALU, ShiftToAdd, AddToEX_MEM_AddedPC, ALUOut;
wire [2:0] ALUcontrol;

wire [31:0] DataMemResult;
wire		MemRead, MemWrite, MemtoReg, ALUSrc, RegWrite, RegDst, Branch;
wire [1:0] ALUOp;

wire	JumpSignal;

reg	[31:0] four;
reg	yesItAlwaysTure;
reg	yesItAlwyasFalse;
reg	[31:0] unused;

mux4to1				PrePCMux		(AddToIF_ID, EX_MEM_AddedPC, JumpAddress, JumpAddress, MuxToPC,  {JumpSignal,{EX_MEM_Signal[4] & EX_MEM_Zero}});
single_register		PC				(MuxToPC, PCToInstMem, clock, clear, yesItAlwaysTure);
Adder				PCAdder			(PCToInstMem, four, AddToIF_ID);
mem					InstMem			(PCToInstMem, unused, InstMemToIF_ID, yesItAlwyasFalse, yesItAlwaysTure, clock);

shiftleft2			JumpShift		(IF_ID_Inst, ShifttoConcat);
concatenate4to28	PCConcat		(ShifttoConcat, PCToInstMem, JumpAddress);


registerfile		Registers		({IF_ID_Inst[25:21]}, RegtoA, {IF_ID_Inst[20:16]}, RegtoB, MEM_WB_RegWriteDst, MuxtoWriteData, clock, yesItAlwyasFalse, MEM_WB_Signal[1]);
signextd			SignExtend		({IF_ID_Inst[15:0]}, ExtendToID_EX);
mcu					YesThisIsMCU	(clock, clear, {IF_ID_Inst[31:26]},
	MemRead, MemWrite, MemtoReg, ALUOp, ALUSrc, RegWrite, RegDst, Branch, 
		JumpSignal);


mux2to1				ALUMux			(ID_EX_ReadData2, ID_EX_ExtendedAddr, MuxToALU, {ID_EX_Signal[6]});
mux2to1for5bit		RegDstMux		(ID_EX_Inst20_16, ID_EX_Inst15_11, MuxToRegDst, ID_EX_Signal[5]);
shiftleft2			Shift			(ID_EX_ExtendedAddr, ShiftToAdd);
Adder				BranchAdder		(ID_EX_AddedPC, ShiftToAdd, AddToEX_MEM_AddedPC);
ALU					YesThisIsALU	(ID_EX_ReadData1, MuxToALU, ALUcontrol, ALUOut, Zero);
acu					YesThisIsACU	(ID_EX_ExtendedAddr[5:0], ID_EX_Signal[8:7], ALUcontrol);

mem					DataMem			(EX_MEM_ALU_Result, EX_MEM_ReadData2, DataMemResult, EX_MEM_Signal[2], EX_MEM_Signal[1], clock);

mux2to1				MemToRegMux		(MEM_WB_ALU_Result, MEM_WB_MemReadData, MuxtoWriteData, MEM_WB_Signal[0]);

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
	clock = 1;

	#5;
	four = 4;
	yesItAlwaysTure = 1;
	yesItAlwyasFalse = 0;
	clear = 1;
	EX_MEM_Signal[4] = 0;
	EX_MEM_Zero = 0;

	/* we may not connect clear to register file and memory because we don't want our initial data get cleared*/
	#10 clear = 0;
end

always @(negedge clock)
begin
	#10
	MEM_WB_MemReadData	=	DataMemResult;


	MEM_WB_Signal	=	EX_MEM_Signal[1:0];
	MEM_WB_ALU_Result	=	EX_MEM_ALU_Result;
	MEM_WB_RegWriteDst	=	EX_MEM_RegWriteDst;

	EX_MEM_Signal	=	ID_EX_Signal[4:0];
	EX_MEM_Zero		=	Zero;
	EX_MEM_AddedPC	=	AddToEX_MEM_AddedPC;
	EX_MEM_ReadData2	=	ID_EX_ReadData2;
	EX_MEM_ALU_Result	=	ALUOut;
	EX_MEM_RegWriteDst	=	MuxToRegDst;


	ID_EX_AddedPC	=	IF_ID_AddedPC;
	ID_EX_ReadData1	=	RegtoA;
	ID_EX_ReadData2	=	RegtoB;
	ID_EX_ExtendedAddr	=	ExtendToID_EX;
	ID_EX_Inst20_16	=	IF_ID_Inst[20:16];
	ID_EX_Inst15_11	=	IF_ID_Inst[15:11];
	ID_EX_Signal	=	{ALUOp[1:0],ALUSrc,RegDst,Branch,MemRead,MemWrite,RegWrite,MemtoReg};


	IF_ID_Inst 		= InstMemToIF_ID;
	IF_ID_AddedPC	= AddToIF_ID;

	



end

initial 
#10000 $stop;

endmodule
