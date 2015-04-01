`include "mux2to1.v"

module tb4mux2to1;
  
  wire x;
  reg a, x1,x0;

  mux2to1 mux00 (a, x1, x0, x);
    
  initial
  begin
    
    a = 0;
    x1 = 0;
    x0 = 0;
    
    #5
    x0 = 1;
    
    #5
    x1 = 1;
    x0 = 0;
    
    #5
    x0 = 1;
    
    #5
    a = 1;
    x1 = 0;
    x0 = 0;
    
    #5
    x0 = 1;
    
    #5
    x1 = 1;
    x0 = 0;
    
    #5
    x0 = 1;
    
    #5
    $stop;
    
  end
endmodule
