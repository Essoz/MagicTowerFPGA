# TCL File Generated by Component Editor 18.1
# Mon Jan 03 13:36:58 CST 2022
# DO NOT MODIFY


# 
# Player_Controller "Player_Controller" v2.3
# ZTY 2022.01.03.13:36:57
# Data Interface to the draw engine
# 

# 
# request TCL package from ACDS 16.1
# 
package require -exact qsys 16.1


# 
# module Player_Controller
# 
set_module_property DESCRIPTION "Data Interface to the draw engine"
set_module_property NAME Player_Controller
set_module_property VERSION 2.3
set_module_property INTERNAL false
set_module_property OPAQUE_ADDRESS_MAP true
set_module_property GROUP MagicTowerFPGA
set_module_property AUTHOR ZTY
set_module_property DISPLAY_NAME Player_Controller
set_module_property INSTANTIATE_IN_SYSTEM_MODULE true
set_module_property EDITABLE true
set_module_property REPORT_TO_TALKBACK false
set_module_property ALLOW_GREYBOX_GENERATION false
set_module_property REPORT_HIERARCHY false


# 
# file sets
# 
add_fileset QUARTUS_SYNTH QUARTUS_SYNTH "" ""
set_fileset_property QUARTUS_SYNTH TOP_LEVEL control_panel
set_fileset_property QUARTUS_SYNTH ENABLE_RELATIVE_INCLUDE_PATHS false
set_fileset_property QUARTUS_SYNTH ENABLE_FILE_OVERWRITE_MODE false
add_fileset_file control_panel.sv SYSTEM_VERILOG PATH IP/player_control/control_panel.sv TOP_LEVEL_FILE

add_fileset SIM_VERILOG SIM_VERILOG "" ""
set_fileset_property SIM_VERILOG TOP_LEVEL control_panel
set_fileset_property SIM_VERILOG ENABLE_RELATIVE_INCLUDE_PATHS false
set_fileset_property SIM_VERILOG ENABLE_FILE_OVERWRITE_MODE false
add_fileset_file control_panel.sv SYSTEM_VERILOG PATH IP/player_control/control_panel.sv


# 
# parameters
# 


# 
# display items
# 


# 
# connection point Clk
# 
add_interface Clk clock end
set_interface_property Clk clockRate 50000000
set_interface_property Clk ENABLED true
set_interface_property Clk EXPORT_OF ""
set_interface_property Clk PORT_NAME_MAP ""
set_interface_property Clk CMSIS_SVD_VARIABLES ""
set_interface_property Clk SVD_ADDRESS_GROUP ""

add_interface_port Clk Clk clk Input 1


# 
# connection point frame_clk
# 
add_interface frame_clk clock end
set_interface_property frame_clk clockRate 60
set_interface_property frame_clk ENABLED true
set_interface_property frame_clk EXPORT_OF ""
set_interface_property frame_clk PORT_NAME_MAP ""
set_interface_property frame_clk CMSIS_SVD_VARIABLES ""
set_interface_property frame_clk SVD_ADDRESS_GROUP ""

add_interface_port frame_clk frame_clk clk Input 1


# 
# connection point Reset
# 
add_interface Reset reset end
set_interface_property Reset associatedClock Clk
set_interface_property Reset synchronousEdges DEASSERT
set_interface_property Reset ENABLED true
set_interface_property Reset EXPORT_OF ""
set_interface_property Reset PORT_NAME_MAP ""
set_interface_property Reset CMSIS_SVD_VARIABLES ""
set_interface_property Reset SVD_ADDRESS_GROUP ""

add_interface_port Reset Reset reset Input 1


# 
# connection point Export_Data
# 
add_interface Export_Data conduit end
set_interface_property Export_Data associatedClock Clk
set_interface_property Export_Data associatedReset Reset
set_interface_property Export_Data ENABLED true
set_interface_property Export_Data EXPORT_OF ""
set_interface_property Export_Data PORT_NAME_MAP ""
set_interface_property Export_Data CMSIS_SVD_VARIABLES ""
set_interface_property Export_Data SVD_ADDRESS_GROUP ""

add_interface_port Export_Data EXPORT_CONFIG export_config Output 3872
add_interface_port Export_Data EXPORT_STATUS export_status Output 320
add_interface_port Export_Data KnightX knightx Output 8
add_interface_port Export_Data KnightY knighty Output 8


# 
# connection point HEX
# 
add_interface HEX conduit end
set_interface_property HEX associatedClock Clk
set_interface_property HEX associatedReset Reset
set_interface_property HEX ENABLED true
set_interface_property HEX EXPORT_OF ""
set_interface_property HEX PORT_NAME_MAP ""
set_interface_property HEX CMSIS_SVD_VARIABLES ""
set_interface_property HEX SVD_ADDRESS_GROUP ""

add_interface_port HEX HEX0 hex0 Output 7
add_interface_port HEX HEX1 hex1 Output 7
add_interface_port HEX HEX2 hex2 Output 7
add_interface_port HEX HEX3 hex3 Output 7
add_interface_port HEX HEX4 hex4 Output 7
add_interface_port HEX HEX5 hex5 Output 7
add_interface_port HEX HEX6 hex6 Output 7
add_interface_port HEX HEX7 hex7 Output 7


# 
# connection point Player_Slave
# 
add_interface Player_Slave avalon end
set_interface_property Player_Slave addressUnits WORDS
set_interface_property Player_Slave associatedClock Clk
set_interface_property Player_Slave associatedReset Reset
set_interface_property Player_Slave bitsPerSymbol 8
set_interface_property Player_Slave burstOnBurstBoundariesOnly false
set_interface_property Player_Slave burstcountUnits WORDS
set_interface_property Player_Slave explicitAddressSpan 0
set_interface_property Player_Slave holdTime 0
set_interface_property Player_Slave linewrapBursts false
set_interface_property Player_Slave maximumPendingReadTransactions 0
set_interface_property Player_Slave maximumPendingWriteTransactions 0
set_interface_property Player_Slave readLatency 0
set_interface_property Player_Slave readWaitStates 0
set_interface_property Player_Slave readWaitTime 0
set_interface_property Player_Slave setupTime 0
set_interface_property Player_Slave timingUnits Cycles
set_interface_property Player_Slave writeWaitTime 0
set_interface_property Player_Slave ENABLED true
set_interface_property Player_Slave EXPORT_OF ""
set_interface_property Player_Slave PORT_NAME_MAP ""
set_interface_property Player_Slave CMSIS_SVD_VARIABLES ""
set_interface_property Player_Slave SVD_ADDRESS_GROUP ""

add_interface_port Player_Slave AVL_ADDR address Input 8
add_interface_port Player_Slave AVL_READ read Input 1
add_interface_port Player_Slave AVL_WRITE write Input 1
add_interface_port Player_Slave AVL_CS chipselect Input 1
add_interface_port Player_Slave AVL_BYTE_EN byteenable Input 4
add_interface_port Player_Slave AVL_WRITEDATA writedata Input 32
add_interface_port Player_Slave AVL_READDATA readdata Output 32
set_interface_assignment Player_Slave embeddedsw.configuration.isFlash 0
set_interface_assignment Player_Slave embeddedsw.configuration.isMemoryDevice 0
set_interface_assignment Player_Slave embeddedsw.configuration.isNonVolatileStorage 0
set_interface_assignment Player_Slave embeddedsw.configuration.isPrintableDevice 0

