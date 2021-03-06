#include "OPEN_RF.h"

#ifdef __MSP430_HAS_CC1101__

#define st(x)   do { x } while (__LINE__ == -1)
#define ENTER_CRITICAL_SECTION(x)       st(x = __get_interrupt_state(); __disable_interrupt(); )
#define EXIT_CRITICAL_SECTION(x)    __set_interrupt_state(x)

// *************************************************************************************************
// @fn          Strobe
// @brief       Send command to radio.
// @param       unsigned char strobe    Command to radio
// @return      statusByte                              Radio core status
// *************************************************************************************************

void Initialisation(void) {

reset();

RF1AIFG &= ~BIT4;           // Clear a pending interrupt
//RF1AIE |= BIT4;             // Enable the interrupt

}

uint8_t Strobe(uint8_t strobe)
{
    
    uint16_t int_state, gdo_state;
    uint8_t statusByte;
    // Check for valid strobe command
    if ((strobe == 0xBD) || ((strobe >= RF_SRES) && (strobe <= RF_SNOP)))
    {
        ENTER_CRITICAL_SECTION(int_state);
 RF1AIFCTL1 &= ~(RFSTATIFG);
  while (!(RF1AIFCTL1 & RFINSTRIFG)) ;
        /* // Clear the Status read flag
        RF1AIFCTL1 &= ~(RFSTATIFG);

        // Wait for radio to be ready for next instruction
        while (!(RF1AIFCTL1 & RFINSTRIFG)) ;

        // Write the strobe instruction
        if ((strobe >= RF_SRES) && (strobe <= RF_SNOP))
        {

            gdo_state = ReadReg(IOCFG2);         // buffer IOCFG2 state
            WriteReg(IOCFG2, 0x29);              // c-ready to GDO2

            RF1AINSTRB = strobe;
            if ((RF1AIN & 0x04) == 0x04)               // chip at sleep mode
            {
                if ((strobe == RF_SXOFF) || (strobe == RF_SPWD) || (strobe == RF_SWOR))
                {
                }
                else
                {
                    while ((RF1AIN & 0x04) == 0x04) ;  // c-ready ?
                    __delay_cycles(9800);              // Delay for ~810usec at 12MHz CPU clock
                }
            }
            WriteReg(IOCFG2, gdo_state);         // restore IOCFG2 setting
        }
        else                                           // chip active mode
        {
            RF1AINSTRB = strobe;
        }
        statusByte = RF1ASTATB;
        while (!(RF1AIFCTL1 & RFSTATIFG)) ; */
		
		RF1AINSTR1B = strobe;
		statusByte = RF1ASTATB;
		//while (!(RF1AIFCTL1 & RFSTATIFG));
		
        EXIT_CRITICAL_SECTION(int_state);
    }
    return statusByte;
}

// *************************************************************************************************
// @fn          ResetRadioCore
// @brief       Software reset radio core.
// @param       none
// @return      none
// *************************************************************************************************
void reset(void)
{
    volatile uint16_t i;
    uint8_t x;

    // Reset radio core
    Strobe(RF_SRES);
    // Wait before checking IDLE
    for (i = 0; i < 100; i++) ;
    do
    {
        x = Strobe(RF_SIDLE);
    }
    while ((x & 0x70) != 0x00);

    // Clear radio error register
    RF1AIFERR = 0;
}

// *************************************************************************************************
// @fn          ReadSingleReg
// @brief       Read byte from register.
// @param       none
// @return      none
// *************************************************************************************************
uint8_t ReadReg(uint8_t addr)
{
    unsigned char x;
    unsigned int int_state;

    ENTER_CRITICAL_SECTION(int_state);

    RF1AINSTR1B = (addr | RF_REGRD);
    x = RF1ADOUTB;

    EXIT_CRITICAL_SECTION(int_state);

    return x;
}

// *************************************************************************************************
// @fn          WriteSingleReg
// @brief       Write byte to register.
// @param       none
// @return      none
// *************************************************************************************************
void WriteReg(uint8_t addr, uint8_t value)
{
    volatile unsigned int i;
    unsigned int int_state;

    ENTER_CRITICAL_SECTION(int_state);

    while (!(RF1AIFCTL1 & RFINSTRIFG)) ;           // Wait for the Radio to be ready for the next
                                                   // instruction

    RF1AINSTRW = ((addr | RF_REGWR) << 8) + value; // Send address + Instruction
    while (!(RF1AIFCTL1 & RFDINIFG )) ;

    i = RF1ADOUTB;                                 // Reset RFDOUTIFG flag which contains status
                                                   // byte

    EXIT_CRITICAL_SECTION(int_state);
}

// *************************************************************************************************
// @fn          ReadBurstReg
// @brief       Read sequence of bytes from register.
// @param       none
// @return      none
// *************************************************************************************************
void ReadBurstReg(uint8_t addr, uint8_t* buffer, uint8_t count)
{
    unsigned int i;
    unsigned int int_state;

    ENTER_CRITICAL_SECTION(int_state);

    while (!(RF1AIFCTL1 & RFINSTRIFG)) ;     // Wait for the Radio to be ready for next instruction
    RF1AINSTR1B = (addr | RF_REGRD);         // Send address + Instruction

    for (i = 0; i < (count - 1); i++)
    {
        while (!(RFDOUTIFG & RF1AIFCTL1)) ;  // Wait for the Radio Core to update the RF1ADOUTB reg
       
	   buffer[i] = RF1ADOUT1B;              // Read DOUT from Radio Core + clears RFDOUTIFG
        // Also initiates auto-read for next DOUT byte
    }
    buffer[count - 1] = RF1ADOUTB;          // Store the last DOUT from Radio Core

    EXIT_CRITICAL_SECTION(int_state);
}

// *************************************************************************************************
// @fn          WriteBurstReg
// @brief       Write sequence of bytes to register.
// @param       none
// @return      none
// *************************************************************************************************
void WriteBurstReg(uint8_t addr, uint8_t *buffer, uint8_t count)
{
    // Write Burst works wordwise not bytewise - bug known already
    unsigned char i;
    unsigned int int_state;

    ENTER_CRITICAL_SECTION(int_state);

    while (!(RF1AIFCTL1 & RFINSTRIFG)) ;               // Wait for the Radio to be ready for next
                                                       // instruction
    RF1AINSTRW = ((addr | RF_REGWR) << 8) + buffer[0]; // Send address + Instruction

    for (i = 1; i < count; i++)
    {
        RF1ADINB = buffer[i];                          // Send data
        while (!(RFDINIFG & RF1AIFCTL1)) ;             // Wait for TX to finish
    }
    i = RF1ADOUTB;                                     // Reset RFDOUTIFG flag which contains status
                                                       // byte

    EXIT_CRITICAL_SECTION(int_state);
}

// *************************************************************************************************
// @fn          WritePATable
// @brief       Write data to power table
// @param       unsigned char value             Value to write
// @return      none
// *************************************************************************************************
/* void WritePATable(uint8_t value)
{
    unsigned char readbackPATableValue = 0;
    unsigned int int_state;

    ENTER_CRITICAL_SECTION(int_state);

    while (readbackPATableValue != value)
    {
        while (!(RF1AIFCTL1 & RFINSTRIFG)) ;
        RF1AINSTRW = 0x7E00 + value; // PA Table write (burst)

        while (!(RF1AIFCTL1 & RFINSTRIFG)) ;
        RF1AINSTRB = RF_SNOP;        // reset pointer

        while (!(RF1AIFCTL1 & RFINSTRIFG)) ;
        RF1AINSTRB = 0xFE;           // PA Table read (burst)

        while (!(RF1AIFCTL1 & RFDINIFG)) ;
        RF1ADINB = 0x00;             //dummy write

        while (!(RF1AIFCTL1 & RFDOUTIFG)) ;
        readbackPATableValue = RF1ADOUT0B;

        while (!(RF1AIFCTL1 & RFINSTRIFG)) ;
        RF1AINSTRB = RF_SNOP;
    }

    EXIT_CRITICAL_SECTION(int_state);
} */
void WritePATable(uint8_t PaTab[], uint8_t Size){
WriteBurstReg(RF_PATABWR,PaTab,Size);
}

#endif
