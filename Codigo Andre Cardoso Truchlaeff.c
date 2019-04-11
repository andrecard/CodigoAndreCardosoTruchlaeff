#include <stdio.h>
#include <stdint.h>

/* Test Description
 * -----------------
 * You have to write a write data routine for a UART device. The UART is a memmory
 * mapped device at the address 0xFC000000 on an embedded platform.
 * To access the memory, use the functions stub_memwrite. This 
 * functions bypass the operating system and access the memory of the device.

 * This peripheral is controlled by the following 32 bit registers (offsets given)
 
 * BRR: Baud rate register Offset: 0x4 
 * - Selects the baud rate and configure UART device
 *
 * TER: Transmit enable register Offset: 0x8
 *  - Bit 23 in this register enables the transmit operation. When bit 23 is set to 1, 
 *    data in TDR[0:8] is sent via UART. Imediately After that, bit 23 is automatically set to 0.
 *
 * RER: Receive  enabel register Offset: 0xC
 * - Bits 3 and 5 notify overrun and framing error and need to be cleared upon reset
 * 
 * IER: Interrupt enable register Offset: 0x10
 * - Bit 14 and 15 enable TX and RX interrupts
 *
 * TDR: Transmit data register     Offset: 0x14
 *  - Contains data to be transmitted via UART
 *  TDR[0:8] Byte to be transmited when transmit enable register bit 23 is set to 1.
 *  TDR[9:32] Reserved
 *
 *
 * RDR: Receive data register     Offset: 0x18
 *  - Contains data received via UART
 *
 *
 * This test have 3 tasks. You should be able to answer it in two hours.
 * 
 * 
 * 
 **/

/**
 *  Data structure containing UART parameters including base address and other settings (supressed).
 * */
typedef struct UART_HANDLE {
  /**
   * Base mememory address. To access the correct device memory register address, you need to sum 
   * the base address with the offsets.
   **/
   
  uint32_t base_mem_addr;
  uint32_t Reg_write_TDR; 
  uint32_t Reg_send_TDR; 
    
} UART_HANDLE;


/**
  This functions writes to the memory address the value of val.
  \param mem_addr Absolute address to memory.
  \param val Value to be written in memory.
*/

void stub_memwrite(uint32_t mem_addr, uint32_t val)
{
	
		if(mem_addr== 0xFC000014 ){
			printf("You put %c in TDR \n", val ); // this tell you that you put the right data in TDR		
		}
		if(mem_addr== 0xFC000008 ){
			printf("You transmited the data in TDR\n");	// this tell you that the data was sended	
		}		
		
	
	
  /* Task 3 (optional): 
    Write a test function for the data here. 
    You could print the values received or create the appropriated code to test if the
    writen values to memory are correct here.
  */
}

/**
  Initialize the UART device.
  \param h Pointer to UART_HANDLE handle;
*/
void init_uart(UART_HANDLE *h)
{
  /* Initialize the handle to be accessed by stubs after that*/
  
  h->base_mem_addr = 0xFC000000;
  h->Reg_write_TDR = 0xFC000014; // value of registrer to write in TDR
  h->Reg_send_TDR  = 0xFC000008; // value of registrer to send the value in TDR 
  
  /* This function also configure the device using BRR and other registers, 
   *  but that code was supressed here. Consider that this initialization is done here. 
   YOU DO NOT NEED TO FILL THIS FUNCTION. */
}


/**
  Write (send) data to UART device.
  \param h Pointer to UART_HANDLE handle
  \param data Pointer to data that will be sent
  \param size Size in bytes of the data pointer
*/
void write_uart(UART_HANDLE *h, void *data, int size) 
{
	int i;
	char *valor = (char*) data; // transform a void * pointer in a string
	
	
	for(i=0;i<size;i++){
		
		stub_memwrite(h->Reg_write_TDR, valor[i]);		// Put data in  TDR[0:8]	 	
		stub_memwrite(h->Reg_send_TDR, 0x400000);		// Enables Transmit the data in TDR[0:8] setting bit 23
		 
	}
	

	 
	
  /* Task 2: You need to fill this function with the appropriated code to write the UART.
  ATTENTION TO THIS VERY IMPORTANT HINT: Make the things as simple as possible. 
  
  - You DO NOT need to handle interrupts;
  - You DO NOT need to read memory, only write;
  - Use stub_memwrite to access the device memory;
  - Remember: To access the correct registers, always sum the base address with the offsets.
   */
}


int main(int argc, char *argv[])
{
  UART_HANDLE handle;
  
  
  char text[] = "Hello World";


  init_uart(&handle);

	
  write_uart(&handle, text , strlen(text)); // considering sending only strings i can use strlen() for the size of text

	
	
  /* Task 1: Write an example of write_uart usage in the next line. */
  	
//	write_uart(UART_HANDLE *h, void *data, int size)


  return 0;
}

