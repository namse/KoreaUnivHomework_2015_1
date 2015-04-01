module carrygu (p, g, c0, P, G, c);
	input [3:0] p, g;
	input c0;
	output P, G; 
	output [4:1]c;

	wire [3:0] p, g;
	
	assign c[1] = g[0] | ( p[0] & c0 );
	assign c[2] = g[1] | ( p[1] & c[1] );
	assign c[3] = g[2] | ( p[2] & c[2] );
	assign c[4] = g[3] | ( p[3] & c[3] );
	
	assign G = g[3] | ( p[3] & g[2] ) | ( p[3] & p[2] & g[1] ) | ( p[3] & p[2] & p[1] & g[0] );
	assign P = p[3] & p[2] & p[1] & p[0];
endmodule