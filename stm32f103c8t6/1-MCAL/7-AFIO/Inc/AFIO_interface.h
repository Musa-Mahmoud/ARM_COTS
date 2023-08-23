#ifndef AFIO_INTERFACE_H_
#define AFIO_INTERFACE_H_

#include <stdint.h>

typedef enum
{
    AFIO_EXTI0_LINE = 0,
    AFIO_EXTI1_LINE,
    AFIO_EXTI2_LINE,
    AFIO_EXTI3_LINE,
    AFIO_EXTI4_LINE,
    AFIO_EXTI5_LINE,
    AFIO_EXTI6_LINE,
    AFIO_EXTI7_LINE,
    AFIO_EXTI8_LINE,
    AFIO_EXTI9_LINE,
    AFIO_EXTI10_LINE,
    AFIO_EXTI11_LINE,
    AFIO_EXTI12_LINE,
    AFIO_EXTI13_LINE,
    AFIO_EXTI14_LINE,
    AFIO_EXTI15_LINE,
    AFIO_PVD_LINE,
    AFIO_RTC_ALARM_LINE,
    AFIO_USB_WAKEUP_LINE
} AFIO_LineNumber_t;

typedef enum
{
    AFIO_PORTA=0,
    AFIO_PORTB,
    AFIO_PORTC,
    AFIO_PORTD,
    AFIO_PORTE
} AFIO_Port_t;

uint8_t AFIO_u8SetEXTIPort(AFIO_LineNumber_t Copy_LineNumber, AFIO_Port_t Copy_Port);

#endif /* AFIO_INTERFACE_H_ */
