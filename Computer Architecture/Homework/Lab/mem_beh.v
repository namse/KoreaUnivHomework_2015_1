
// a memory module
// note that addr is a byte address. To simplify our implementation
// we use addr>>2 to index the memory array. 

module mem(addr,datain,dataout, MemWrite, MemRead);

// currently the memory has 128 32-bit words
parameter mem_capacity = 4096;

input [31:0] addr, datain;
output [31:0] dataout; 
reg [31:0] dataout;

// controls when writing and when readiing
input  MemWrite, MemRead; 

// memory cells are defined here
// reg [31:0] memory [mem_capacity-1:0];
reg [31:0] memory [mem_capacity-1:0];
integer i;

// reset it at the beginning
initial begin
   for (i=0; i<mem_capacity-1; i=i+1)
      memory[i] = 0;

// read initial data into the memory
// pls refer to http://www.asic-world.com/verilog/memory_fsm1.html
   $readmemh("mem.dat", memory);
end

// whenever the any of sigals (addr or datain or memwrite or memread) changes 
always @(addr or datain or MemWrite or MemRead)
begin 
   if (MemRead)
      dataout = memory[addr>>2];
   if (MemWrite)
      memory[addr>>2] = datain;
end 

endmodule

module MemTestbench;
   reg [31:0] addr, datain;
   reg MemWrite, MemRead;
   wire [31:0] dataout;
   
   mem UUT(addr, datain, dataout, MemWrite, MemRead);

   initial begin
       
       addr = 0; 
       MemWrite = 0;
       MemRead = 1;
        
       #20 addr = 32'b0000_0000_0000_0000_0000_0000_0000_0100; 
           MemWrite = 0;
           MemRead = 1;
       
       #20 addr = 32'b0000_0000_0000_0000_0000_0000_0001_0000; 
           MemWrite = 0;
           MemRead = 1;
       
       #20 addr = 32'b0000_0000_0000_0000_0000_0000_0010_0000; 
           MemWrite = 0;
           MemRead = 1;
       
       #20 addr = 32'b0000_0000_0000_0000_0000_0000_0011_0000; 
           MemWrite = 0;
           MemRead = 1;
       
       #20 addr = 32'b0000_0000_0000_0000_0000_0000_0100_0000; 
           MemWrite = 0;
           MemRead = 1;
       
       #20 addr = 32'b0000_0000_0000_0000_0000_0000_0101_0000; 
           MemWrite = 0;
           MemRead = 1;
       
       #20 addr = 32'b0000_0000_0000_0000_0000_0000_0110_0000; 
           MemWrite = 0;
           MemRead = 1;
       
       #20 addr = 32'b0000_0000_0000_0000_0000_0000_0111_0000; 
           MemWrite = 0;
           MemRead = 1;
       
       #20 addr = 32'b0000_0000_0000_0000_0000_0000_1000_0000; 
           MemWrite = 0;
           MemRead = 1;
       
       #20 addr = 32'b0000_0000_0000_0000_0000_0000_1001_0000; 
           MemWrite = 0;
           MemRead = 1;
       
       #20 addr = 32'b0000_0000_0000_0000_0000_0000_1010_0000; 
           MemWrite = 0;
           MemRead = 1;
       
       #20 addr = 32'b0000_0000_0000_0000_0000_0000_1011_0000; 
           MemWrite = 0;
           MemRead = 1;
       
       #20 addr = 32'b0000_0000_0000_0000_0000_1000_0000_0000; 
           MemWrite = 0;
           MemRead = 1;
       
       #20 addr = 32'b0000_0000_0000_0000_0000_1000_0001_0000; 
           MemWrite = 0;
           MemRead = 1;
       
       #20 addr = 32'b0000_0000_0000_0000_0000_1000_0010_0000; 
           MemWrite = 0;
           MemRead = 1;
       
       #20 addr = 32'b0000_0000_0000_0000_0000_1000_0011_0000; 
           MemWrite = 0;
           MemRead = 1;
       
       #20 addr = 32'b0000_0000_0000_0000_0000_1000_0100_0000; 
           MemWrite = 0;
           MemRead = 1;
       
       #20 addr = 32'b0000_0000_0000_0000_0000_1000_0101_0000; 
           MemWrite = 0;
           MemRead = 1;
       
       #20 addr = 32'b0000_0000_0000_0000_0000_1000_0110_0000; 
           MemWrite = 0;
           MemRead = 1;
       
       #20 addr = 32'b0000_0000_0000_0000_0000_1000_0111_0000; 
           MemWrite = 0;
           MemRead = 1;
       
       #20 addr = 32'b0000_0000_0000_0000_0000_1000_1000_0000; 
           MemWrite = 0;
           MemRead = 1;
       
       #20 addr = 32'b0000_0000_0000_0000_0000_1000_1001_0000; 
           MemWrite = 0;
           MemRead = 1;
       
       #20 addr = 32'b0000_0000_0000_0000_0001_0000_0000_0000; 
           MemWrite = 0;
           MemRead = 1;

       #20 addr = 5;
           datain = 6;
           MemWrite = 1;
           MemRead = 0;
       #20 addr = 1;
           datain = 10;
           MemWrite = 1;
           MemRead = 0;
       #20 addr = 8;
           datain = 11;
           MemWrite = 1;
           MemRead = 0;
       #20 addr = 5;
           datain = 10;
           MemWrite = 0;
           MemRead = 1;
       #20 addr = 1;
           datain = 13;
           MemWrite = 0;
           MemRead = 1;
       #20 addr = 8;
           datain = 13;
           MemWrite = 0;
           MemRead = 1;
   end

   initial
      #600 $stop;

endmodule
