#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_

#include <stdint.h>

typedef enum
{
    CLCD_MODE_4BIT = 4,
    CLCD_MODE_8BIT = 8
} CLCD_Mode_t;

typedef struct 
{
    uint8_t *DataPorts;         /* Ports must be at this order: D0, D1, D2, D3, D4, D5, D6, D7. From D4 to D7 if 4-bit mode is used */
    uint8_t *CtrlPorts;         /* Ports must be at this order: RS, R/W, EN                                                         */
    uint8_t *DataPins;          /* Pins must be at this order: D0, D1, D2, D3, D4, D5, D6, D7. From D4 to D7 if 4-bit mode is used  */
    uint8_t *CtrlPins;          /* Pins must be at this order: RS, R/W, EN                                                          */
    CLCD_Mode_t Mode;
} CLCD_Config_t;

/* Public Functions Prototype */

void CLCD_voidSendCommand(const CLCD_Config_t *Copy_CLCDConfig, uint8_t Copy_u8Command);

void CLCD_voidSendData(const CLCD_Config_t *Copy_CLCDConfig, uint8_t Copy_u8Data);

void CLCD_voidInit(const CLCD_Config_t *Copy_CLCDConfig);

void CLCD_voidSendString(const CLCD_Config_t *Copy_CLCDConfig, const char *Copy_pcString);

void CLCD_voidGoToXY(const CLCD_Config_t *Copy_CLCDConfig, uint8_t Copy_u8XPos, uint8_t Copy_u8YPos);

void CLCD_voidWriteSpecialCharacter(const CLCD_Config_t *Copy_CLCDConfig, uint8_t *Copy_pu8Pattern, uint8_t Copy_u8PatternNumber, uint8_t Copy_u8XPos, uint8_t Copy_u8YPos);

void CLCD_voidWriteNumber(const CLCD_Config_t *Copy_CLCDConfig, uint32_t Copy_u32Number);

void CLCD_voidClearDisplay(const CLCD_Config_t *Copy_CLCDConfig);

#endif /* CLCD_INTERFACE_H_ */
