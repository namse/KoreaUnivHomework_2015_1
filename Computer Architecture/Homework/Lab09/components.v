module single_register(datain, dataout, clk, clr, WE);
    input [31:0] datain;
    output [31:0] dataout;
    input clk, clr, WE;

    reg [31:0] register;

always @(posedge clk or posedge clr)
begin
  if(clr)
    register = 0;  
  else
    if(WE == 1)
    register =  datain;
end    
  assign dataout = register;

endmodule

module single_register_Testbench;

reg [31:0] inputA; 
wire [31:0] result;
reg  clk, clr, WE;

single_register UUT(inputA,result, clk, clr, WE);

   initial begin
      clk = 0;
      clr = 0;
      WE = 1;
      #20 inputA = 12;
      clk = !clk;
      #40 inputA = 24;
      clk = !clk;
      #40 inputA = 36;
      clk = !clk;
      WE = 0;
      #40 inputA = 48;
      clk = !clk;
      clr = 1;
      #40 inputA = 1024;
      clk = !clk;
      clr = 0;
      #40 inputA = 2048;
      clk = !clk;
      WE = 1;
      #40 inputA = 4096;
      clk = !clk;
      #40 inputA = 12345;
      clk = !clk;
   end


endmodule

module mux4to1(datain0, datain1, datain2, datain3, dataout, select);
input [31:0] datain0, datain1, datain2, datain3;
input[1:0] select;
output [31:0] dataout; 
reg [31:0] dataout;

always@(datain0 or datain1 or datain2 or datain3 or select)
begin
  case(select)
  2'b00:  dataout = datain0;
  2'b01:  dataout = datain1;
  2'b10:  dataout = datain2;
  2'b11:  dataout = datain3;
  endcase
end

endmodule

module mux4to1_Testbench;

reg [31:0] inputA;
reg [31:0] inputB;
reg [31:0] inputC;
reg [31:0] inputD; 
reg [1:0] select;
wire [31:0] result;

mux4to1 UUT(inputA,inputB, inputC, inputD, result, select);

   initial begin
      inputA = 1;
      inputB = 2;
      inputC = 3;
      inputD = 4;
      #20 select = 0;
      #40 select = 1;
      #40 select = 2;
      #40 select = 3;
   end

endmodule


module signextd(datain, dataout);
input [15:0] datain;
output [31:0] dataout;
reg [31:0] dataout;
integer i;

always @ (datain)
begin
  dataout = $signed(datain);
end

endmodule

module signextd_Testbench;

reg [15:0] inputA; 
wire [31:0] result;

signextd UTT(inputA,result);

  initial begin
      #20 inputA = 1234;
      #40 inputA = 64000;
      #40 inputA = 35;
  end


endmodule

module shiftleft2(datain, dataout);
input [31:0] datain;
output [31:0] dataout;
reg [31:0] dataout;

always @ (datain)
begin
  dataout = datain * 4;
end
endmodule

module shiftleft2_Testbench;

reg [31:0] inputA; 
wire [31:0] result;

shiftleft2 UUT(inputA,result);

   initial begin
       #20 inputA = 32'b0000_0000_0000_0000_1010_1010_1010_1010;
       #40 inputA = 32'b0000_0000_0000_0000_1111_1111_1111_1111;
       #40 inputA = 32'b1110_1110_1110_1110_1110_1110_1110_1110;
       #40 inputA = 32'b1001_1001_1001_1001_0110_0110_0110_0110;
       #40 inputA = 32'b0000_1000_0001_0000_0100_0010_0010_0101;
       #40 inputA = 32'b0000_1111_0000_1111_0000_1111_0000_1111;
       #40 inputA = 32'b1111_0000_1111_0000_1111_0000_1111_0000;
       #40 inputA = 32'b0110_0011_1100_0110_0011_1100_0110_0011;
   end

   initial
       #340 $stop;


endmodule

/* concatenate pcin[31-28] with datain[27-0] to form a jump address*/
module concatenate4to28(datain, pcin, pcout);
input [31:0] datain, pcin;
output [31:0] pcout;
reg [31:0] pcout;

always @ (datain or pcin)
begin
  pcout = {pcin[31:28],datain[27:0]};
end

endmodule

module concatenate4to28_Testbench;

reg [31:0] inputA, inputB; 
wire [31:0] result;

concatenate4to28 UUT(inputA, inputB, result);

   initial begin
      #20 inputA = 32'b0000_0000_0000_0000_1010_1010_1010_1010;
      inputB = 32'b0000_0000_0000_0000_1111_1111_1111_1111;
      
      #40 inputA = 32'b1110_1110_1110_1110_1110_1110_1110_1110;
      inputB = 32'b1001_1001_1001_1001_0110_0110_0110_0110;
      
      #40 inputA = 32'b0000_1000_0001_0000_0100_0010_0010_0101;
      inputB = 32'b0000_1111_0000_1111_0000_1111_0000_1111;
      
      #40 inputA = 32'b1111_0000_1111_0000_1111_0000_1111_0000;
      inputB = 32'b0110_0011_1100_0110_0011_1100_0110_0011;
   end

endmodule
