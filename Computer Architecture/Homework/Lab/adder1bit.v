module adder1bit (a, b, c, s, p, g);
	input a, b, c;
	output s, p, g;
  
  /* to do */

	assign p = a ^ b;
	assign g = a & b;
	assign s = p ^ c;
endmodule