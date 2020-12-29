#if VM_TRACE
	#include <verilated_vcd_c.h>
#endif
#include <verilated.h>
#include <string>
#include "Vregbank.h"
#define STRING_(x) #x
#define STRING(x) STRING_(x)
#define SIM_TIME     100000
#define RST_TIME      10000
#define CLOCK_PERIOD   1000

vluint64_t main_time = 0;	// Current simulation time (64-bit unsigned)

int main(int argc, char **argv, char **env) {
	Verilated::commandArgs(argc, argv);
	Vregbank* top = new Vregbank;

	#if VM_TRACE			// If verilator was invoked with --trace
		Verilated::traceEverOn(true);	// Verilator must compute traced signals
		VL_PRINTF("Enabling waves...\n");
		VerilatedVcdC* tfp = new VerilatedVcdC;
		top->trace (tfp, 99);	// Trace 99 levels of hierarchy
		tfp->VerilatedVcdC::set_time_unit("1ps");
		tfp->VerilatedVcdC::set_time_resolution("1ps");
		tfp->open (STRING(VCD_FILE));	// Open the dump file
	#endif

	uint32_t clk;
	uint32_t rst;
	uint32_t we;
	uint32_t waddr;
	uint32_t wdata;
	uint32_t r0addr;
	uint32_t r1addr;
	clk = 0;
	rst = 1;
	while (main_time <= SIM_TIME)
	{
		if (main_time % (CLOCK_PERIOD/2) == 0) {
			clk = (clk + 1) & 1;
		}
		top->clk_i = clk;
		top->eval();
		if (main_time >= RST_TIME) {
			rst = 0;
		}
		we = rand() % 2;
		waddr = rand() % 32;
		wdata = rand();
		r0addr = rand() % 32;
		r1addr = rand() % 32;
		top->rst_i = rst;
		top->we_i = we;
		top->waddr_i = waddr;
		top->wdata_i = wdata;
		top->r0addr_i = r0addr;
		top->r1addr_i = r1addr;
		#if VM_TRACE
			if (tfp) tfp->dump (main_time);	// Create waveform trace for this timestamp
		#endif
		// printf("\noper: %d, a: 0x%08X, b: 0x%08X, z: 0x%08X\n",oper,a,b,top->z_o);
		main_time++;
	}
	// }
	#if VM_TRACE
	    if (tfp) tfp->close();
	#endif
	delete top;
	exit(0);
}
