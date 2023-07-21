#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

#include <stdint.h>

typedef void (*EXTI_Callback)(void);

typedef struct
{
    uint32_t TriggerConfig;
    uint32_t EnableConfig;
    EXTI_Callback CallbackFunction;
} EXTI_Config_t;


uint8_t EXTI_u8Init(const EXTI_Config_t *Copy_EXTIConfig);

uint8_t EXTI_u8EnableINT();

uint8_t EXTI_u8DisableINT();

uint8_t EXTI_u8ClearPendingFlag();

uint8_t EXTI_u8ReadPendingFlag();

#endif /* EXTI_INTERFACE_H_ */
