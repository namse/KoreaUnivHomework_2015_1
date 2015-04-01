`include "DEC24.v"

module tb4DEC24;
  wire [3:0] OUTV;
  reg [1:0] INV;
  reg ENA;
  
  DEC24 DEC2400 (ENA, INV, OUTV);
  
  initial
  begin
  
    ENA = 0;
    INV[1] = 0;
    INV[0] = 0;
    
    #5
    INV[0] = 1;
    
    #5
    INV[1] = 1;
    INV[0] = 0;
    
    #5
    INV[0] = 1;
    
    #5
    ENA = 1;
    INV[1] = 0;
    INV[0] = 0;
    
    #5
    INV[0] = 1;
    
    #5
    INV[1] = 1;
    INV[0] = 0;
    
    #5
    INV[0] = 1;
    
    #5
    $stop;    
  end
endmodule
