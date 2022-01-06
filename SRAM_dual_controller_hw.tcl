# TCL File Generated by Component Editor 18.1
# Fri Dec 31 06:17:21 CST 2021
# DO NOT MODIFY


# 
# SRAM_dual_controller "SRAM_dual_controller" v1.0
#  2021.12.31.06:17:21
# 
# 

# 
# request TCL package from ACDS 16.1
# 
package require -exact qsys 16.1


# 
# module SRAM_dual_controller
# 
set_module_property DESCRIPTION ""
set_module_property NAME SRAM_dual_controller
set_module_property VERSION 1.0
set_module_property INTERNAL false
set_module_property OPAQUE_ADDRESS_MAP true
set_module_property GROUP MagicTowerFPGA
set_module_property AUTHOR ""
set_module_property DISPLAY_NAME SRAM_dual_controller
set_module_property INSTANTIATE_IN_SYSTEM_MODULE true
set_module_property EDITABLE true
set_module_property REPORT_TO_TALKBACK false
set_module_property ALLOW_GREYBOX_GENERATION false
set_module_property REPORT_HIERARCHY false


# 
# file sets
# 
add_fileset QUARTUS_SYNTH QUARTUS_SYNTH "" ""
set_fileset_property QUARTUS_SYNTH TOP_LEVEL SRAM_Multiplexer
set_fileset_property QUARTUS_SYNTH ENABLE_RELATIVE_INCLUDE_PATHS false
set_fileset_property QUARTUS_SYNTH ENABLE_FILE_OVERWRITE_MODE false
add_fileset_file SRAM_dual_controller.sv SYSTEM_VERILOG PATH IP/SRAM_dual_controller/SRAM_dual_controller.sv TOP_LEVEL_FILE


# 
# parameters
# 


# 
# display items
# 


# 
# connection point clock
# 
add_interface clock clock end
set_interface_property clock clockRate 0
set_interface_property clock ENABLED true
set_interface_property clock EXPORT_OF ""
set_interface_property clock PORT_NAME_MAP ""
set_interface_property clock CMSIS_SVD_VARIABLES ""
set_interface_property clock SVD_ADDRESS_GROUP ""

add_interface_port clock CLK clk Input 1


# 
# connection point reset
# 
add_interface reset reset end
set_interface_property reset associatedClock clock
set_interface_property reset synchronousEdges DEASSERT
set_interface_property reset ENABLED true
set_interface_property reset EXPORT_OF ""
set_interface_property reset PORT_NAME_MAP ""
set_interface_property reset CMSIS_SVD_VARIABLES ""
set_interface_property reset SVD_ADDRESS_GROUP ""

add_interface_port reset RESET reset Input 1


# 
# connection point SRAM
# 
add_interface SRAM conduit end
set_interface_property SRAM associatedClock clock
set_interface_property SRAM associatedReset ""
set_interface_property SRAM ENABLED true
set_interface_property SRAM EXPORT_OF ""
set_interface_property SRAM PORT_NAME_MAP ""
set_interface_property SRAM CMSIS_SVD_VARIABLES ""
set_interface_property SRAM SVD_ADDRESS_GROUP ""

add_interface_port SRAM SRAM_OE_N sram_oe_n Output 1
add_interface_port SRAM SRAM_ADDR sram_addr Output 20
add_interface_port SRAM SRAM_CE_N sram_ce_n Output 1
add_interface_port SRAM SRAM_DQ sram_dq Bidir 16
add_interface_port SRAM SRAM_LB_N sram_lb_n Output 1
add_interface_port SRAM SRAM_UB_N sram_ub_n Output 1
add_interface_port SRAM SRAM_WE_N sram_we_n Output 1


# 
# connection point hardware
# 
add_interface hardware conduit end
set_interface_property hardware associatedClock clock
set_interface_property hardware associatedReset ""
set_interface_property hardware ENABLED true
set_interface_property hardware EXPORT_OF ""
set_interface_property hardware PORT_NAME_MAP ""
set_interface_property hardware CMSIS_SVD_VARIABLES ""
set_interface_property hardware SVD_ADDRESS_GROUP ""

add_interface_port hardware HW_ADDR hw_addr Input 21
add_interface_port hardware HW_READDATA hw_readdata Output 8


# 
# connection point avalon_slave
# 
add_interface avalon_slave avalon end
set_interface_property avalon_slave addressUnits WORDS
set_interface_property avalon_slave associatedClock clock
set_interface_property avalon_slave associatedReset reset
set_interface_property avalon_slave bitsPerSymbol 8
set_interface_property avalon_slave burstOnBurstBoundariesOnly false
set_interface_property avalon_slave burstcountUnits WORDS
set_interface_property avalon_slave explicitAddressSpan 0
set_interface_property avalon_slave holdTime 0
set_interface_property avalon_slave linewrapBursts false
set_interface_property avalon_slave maximumPendingReadTransactions 0
set_interface_property avalon_slave maximumPendingWriteTransactions 0
set_interface_property avalon_slave readLatency 0
set_interface_property avalon_slave readWaitTime 1
set_interface_property avalon_slave setupTime 0
set_interface_property avalon_slave timingUnits Cycles
set_interface_property avalon_slave writeWaitTime 0
set_interface_property avalon_slave ENABLED true
set_interface_property avalon_slave EXPORT_OF ""
set_interface_property avalon_slave PORT_NAME_MAP ""
set_interface_property avalon_slave CMSIS_SVD_VARIABLES ""
set_interface_property avalon_slave SVD_ADDRESS_GROUP ""

add_interface_port avalon_slave AVL_ADDR address Input 21
add_interface_port avalon_slave AVL_READ read Input 1
add_interface_port avalon_slave AVL_READDATA readdata Output 8
add_interface_port avalon_slave AVL_WRITE write Input 1
add_interface_port avalon_slave AVL_WRITEDATA writedata Input 8
set_interface_assignment avalon_slave embeddedsw.configuration.isFlash 0
set_interface_assignment avalon_slave embeddedsw.configuration.isMemoryDevice 0
set_interface_assignment avalon_slave embeddedsw.configuration.isNonVolatileStorage 0
set_interface_assignment avalon_slave embeddedsw.configuration.isPrintableDevice 0


# 
# connection point clock_100mhz
# 
add_interface clock_100mhz clock end
set_interface_property clock_100mhz clockRate 0
set_interface_property clock_100mhz ENABLED true
set_interface_property clock_100mhz EXPORT_OF ""
set_interface_property clock_100mhz PORT_NAME_MAP ""
set_interface_property clock_100mhz CMSIS_SVD_VARIABLES ""
set_interface_property clock_100mhz SVD_ADDRESS_GROUP ""

add_interface_port clock_100mhz CLK2 clk Input 1

