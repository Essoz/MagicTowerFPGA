/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'USB_kb_soc' in SOPC Builder design 'final_soc'
 * SOPC Builder design path: ../../final_soc.sopcinfo
 *
 * Generated: Mon Jan 03 20:07:41 CST 2022
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2_gen2"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x00008820
#define ALT_CPU_CPU_ARCH_NIOS2_R1
#define ALT_CPU_CPU_FREQ 50000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "tiny"
#define ALT_CPU_DATA_ADDR_WIDTH 0x10
#define ALT_CPU_DCACHE_LINE_SIZE 0
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_DCACHE_SIZE 0
#define ALT_CPU_EXCEPTION_ADDR 0x00000020
#define ALT_CPU_FLASH_ACCELERATOR_LINES 0
#define ALT_CPU_FLASH_ACCELERATOR_LINE_SIZE 0
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 50000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 0
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 0
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_ICACHE_SIZE 0
#define ALT_CPU_INST_ADDR_WIDTH 0x10
#define ALT_CPU_NAME "USB_kb_soc"
#define ALT_CPU_OCI_VERSION 1
#define ALT_CPU_RESET_ADDR 0x00000000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x00008820
#define NIOS2_CPU_ARCH_NIOS2_R1
#define NIOS2_CPU_FREQ 50000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "tiny"
#define NIOS2_DATA_ADDR_WIDTH 0x10
#define NIOS2_DCACHE_LINE_SIZE 0
#define NIOS2_DCACHE_LINE_SIZE_LOG2 0
#define NIOS2_DCACHE_SIZE 0
#define NIOS2_EXCEPTION_ADDR 0x00000020
#define NIOS2_FLASH_ACCELERATOR_LINES 0
#define NIOS2_FLASH_ACCELERATOR_LINE_SIZE 0
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 0
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 0
#define NIOS2_ICACHE_LINE_SIZE_LOG2 0
#define NIOS2_ICACHE_SIZE 0
#define NIOS2_INST_ADDR_WIDTH 0x10
#define NIOS2_OCI_VERSION 1
#define NIOS2_RESET_ADDR 0x00000000


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_ONCHIP_MEMORY2
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_SYSID_QSYS
#define __ALTERA_NIOS2_GEN2


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "Cyclone IV E"
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/USB_jtag_uart"
#define ALT_STDERR_BASE 0x9090
#define ALT_STDERR_DEV USB_jtag_uart
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/USB_jtag_uart"
#define ALT_STDIN_BASE 0x9090
#define ALT_STDIN_DEV USB_jtag_uart
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/USB_jtag_uart"
#define ALT_STDOUT_BASE 0x9090
#define ALT_STDOUT_DEV USB_jtag_uart
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "final_soc"


/*
 * USB_jtag_uart configuration
 *
 */

#define ALT_MODULE_CLASS_USB_jtag_uart altera_avalon_jtag_uart
#define USB_JTAG_UART_BASE 0x9090
#define USB_JTAG_UART_IRQ 5
#define USB_JTAG_UART_IRQ_INTERRUPT_CONTROLLER_ID 0
#define USB_JTAG_UART_NAME "/dev/USB_jtag_uart"
#define USB_JTAG_UART_READ_DEPTH 64
#define USB_JTAG_UART_READ_THRESHOLD 8
#define USB_JTAG_UART_SPAN 8
#define USB_JTAG_UART_TYPE "altera_avalon_jtag_uart"
#define USB_JTAG_UART_WRITE_DEPTH 64
#define USB_JTAG_UART_WRITE_THRESHOLD 8


/*
 * USB_onchip_mem configuration
 *
 */

#define ALT_MODULE_CLASS_USB_onchip_mem altera_avalon_onchip_memory2
#define USB_ONCHIP_MEM_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define USB_ONCHIP_MEM_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define USB_ONCHIP_MEM_BASE 0x0
#define USB_ONCHIP_MEM_CONTENTS_INFO ""
#define USB_ONCHIP_MEM_DUAL_PORT 0
#define USB_ONCHIP_MEM_GUI_RAM_BLOCK_TYPE "AUTO"
#define USB_ONCHIP_MEM_INIT_CONTENTS_FILE "final_soc_USB_onchip_mem"
#define USB_ONCHIP_MEM_INIT_MEM_CONTENT 1
#define USB_ONCHIP_MEM_INSTANCE_ID "NONE"
#define USB_ONCHIP_MEM_IRQ -1
#define USB_ONCHIP_MEM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define USB_ONCHIP_MEM_NAME "/dev/USB_onchip_mem"
#define USB_ONCHIP_MEM_NON_DEFAULT_INIT_FILE_ENABLED 0
#define USB_ONCHIP_MEM_RAM_BLOCK_TYPE "AUTO"
#define USB_ONCHIP_MEM_READ_DURING_WRITE_MODE "DONT_CARE"
#define USB_ONCHIP_MEM_SINGLE_CLOCK_OP 0
#define USB_ONCHIP_MEM_SIZE_MULTIPLE 1
#define USB_ONCHIP_MEM_SIZE_VALUE 32768
#define USB_ONCHIP_MEM_SPAN 32768
#define USB_ONCHIP_MEM_TYPE "altera_avalon_onchip_memory2"
#define USB_ONCHIP_MEM_WRITABLE 1


/*
 * USB_sys_id configuration
 *
 */

#define ALT_MODULE_CLASS_USB_sys_id altera_avalon_sysid_qsys
#define USB_SYS_ID_BASE 0x9088
#define USB_SYS_ID_ID 0
#define USB_SYS_ID_IRQ -1
#define USB_SYS_ID_IRQ_INTERRUPT_CONTROLLER_ID -1
#define USB_SYS_ID_NAME "/dev/USB_sys_id"
#define USB_SYS_ID_SPAN 8
#define USB_SYS_ID_TIMESTAMP 1641211182
#define USB_SYS_ID_TYPE "altera_avalon_sysid_qsys"


/*
 * button configuration
 *
 */

#define ALT_MODULE_CLASS_button altera_avalon_pio
#define BUTTON_BASE 0x9070
#define BUTTON_BIT_CLEARING_EDGE_REGISTER 0
#define BUTTON_BIT_MODIFYING_OUTPUT_REGISTER 0
#define BUTTON_CAPTURE 0
#define BUTTON_DATA_WIDTH 4
#define BUTTON_DO_TEST_BENCH_WIRING 0
#define BUTTON_DRIVEN_SIM_VALUE 0
#define BUTTON_EDGE_TYPE "NONE"
#define BUTTON_FREQ 50000000
#define BUTTON_HAS_IN 1
#define BUTTON_HAS_OUT 0
#define BUTTON_HAS_TRI 0
#define BUTTON_IRQ -1
#define BUTTON_IRQ_INTERRUPT_CONTROLLER_ID -1
#define BUTTON_IRQ_TYPE "NONE"
#define BUTTON_NAME "/dev/button"
#define BUTTON_RESET_VALUE 0
#define BUTTON_SPAN 16
#define BUTTON_TYPE "altera_avalon_pio"


/*
 * hal configuration
 *
 */

#define ALT_INCLUDE_INSTRUCTION_RELATED_EXCEPTION_API
#define ALT_MAX_FD 32
#define ALT_SYS_CLK none
#define ALT_TIMESTAMP_CLK none


/*
 * keycode configuration
 *
 */

#define ALT_MODULE_CLASS_keycode altera_avalon_pio
#define KEYCODE_BASE 0x9060
#define KEYCODE_BIT_CLEARING_EDGE_REGISTER 0
#define KEYCODE_BIT_MODIFYING_OUTPUT_REGISTER 0
#define KEYCODE_CAPTURE 0
#define KEYCODE_DATA_WIDTH 8
#define KEYCODE_DO_TEST_BENCH_WIRING 0
#define KEYCODE_DRIVEN_SIM_VALUE 0
#define KEYCODE_EDGE_TYPE "NONE"
#define KEYCODE_FREQ 50000000
#define KEYCODE_HAS_IN 0
#define KEYCODE_HAS_OUT 1
#define KEYCODE_HAS_TRI 0
#define KEYCODE_IRQ -1
#define KEYCODE_IRQ_INTERRUPT_CONTROLLER_ID -1
#define KEYCODE_IRQ_TYPE "NONE"
#define KEYCODE_NAME "/dev/keycode"
#define KEYCODE_RESET_VALUE 0
#define KEYCODE_SPAN 16
#define KEYCODE_TYPE "altera_avalon_pio"


/*
 * keycode_mem configuration
 *
 */

#define ALT_MODULE_CLASS_keycode_mem altera_avalon_onchip_memory2
#define KEYCODE_MEM_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define KEYCODE_MEM_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define KEYCODE_MEM_BASE 0x9098
#define KEYCODE_MEM_CONTENTS_INFO ""
#define KEYCODE_MEM_DUAL_PORT 1
#define KEYCODE_MEM_GUI_RAM_BLOCK_TYPE "AUTO"
#define KEYCODE_MEM_INIT_CONTENTS_FILE "final_soc_keycode_mem"
#define KEYCODE_MEM_INIT_MEM_CONTENT 1
#define KEYCODE_MEM_INSTANCE_ID "NONE"
#define KEYCODE_MEM_IRQ -1
#define KEYCODE_MEM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define KEYCODE_MEM_NAME "/dev/keycode_mem"
#define KEYCODE_MEM_NON_DEFAULT_INIT_FILE_ENABLED 0
#define KEYCODE_MEM_RAM_BLOCK_TYPE "AUTO"
#define KEYCODE_MEM_READ_DURING_WRITE_MODE "DONT_CARE"
#define KEYCODE_MEM_SINGLE_CLOCK_OP 1
#define KEYCODE_MEM_SIZE_MULTIPLE 1
#define KEYCODE_MEM_SIZE_VALUE 4
#define KEYCODE_MEM_SPAN 4
#define KEYCODE_MEM_TYPE "altera_avalon_onchip_memory2"
#define KEYCODE_MEM_WRITABLE 1


/*
 * otg_hpi_address configuration
 *
 */

#define ALT_MODULE_CLASS_otg_hpi_address altera_avalon_pio
#define OTG_HPI_ADDRESS_BASE 0x9050
#define OTG_HPI_ADDRESS_BIT_CLEARING_EDGE_REGISTER 0
#define OTG_HPI_ADDRESS_BIT_MODIFYING_OUTPUT_REGISTER 0
#define OTG_HPI_ADDRESS_CAPTURE 0
#define OTG_HPI_ADDRESS_DATA_WIDTH 2
#define OTG_HPI_ADDRESS_DO_TEST_BENCH_WIRING 0
#define OTG_HPI_ADDRESS_DRIVEN_SIM_VALUE 0
#define OTG_HPI_ADDRESS_EDGE_TYPE "NONE"
#define OTG_HPI_ADDRESS_FREQ 50000000
#define OTG_HPI_ADDRESS_HAS_IN 0
#define OTG_HPI_ADDRESS_HAS_OUT 1
#define OTG_HPI_ADDRESS_HAS_TRI 0
#define OTG_HPI_ADDRESS_IRQ -1
#define OTG_HPI_ADDRESS_IRQ_INTERRUPT_CONTROLLER_ID -1
#define OTG_HPI_ADDRESS_IRQ_TYPE "NONE"
#define OTG_HPI_ADDRESS_NAME "/dev/otg_hpi_address"
#define OTG_HPI_ADDRESS_RESET_VALUE 0
#define OTG_HPI_ADDRESS_SPAN 16
#define OTG_HPI_ADDRESS_TYPE "altera_avalon_pio"


/*
 * otg_hpi_cs configuration
 *
 */

#define ALT_MODULE_CLASS_otg_hpi_cs altera_avalon_pio
#define OTG_HPI_CS_BASE 0x9010
#define OTG_HPI_CS_BIT_CLEARING_EDGE_REGISTER 0
#define OTG_HPI_CS_BIT_MODIFYING_OUTPUT_REGISTER 0
#define OTG_HPI_CS_CAPTURE 0
#define OTG_HPI_CS_DATA_WIDTH 1
#define OTG_HPI_CS_DO_TEST_BENCH_WIRING 0
#define OTG_HPI_CS_DRIVEN_SIM_VALUE 0
#define OTG_HPI_CS_EDGE_TYPE "NONE"
#define OTG_HPI_CS_FREQ 50000000
#define OTG_HPI_CS_HAS_IN 0
#define OTG_HPI_CS_HAS_OUT 1
#define OTG_HPI_CS_HAS_TRI 0
#define OTG_HPI_CS_IRQ -1
#define OTG_HPI_CS_IRQ_INTERRUPT_CONTROLLER_ID -1
#define OTG_HPI_CS_IRQ_TYPE "NONE"
#define OTG_HPI_CS_NAME "/dev/otg_hpi_cs"
#define OTG_HPI_CS_RESET_VALUE 0
#define OTG_HPI_CS_SPAN 16
#define OTG_HPI_CS_TYPE "altera_avalon_pio"


/*
 * otg_hpi_data configuration
 *
 */

#define ALT_MODULE_CLASS_otg_hpi_data altera_avalon_pio
#define OTG_HPI_DATA_BASE 0x9040
#define OTG_HPI_DATA_BIT_CLEARING_EDGE_REGISTER 0
#define OTG_HPI_DATA_BIT_MODIFYING_OUTPUT_REGISTER 0
#define OTG_HPI_DATA_CAPTURE 0
#define OTG_HPI_DATA_DATA_WIDTH 16
#define OTG_HPI_DATA_DO_TEST_BENCH_WIRING 0
#define OTG_HPI_DATA_DRIVEN_SIM_VALUE 0
#define OTG_HPI_DATA_EDGE_TYPE "NONE"
#define OTG_HPI_DATA_FREQ 50000000
#define OTG_HPI_DATA_HAS_IN 1
#define OTG_HPI_DATA_HAS_OUT 1
#define OTG_HPI_DATA_HAS_TRI 0
#define OTG_HPI_DATA_IRQ -1
#define OTG_HPI_DATA_IRQ_INTERRUPT_CONTROLLER_ID -1
#define OTG_HPI_DATA_IRQ_TYPE "NONE"
#define OTG_HPI_DATA_NAME "/dev/otg_hpi_data"
#define OTG_HPI_DATA_RESET_VALUE 0
#define OTG_HPI_DATA_SPAN 16
#define OTG_HPI_DATA_TYPE "altera_avalon_pio"


/*
 * otg_hpi_r configuration
 *
 */

#define ALT_MODULE_CLASS_otg_hpi_r altera_avalon_pio
#define OTG_HPI_R_BASE 0x9030
#define OTG_HPI_R_BIT_CLEARING_EDGE_REGISTER 0
#define OTG_HPI_R_BIT_MODIFYING_OUTPUT_REGISTER 0
#define OTG_HPI_R_CAPTURE 0
#define OTG_HPI_R_DATA_WIDTH 1
#define OTG_HPI_R_DO_TEST_BENCH_WIRING 0
#define OTG_HPI_R_DRIVEN_SIM_VALUE 0
#define OTG_HPI_R_EDGE_TYPE "NONE"
#define OTG_HPI_R_FREQ 50000000
#define OTG_HPI_R_HAS_IN 0
#define OTG_HPI_R_HAS_OUT 1
#define OTG_HPI_R_HAS_TRI 0
#define OTG_HPI_R_IRQ -1
#define OTG_HPI_R_IRQ_INTERRUPT_CONTROLLER_ID -1
#define OTG_HPI_R_IRQ_TYPE "NONE"
#define OTG_HPI_R_NAME "/dev/otg_hpi_r"
#define OTG_HPI_R_RESET_VALUE 0
#define OTG_HPI_R_SPAN 16
#define OTG_HPI_R_TYPE "altera_avalon_pio"


/*
 * otg_hpi_reset configuration
 *
 */

#define ALT_MODULE_CLASS_otg_hpi_reset altera_avalon_pio
#define OTG_HPI_RESET_BASE 0x9000
#define OTG_HPI_RESET_BIT_CLEARING_EDGE_REGISTER 0
#define OTG_HPI_RESET_BIT_MODIFYING_OUTPUT_REGISTER 0
#define OTG_HPI_RESET_CAPTURE 0
#define OTG_HPI_RESET_DATA_WIDTH 1
#define OTG_HPI_RESET_DO_TEST_BENCH_WIRING 0
#define OTG_HPI_RESET_DRIVEN_SIM_VALUE 0
#define OTG_HPI_RESET_EDGE_TYPE "NONE"
#define OTG_HPI_RESET_FREQ 50000000
#define OTG_HPI_RESET_HAS_IN 0
#define OTG_HPI_RESET_HAS_OUT 1
#define OTG_HPI_RESET_HAS_TRI 0
#define OTG_HPI_RESET_IRQ -1
#define OTG_HPI_RESET_IRQ_INTERRUPT_CONTROLLER_ID -1
#define OTG_HPI_RESET_IRQ_TYPE "NONE"
#define OTG_HPI_RESET_NAME "/dev/otg_hpi_reset"
#define OTG_HPI_RESET_RESET_VALUE 0
#define OTG_HPI_RESET_SPAN 16
#define OTG_HPI_RESET_TYPE "altera_avalon_pio"


/*
 * otg_hpi_w configuration
 *
 */

#define ALT_MODULE_CLASS_otg_hpi_w altera_avalon_pio
#define OTG_HPI_W_BASE 0x9020
#define OTG_HPI_W_BIT_CLEARING_EDGE_REGISTER 0
#define OTG_HPI_W_BIT_MODIFYING_OUTPUT_REGISTER 0
#define OTG_HPI_W_CAPTURE 0
#define OTG_HPI_W_DATA_WIDTH 1
#define OTG_HPI_W_DO_TEST_BENCH_WIRING 0
#define OTG_HPI_W_DRIVEN_SIM_VALUE 0
#define OTG_HPI_W_EDGE_TYPE "NONE"
#define OTG_HPI_W_FREQ 50000000
#define OTG_HPI_W_HAS_IN 0
#define OTG_HPI_W_HAS_OUT 1
#define OTG_HPI_W_HAS_TRI 0
#define OTG_HPI_W_IRQ -1
#define OTG_HPI_W_IRQ_INTERRUPT_CONTROLLER_ID -1
#define OTG_HPI_W_IRQ_TYPE "NONE"
#define OTG_HPI_W_NAME "/dev/otg_hpi_w"
#define OTG_HPI_W_RESET_VALUE 0
#define OTG_HPI_W_SPAN 16
#define OTG_HPI_W_TYPE "altera_avalon_pio"

#endif /* __SYSTEM_H_ */
