#if VM_TRACE
	#include <verilated_vcd_c.h>
#endif
#include <verilated.h>
#include <string>
#include "Valu_32i.h"
#define STRING_(x) #x
#define STRING(x) STRING_(x)

vluint64_t main_time = 0;	// Current simulation time (64-bit unsigned)

int main(int argc, char **argv, char **env) {
	Verilated::commandArgs(argc, argv);
	Valu_32i* top = new Valu_32i;

	#if VM_TRACE			// If verilator was invoked with --trace
		Verilated::traceEverOn(true);	// Verilator must compute traced signals
		VL_PRINTF("Enabling waves...\n");
		VerilatedVcdC* tfp = new VerilatedVcdC;
		top->trace (tfp, 99);	// Trace 99 levels of hierarchy
		tfp->VerilatedVcdC::set_time_unit("1ps");
		tfp->VerilatedVcdC::set_time_resolution("1ps");
		tfp->open (STRING(VCD_FILE));	// Open the dump file
	#endif

	// while (!Verilated::gotFinish())
	// {
	// static int clk = 0;
	// clk = (clk+1) & 1;

	//uint32_t palentry = rand();
	// static uint32_t palentry = 0;
	// palentry+=1000;
	uint32_t a, b;
	for (int oper=0; oper<10; oper++) {
		a = rand();
		b = rand();
		top->oper_i = oper;
		top->a_i = a;
		top->b_i = b;
		top->eval(); 
		#if VM_TRACE
			if (tfp) tfp->dump (main_time);	// Create waveform trace for this timestamp
		#endif
		printf("\noper: %d, a: 0x%08X, b: 0x%08X, z: 0x%08X\n",oper,a,b,top->z_o);
		main_time++;
	}
	// }
	#if VM_TRACE
	    if (tfp) tfp->close();
	#endif
	delete top;
	exit(0);
}
