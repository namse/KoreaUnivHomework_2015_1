`include "adder1bit.v"
`include "carrygu.v"

module adder4bit(a, b, cin, sum, P, G, cout);
	input [3:0] a, b;
	input cin;
	output [3:0] sum;
	output P, G, cout;

	wire [4:1] carry;
	wire [3:0] p;
	wire [3:0] g;

	adder1bit adder1bit0 ( a[0], b[0], cin, sum[0], p[0], g[0] );
	adder1bit adder1bit1 ( a[1], b[1], carry[1], sum[1], p[1], g[1] );
	adder1bit adder1bit2 ( a[2], b[2], carry[2], sum[2], p[2], g[2] );
	adder1bit adder1bit3 ( a[3], b[3], carry[3], sum[3], p[3], g[3] );

	carrygu carrygu_ (p, g, cin, P, G, carry);

	assign cout = carry[4];

endmodule