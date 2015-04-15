`include "DFF.v"

module tb4dff;
  
  wire Q, Qbar;
  reg D, clk;
  
  DFF dff00 (clk, D, Q, Qbar);
    
  initial
  begin
    
    $monitor ($time, "clk = %b, D = %b, Q = %b, Qbar = %b", clk, D, Q, Qbar);
    
    clk = 1'd1;
    D = 1'd0;
    
    #15
    D = 1'd1;
    
    #15
    D = 1'd0;
    
    #15
    D = 1'd1;
    
    #15
    D = 1'd0;
    
    #15
    D = 1'd1;
    
    #15
    D = 1'd0;
    
    #15
    D = 1'd1;
    
    #15
    $stop;
    
  end
  
  always
  begin
    #10 clk = ~clk;
  end 
  
endmodule