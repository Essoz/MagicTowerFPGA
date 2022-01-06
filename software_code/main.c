#include "io.h"
#include <stdio.h>
#include <sys/alt_dma.h>
#include "system.h"

void init_memory(unsigned int base, unsigned int len, unsigned int value)
{
    int i;
    for (i=0; i<len; i++)
    {
        IOWR_8DIRECT(base, i, value);
        printf("Init: memory base 0x%x, address 0x%x, value 0x%x\n", base, i, value);
    }
}

void read_memory(unsigned int base, unsigned int len)
{
    int i;
    for (i=0; i<len; i++)
    {
        int value = IORD_8DIRECT(base, i);
        printf(" Read: memory base 0x%x, address 0x%x, value 0x%x\n", base, i, value);
    }
}

static volatile int rx_done = 0;
static void done(void *handle, void *data)
{
    rx_done++;
}

alt_8 *mem_to_buf(unsigned int src, int nBytes)
{
    alt_8 dst[nBytes];
    
    void *tx_data = (void *) alt_uncached_malloc(src);
    void *rx_data = (void *) alt_uncached_malloc(&dst);
    alt_dma_txchan txchan;
    alt_dma_rxchan rxchan;
    int rc;    
    
   /* Create the transmit channel */
    if ((txchan = alt_dma_txchan_open("/dev/dma")) == NULL)
    {
        printf("Failed to open transmit channel\n");
        exit (1);
    }

    /* Create the receive channel */
    if ((rxchan = alt_dma_rxchan_open("/dev/dma")) == NULL)
    {
        printf("Failed to open receive channel\n");
        exit (1);
    }

    /* Post the transmit request */
    if ((rc = alt_dma_txchan_send(txchan, tx_data, nBytes, NULL, NULL)) < 0)
    {
        printf("Failed to post transmit request, reason = %i\n", rc);
        exit (1);
    }

    /* Post the receive request */
    if ((rc = alt_dma_rxchan_prepare(rxchan, rx_data, nBytes, done, NULL)) < 0)
    {
        printf("Failed to post read request, reason = %i\n", rc);
        exit (1);
    }

    /* wait for transfer to complete */
    while (!rx_done);
    printf("Transfer successful!\n");
    
    if (memcmp(tx_data, rx_data, nBytes))
    {
        printf("Verification failed\n");
        exit (1);
    }
    alt_uncached_free(tx_data);
    alt_uncached_free(rx_data);   
    
    return dst;
}

int mem_to_mem(unsigned int src, unsigned int dst, int nBytes)
{
    void *tx_data = (void *) alt_uncached_malloc(src);
    void *rx_data = (void *) alt_uncached_malloc(dst);
    alt_dma_txchan txchan;
    alt_dma_rxchan rxchan;
    int rc;
    
    /* Create the transmit channel */
    if ((txchan = alt_dma_txchan_open("/dev/dma")) == NULL)
    {
        printf("Failed to open transmit channel\n");
        exit (1);
    }

    /* Create the receive channel */
    if ((rxchan = alt_dma_rxchan_open("/dev/dma")) == NULL)
    {
        printf("Failed to open receive channel\n");
        exit (1);
    }

    /* Post the transmit request */
    if ((rc = alt_dma_txchan_send(txchan, tx_data, nBytes, NULL, NULL)) < 0)
    {
        printf("Failed to post transmit request, reason = %i\n", rc);
        exit (1);
    }

    /* Post the receive request */
    if ((rc = alt_dma_rxchan_prepare(rxchan, rx_data, nBytes, done, NULL)) < 0)
    {
        printf("Failed to post read request, reason = %i\n", rc);
        exit (1);
    }

    /* wait for transfer to complete */
    while (!rx_done);
    printf("Transfer successful!\n");
    
    if (memcmp(tx_data, rx_data, nBytes))
    {
        printf("Verification failed\n");
        exit (1);
    }
    alt_uncached_free(tx_data);
    alt_uncached_free(rx_data);   
}

void test(double *x, double *y)
{
    *x = *y;
}

int main()
{
    unsigned int src = SDRAM_BASE;
    unsigned int dst = SDRAM_BASE + 0x10000;
    int nBytes = 0x10;
    
    printf("Before DMA\n");
    init_memory(src, nBytes, 0x33);
    read_memory(src, nBytes);
    
//    mem_to_mem(src, dst, nBytes);
    mem_to_buf(SDRAM_BASE, 0x10);

    printf("After DMA\n");
    read_memory(dst, nBytes);
    
    printf("\nExiting...%c", 4); // 4 will terminate the console    
    
    return 0;
} 