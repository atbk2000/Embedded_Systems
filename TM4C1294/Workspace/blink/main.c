// Target: Texas Instruments TM4C1294NCPDT
// Toolchain: Code Composer Studio (CCS)

#include <stdint.h>
#include <stdbool.h>
#include <tm4c1294ncpdt.h>

void delay(void){

    volatile uint32_t i;

    for(i = 0; i < 1000000; i++){
        // Simple software delay
    }
}

int main(void)
{
    // Enable clock for GPIO Port N
    SYSCTL_RCGCGPIO_R |= (1U << 12);

    // Wait until port N is ready
    while((SYSCTL_PRGPIO_R & (1U << 12)) == 0){}

    // Configure PN1 as output
    GPIO_PORTN_DIR_R |= (1U << 1);

    // Enable digital function on PN1
    GPIO_PORTN_DEN_R |= (1U << 1);

    // Blink LED
    while(1){
        GPIO_PORTN_DATA_R ^= (1U << 1);
        delay();
    }
}