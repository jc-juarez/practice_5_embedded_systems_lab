#include <bcm2835.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MODE_READ 0
#define MODE_WRITE 1

#define MAX_LEN 256

int main(void) {
	
	uint16_t clk_div = BCM2835_I2C_CLOCK_DIVIDER_148;
	uint8_t slave_address1 = 0x68;
	uint8_t slave_address2 = 0x4d;
	uint32_t len1 = 0;
	uint32_t len2 = 0;
	
	char buf[MAX_LEN];
	int i = 0;
	uint8_t data;
	
	char wbuf[MAX_LEN];
	memset(wbuf, 0, sizeof(wbuf));
	
	
	// Date and time
	bcm2835_i2c_setSlaveAddress(slave_address1);
    bcm2835_i2c_setClockDivider(clk_div);
	data = bcm2835_i2c_write(wbuf, 1);
	
	for (i=0; i<MAX_LEN; i++) buf[i] = 'n';
    	data = bcm2835_i2c_read(buf, 7);  
    	for (i=0; i<MAX_LEN; i++)
    		if(buf[i] != 'n') printf("Read Buf[%d] = %x\n", i, buf[i]);
}
