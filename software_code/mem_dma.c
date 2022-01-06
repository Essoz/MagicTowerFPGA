#include <stdio.h>
#include <stdlib.h>
#include "sys/alt_dma.h"
#include "system.h"
static volatile int rx_done = 0;
/*
* Callback function that obtains notification that the data
* is received.*/
static void done (void* handle, void* data)
{
rx_done++;
}
/*
*
*/
int main (int argc, char* argv[], char* envp[])
{
int rc;
alt_dma_txchan txchan;
alt_dma_rxchan rxchan;
void* tx_data = (void*) 0x901000; /* pointer to data to send */
void* rx_buffer = (void*) 0x902000; /* pointer to rx buffer */
/* Create the transmit channel */
if ((txchan = alt_dma_txchan_open("/dev/dma_0")) == NULL)
{
printf ("Failed to open transmit channel\n");
exit (1);
}
/* Create the receive channel */
if ((rxchan = alt_dma_rxchan_open("/dev/dma_0")) == NULL)
{
printf ("Failed to open receive channel\n"); 
exit (1); 
} 
/* Post the transmit request */ 
if ((rc = alt_dma_txchan_send (txchan, tx_data, 128, NULL, Null)) < 0)
{
printf ("Failed to post transmit request, reason = %i\n", rc);
exit (1);
}
/* Post the receive request */
if ((rc = alt_dma_rxchan_prepare (rxchan,
rx_buffer,
128,
done,
NULL}} < 0)
{
printf ("Failed to post read request, reason = %i\n", rc);
exit (1); 
}
/* wait for transfer to complete */
while (!rx_done); 
printf ("Transfer successful!\n"); 
return 0; 
}
