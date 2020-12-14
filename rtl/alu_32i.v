////////////////////////////////////////////////////////////////////////////////
// ALU
////////////////////////////////////////////////////////////////////////////////

module alu_32i #(parameter
	DATA_WIDTH=32,
	OPER_WIDTH=4)(
	input  [OPER_WIDTH-1:0] oper_i,
	input  [DATA_WIDTH-1:0] a_i,
	input  [DATA_WIDTH-1:0] b_i,
	output [DATA_WIDTH-1:0] z_o);

	always @(*)	begin
		case(oper_i)
			0: // Addition
				z_o = a_i + b_i ;
			1: // Subtraction
				z_o = a_i - b_i ;
			2: // AND
				z_o = a_i & b_i ;
			3: // OR
				z_o = a_i | b_i ;
			4: // XOR
				z_o = a_i ^ b_i ;
			5: // Logical shift left
				z_o = a_i << 1;
			6: // Logical shift right
				z_o = a_i >> 1;
			7: // Arithmetic shift right
				z_o = a_i >> b_i;
			8: // Greater comparison
				z_o = (a_i > b_i) ? 1 : 0 ;
			9: // Equal comparison
				z_o = (a_i == b_i) ? 1 : 0 ;
			default: z_o = a_i + b_i ; 
		endcase
	end

endmodule // alu
