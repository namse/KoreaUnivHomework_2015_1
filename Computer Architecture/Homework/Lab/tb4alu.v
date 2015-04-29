`include "alu4bit.v"

module tb4alu;
  
  reg [3:0] A, B;
  reg CIN, BINV;
  reg [1:0] OP;
  
  wire COUT;
  wire [3:0] Y;
  
  alu4bit alu4bit00 (A, B, CIN, BINV, OP, COUT, Y);
  
  initial begin
    A = 4'b0000;
    B = 4'b0000;
    CIN = 1'b0;
    BINV = 1'b0;
    OP = 2'b00;
    
    #10
    A = 4'b0101;
    B = 4'b1111;
    OP = 2'b00;
    
    #10
    A = 4'b1010;
    B = 4'b1111;
    OP = 2'b00;
    
    #10
    A = 4'b0101;
    B = 4'b0000;
    OP = 2'b01;
    
    #10
    A = 4'b1010;
    B = 4'b0000;
    OP = 2'b01;
    
    #10
    A = 4'b0111;
    B = 4'b0101;
    CIN = 1'b0;
    BINV = 1'b0;
    OP = 2'b10;
    
    #10
    A = 4'b0100;
    B = 4'b0010;
    CIN = 1'b1;
    BINV = 1'b0;
    OP = 2'b10;
    
    #10
    A = 4'b0101;
    B = 4'b0010;
    CIN = 1'b1;
    BINV = 1'b1;
    OP = 2'b10;
    
    #10
    A = 4'b0100;
    B = 4'b0101;
    CIN = 1'b1;
    BINV = 1'b1;
    OP = 2'b10;
    
    #10
    A = 4'b0111;
    B = 4'b0110;
    CIN = 1'b1;
    BINV = 1'b1;
    OP = 2'b11;
     
    #10
    A = 4'b0011;
    B = 4'b0111;
    CIN = 1'b1;
    BINV = 1'b1;
    OP = 2'b11;
    
    #10
    $stop;
  end
endmodule