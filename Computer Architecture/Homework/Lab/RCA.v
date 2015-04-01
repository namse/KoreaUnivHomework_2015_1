`include "fulladder.v"

module RCA (c_out, sum, c_in, a, b);
	input c_in;
	input [15:0] a, b;
	output c_out;
	output [15:0] sum;
  
	wire [14:0] carry;
	
	fa fa00 ( carry[0], sum[0], c_in, a[0], b[0]);
	fa fa01 ( carry[1], sum[1], carry[0], a[1], b[1]);
	fa fa02 ( carry[2], sum[2], carry[1], a[2], b[2]);
	fa fa03 ( carry[3], sum[3], carry[2], a[3], b[3]);
	fa fa04 ( carry[4], sum[4], carry[3], a[4], b[4]);
	fa fa05 ( carry[5], sum[5], carry[4], a[5], b[5]);
	fa fa06 ( carry[6], sum[6], carry[5], a[6], b[6]);
	fa fa07 ( carry[7], sum[7], carry[6], a[7], b[7]);
	fa fa08 ( carry[8], sum[8], carry[7], a[8], b[8]);
	fa fa09 ( carry[9], sum[9], carry[8], a[9], b[9]);
	fa fa10 ( carry[1], sum[10], carry[9], a[10], b[10]);
	fa fa11 ( carry[11], sum[11], carry[10], a[11], b[11]);
	fa fa12 ( carry[12], sum[12], carry[11], a[12], b[12]);
	fa fa13 ( carry[13], sum[13], carry[12], a[13], b[13]);
	fa fa14 ( carry[14], sum[14], carry[13], a[14], b[14]);
	fa fa15 ( c_out, sum[15], carry[14], a[15], b[15]);
endmodule
