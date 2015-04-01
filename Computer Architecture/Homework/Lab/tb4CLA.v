`include "CLA.v"

module tb4CLA;
  
  wire C_OUT;
  wire [15:0] SUM;
  reg C_IN;
  reg [15:0] A, B;
  
  CLA CLA00 (A, B, C_IN, SUM, C_OUT);
  
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
    A = 16'd62551;
    B = 16'd15456;
    
    #5
    C_IN = 1'd1;
    A = 16'd2315;
    B = 16'd4548;
    
    #5
    C_IN = 1'd1;
    A = 16'd54544;
    B = 16'd64545;
    
    #5
    C_IN = 1'd1;
    A = 16'd15478;
    B = 16'd63265;
    
    #5
    C_IN = 1'd1;
    A = 16'd6152;
    B = 16'd65210;
    
    #5
    C_IN = 1'd1;
    A = 16'd1;
    B = 16'd1;
    
    #5
    C_IN = 1'd1;
    A = 16'd45944;
    B = 16'd9545;
    
    #5
    C_IN = 1'd1;
    A = 16'd1234;
    B = 16'd65531;
    
    #5
    C_IN = 1'd1;
    A = 16'd17832;
    B = 16'd64512;
    
    #5
    C_IN = 1'd1;
    A = 16'd54581;
    B = 16'd64259;
    
    #5
    C_IN = 1'd1;
    A = 16'd2;
    B = 16'd6;
    
    #5
    C_IN = 1'd1;
    A = 16'd4;
    B = 16'd6;
    
    #5
    C_IN = 1'd1;
    A = 16'd12345;
    B = 16'd1;
    
    #5
    C_IN = 1'd1;
    A = 16'd5;
    B = 16'd65537;
    
    #5
    C_IN = 1'd1;
    A = 16'd54;
    B = 16'd45;
    
        
    #5
    $stop;
  end
endmodule
