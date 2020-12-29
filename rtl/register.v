////////////////////////////////////////////////////////////////////////////////
// Register
////////////////////////////////////////////////////////////////////////////////

module register #(parameter
	DATA_WIDTH=32)(
	input                   clk_i,
	input                   rst_i,
	input                   ce_i,
	input  [DATA_WIDTH-1:0] d_i,
	output [DATA_WIDTH-1:0] q_o);

	reg [DATA_WIDTH-1:0] q_o;

	always @(posedge clk_i or posedge rst_i) begin
		if (rst_i == 1'b1) begin
			q_o <= '0;
		end else begin
			if (ce_i == 1'b1) begin
				q_o <= d_i;
			end
		end
	end

endmodule // register
