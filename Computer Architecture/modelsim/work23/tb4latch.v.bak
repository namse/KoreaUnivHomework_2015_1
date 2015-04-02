`include "sr_latch.v"

module Testbench4Sr_latch;

wire q, qbar;
reg setbar, resetbar;

SR_latch SR_latch1(q, qbar, setbar, resetbar);

initial
begin
    
  setbar = 1'b0;
  resetbar = 1'b1;
  
  #5
  setbar = 1'b1;
  
  #5
  resetbar = 1'b0;
  
  #5
  resetbar = 1'b1;
  
  #5
  setbar = 1'b0;
  resetbar = 1'b0;

  #5
  $stop;
end
endmodule
