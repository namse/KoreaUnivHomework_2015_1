`include "sr_latch.v"

module DFF(clock, D, Q, Qbar);

	input clock, D;
	output Q, Qbar;

	wire NULL;
	wire sr_up_qbar;
	wire sr_down_qbar;
	wire sr_down_q;

	wire sr_down_sbar;

	assign sr_down_sbar = clock & sr_up_qbar;

	SR_latch srlatch_up(NULL, sr_up_qbar, sr_down_qbar, clock);
	SR_latch srlatch_down(sr_down_q, sr_down_qbar, sr_down_sbar, D);
	SR_latch srlatch_right(Q, Qbar, sr_up_qbar, sr_down_q);
endmodule