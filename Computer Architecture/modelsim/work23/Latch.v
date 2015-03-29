module SR_latch(Q, Qbar, Sbar, Rbar);
   output Q, Qbar;
   input Sbar, Rbar;
   
   assign Q = ~(Sbar & Qbar);
   assign Qbar = ~(Rbar & Q);
endmodule
