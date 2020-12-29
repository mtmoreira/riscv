################################################################################
# Makefile
#
# Revision | Author                            | Date     | Comment
#:---------|:----------------------------------|:---------|:--------------------
# 1.0      | Matheus Trevisan Moreira          | 12/16/20 | Initial Version
################################################################################
# Configuration
RTL_FOLDER=../rtl
TB_FOLDER=./tb
VERILATED_FOLDER=./verilator_sim
COMPILER=verilator
COMPILER_FLAGS=-Wall -Mdir $(VERILATED_FOLDER) --cc
WAVE_VIEWER=gtkwave
ifdef VCD
	COMPILER_FLAGS:=--trace -CFLAGS -DVCD_FILE=$(VCD) $(COMPILER_FLAGS)
endif
ifndef DESIGN
	DESIGN=alu_32i
endif
COMPILER_FLAGS:=$(COMPILER_FLAGS) $(RTL_FOLDER)/$(DESIGN).v --exe $(TB_FOLDER)/tb_$(DESIGN).cpp
CLEAN_FILES=verilator_sim vcd
################################################################################
# Main
help:
	@echo "Main Makefile for simulation"

compile:
	$(COMPILER) $(COMPILER_FLAGS)
	make -C $(VERILATED_FOLDER) -f V$(DESIGN).mk

sim_wave:
	mkdir -p vcd
	@make sim DESIGN=$(DESIGN) VCD=vcd/$(DESIGN).vcd
	@make wave VCD=vcd/$(DESIGN).vcd

sim: compile
	$(VERILATED_FOLDER)/V$(DESIGN)

clean:
	rm -rf $(CLEAN_FILES)

wave:
	$(WAVE_VIEWER) $(VCD)