`include "RCA.v"

module tb4RCA;
  
  wire C_OUT;
  wire [15:0] SUM;
  reg C_IN;
  reg [15:0] A, B;
  
  RCA RCA00 (C_OUT, SUM, C_IN, A, B);
  
  initial
  begin
    
    C_IN = 1'd1;
    A = 16'd21;
    B = 16'd56;
    
    #5
    C_IN = 1'd0;
    A = 16'd23;
    B = 16'd198;
    
    #5
    C_IN = 1'd1;
    A = 16'd423;
    B = 16'd345;
    
    #5
    C_IN = 1'd0;
    A = 16'd999;
    B = 16'd0;
    
    #5
    C_IN = 1'd1;
    A = 16'd5435;
    B = 16'd3456;
    
    #5
    C_IN = 1'd1;
    A = 16'd2454;
    B = 16'd9867;
    
    #5
    C_IN = 1'd1;
    A = 16'd1;
    B = 16'd2;
    
    #5
    C_IN = 1'd1;
    A = 16'd3;
    B = 16'd4;
    
    #5
    C_IN = 1'd1;
    A = 16'd5;
    B = 16'd6;
    
    #5
    $stop;
  end
endmodule
