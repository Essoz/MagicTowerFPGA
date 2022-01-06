#include "memcpy_dma.h"

#include "altera_avalon_sgdma.h"
#include "altera_avalon_sgdma_descriptor.h"
#include "altera_avalon_sgdma_regs.h"
// Allocate descriptors in the descriptor_memory (onchip memory)
alt_sgdma_descriptor dma_descriptor 	__attribute__((section(".onchip")));
alt_sgdma_descriptor dma_descriptor_end	__attribute__((section(".onchip")));
alt_sgdma_dev* dma_device = NULL;

uint32_t memcpy_dma(volatile void* to, void* from, uint16_t size) {
	if(!dma_device) {
		dma_device = alt_avalon_sgdma_open("/dev/sgdma_0");
	}

	alt_avalon_sgdma_construct_mem_to_mem_desc(
			&dma_descriptor,		// dma descriptor
			&dma_descriptor_end,	// next (could be meaning less but needs to be properly allocated)
			from,					// source
			(void*) to,				// destination
			size,					// expected_bytes_transferred
			0,						// no fixed read address
			0						// no fixed write address
	);
	alt_avalon_sgdma_do_sync_transfer(dma_device, &dma_descriptor);
	return dma_descriptor.actual_bytes_transferred;
}
