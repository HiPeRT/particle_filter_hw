############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
############################################################
open_project rm_kria
set_top RM
add_files ./RMTypes.hpp
add_files ./RMMapLoader.hpp
add_files ./RMDispatcher.hpp
add_files ./RMCore.hpp
add_files ./RMCompute.hpp
add_files ./RM.hpp
add_files ./RM.cpp
open_solution "solution1" -flow_target vivado
set_part {xck26-sfvc784-2LV-c}
create_clock -period 10 -name default
#config_export -display_name RM -format ip_catalog -rtl verilog -vivado_clock 10
#source "./rm_kria/solution1/directives.tcl"
#csim_design
csynth_design
#cosim_design
export_design -rtl verilog -format ip_catalog -display_name "RM"
