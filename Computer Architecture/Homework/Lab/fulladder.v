module fa(c_out,sum,c_in,a,b);
	output c_out,sum;
	input c_in,a,b;

	assign c_out = ( a & b ) | ( b & c_in ) | ( c_in & a );
	assign sum = a ^ b ^ c_in;
endmodule
