////////////////////////////////////////////////////////////////////////////////
// Register bank
////////////////////////////////////////////////////////////////////////////////

module regbank #(parameter
	DATA_WIDTH=32,
	ADDR_WIDTH=5) (
	input                   clk_i,
	input                   rst_i,
	input                   we_i,
	input  [ADDR_WIDTH-1:0] waddr_i,
	input  [DATA_WIDTH-1:0] wdata_i,
	input  [ADDR_WIDTH-1:0] r0addr_i,
	output [DATA_WIDTH-1:0] r0data_o,
	input  [ADDR_WIDTH-1:0] r1addr_i,
	output [DATA_WIDTH-1:0] r1data_o);

	// Internal wires
	reg  [DATA_WIDTH-1:0]      r0data_o;
	reg  [DATA_WIDTH-1:0]      r1data_o;
	reg  [(2**ADDR_WIDTH)-1:0] reg_array_ce;
	wire [DATA_WIDTH-1:0]      reg_array [(2**ADDR_WIDTH)-1:0];

	// Register array
	genvar regidx;
	generate
		for (regidx = 0; regidx < (2**ADDR_WIDTH); regidx=regidx+1) begin
			wire reg_ce;
			assign reg_ce = we_i & reg_array_ce[regidx];
			register #(.DATA_WIDTH(DATA_WIDTH))
				reg_i (
					.clk_i(clk_i),
					.rst_i(rst_i),
					.ce_i(reg_ce),
					.d_i(wdata_i),
					.q_o(reg_array[regidx])
				) ;
		end
	endgenerate

	// Decoder
	always @(*) begin
		r0data_o     = reg_array[r0addr_i];
		r1data_o     = reg_array[r1addr_i];
		reg_array_ce = 1 << waddr_i;
	end

endmodule // register
