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
SIMULATOR=verilator_sim
SIMULATOR_FLAGS=
COMPILER=verilator
COMPILER_FLAGS=-Wall -Mdir $(SIMULATOR) --cc
WAVE_VIEWER=gtkwave
ifdef VCD
	COMPILER_FLAGS:=--trace -CFLAGS -DVCD_FILE=$(VCD) $(COMPILER_FLAGS)
endif
ifndef DESIGN
	DESIGN=alu_32i
endif
ifeq ($(DESIGN),alu_32i)
	COMPILER_FLAGS:=$(COMPILER_FLAGS) $(RTL_FOLDER)/alu_32i.v --exe $(TB_FOLDER)/tb_alu_32i.cpp
	COMPILER_FLAGS:=$(COMPILER_FLAGS) ; make -C $(SIMULATOR) -f Valu_32i.mk
	SIMULATOR:=$(SIMULATOR)/Valu_32i
endif
CLEAN_FILES=verilator_sim vcd
################################################################################
# Main
help:
	@echo "Main Makefile for simulation"

compile:
	$(COMPILER) $(COMPILER_FLAGS)

sim_wave:
	mkdir -p vcd
	make sim DESIGN=$(DESIGN) VCD=vcd/$(DESIGN).vcd
	make wave VCD=vcd/$(DESIGN).vcd

sim: compile
	$(SIMULATOR) $(SIMULATOR_FLAGS)

clean:
	rm -rf $(CLEAN_FILES)

wave:
	$(WAVE_VIEWER) $(VCD)