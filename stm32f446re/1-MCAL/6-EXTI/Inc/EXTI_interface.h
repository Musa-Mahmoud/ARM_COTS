#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

#include <stdint.h>

typedef void (*EXTI_Callback)(void);

typedef enum
{
    EXTI0_LINE = 0,
    EXTI1_LINE,
    EXTI2_LINE,
    EXTI3_LINE,
    EXTI4_LINE,
    EXTI5_LINE,
    EXTI6_LINE,
    EXTI7_LINE,
    EXTI8_LINE,
    EXTI9_LINE,
    EXTI10_LINE,
    EXTI11_LINE,
    EXTI12_LINE,
    EXTI13_LINE,
    EXTI14_LINE,
    EXTI15_LINE,
    PVD_LINE,
    RTC_ALARM_LINE,
    OTG_FS_WKUP_LINE,
    OTG_HS_WKUP_LINE = 20,
    TAMP_STAMP_LINE,
    RTC_WKUP_LINE
} EXTI_LineNumber_t;

typedef enum
{
    RISING_EDGE,
    FALLING_EDGE,
    RISING_FALLING_EDGE
} EXTI_TriggerSource_t;

typedef enum
{
    DISABLED,
    ENABLED
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
