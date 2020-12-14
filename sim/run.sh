verilator -Wall --cc --trace ../rtl/alu_32i.v --exe tb_alu_32i.cpp
make -C obj_dir -f Valu_32i.mk
obj_dir/Valu_32i

