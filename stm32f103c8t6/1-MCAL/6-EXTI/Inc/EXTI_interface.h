#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

#include <stdint.h>

typedef void (*EXTI_Callback)(void);

typedef enum
{
    EXTI_EXTI0_LINE = 0,
    EXTI_EXTI1_LINE,
    EXTI_EXTI2_LINE,
    EXTI_EXTI3_LINE,
    EXTI_EXTI4_LINE,
    EXTI_EXTI5_LINE,
    EXTI_EXTI6_LINE,
    EXTI_EXTI7_LINE,
    EXTI_EXTI8_LINE,
    EXTI_EXTI9_LINE,
    EXTI_EXTI10_LINE,
    EXTI_EXTI11_LINE,
    EXTI_EXTI12_LINE,
    EXTI_EXTI13_LINE,
    EXTI_EXTI14_LINE,
    EXTI_EXTI15_LINE,
    EXTI_PVD_LINE,
    EXTI_RTC_ALARM_LINE,
    EXTI_USB_WAKEUP_LINE
} EXTI_LineNumber_t;

typedef enum
{
    EXTI_RISING_EDGE,
    EXTI_FALLING_EDGE,
    EXTI_RISING_FALLING_EDGE
} EXTI_TriggerSource_t;

typedef enum
{
    EXTI_DISABLED,
    EXTI_ENABLED
} EXTI_InitState_t;

typedef struct
{
    EXTI_LineNumber_t LineNumber;
    EXTI_TriggerSource_t TriggerConfig;
    EXTI_InitState_t InitalState;
    EXTI_Callback CallbackFunction;
} EXTI_Config_t;

uint8_t EXTI_u8Init(const EXTI_Config_t *Copy_EXTIConfig);

uint8_t EXTI_u8SetTrigSrc(EXTI_LineNumber_t Copy_LineNumber, EXTI_TriggerSource_t Copy_TriggerSource);

uint8_t EXTI_u8EnableINT(EXTI_LineNumber_t Copy_LineNumber);

uint8_t EXTI_u8DisableINT(EXTI_LineNumber_t Copy_LineNumber);

uint8_t EXTI_u8ClearPendingFlag(EXTI_LineNumber_t Copy_LineNumber);

uint8_t EXTI_u8ReadPendingFlag(EXTI_LineNumber_t Copy_LineNumber, uint8_t *Copy_pu8FlagStatus);

#endif /* EXTI_INTERFACE_H_ */
