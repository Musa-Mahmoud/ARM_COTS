#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_

#include <stdint.h>

#define GPIO_OK          1
#define GPIO_NOT_OK      0

/********************************
 * @Port_t enum
 *
 */
typedef enum
{
    GPIO_PORTA=0,
    GPIO_PORTB,
    GPIO_PORTC,
    GPIO_PORTD,
    GPIO_PORTE
} Port_t;

/********************************
 * @Pin_t enum
 *
 */
typedef enum
{
    GPIO_PIN0=0,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7,
    GPIO_PIN8,
    GPIO_PIN9,
    GPIO_PIN10,
    GPIO_PIN11,
    GPIO_PIN12,
    GPIO_PIN13,
    GPIO_PIN14,
    GPIO_PIN15
} Pin_t;

/********************************
 * @PinVal_t enum
 *
 */
typedef enum
{
    GPIO_PIN_LOW=0,
    GPIO_PIN_HIGH
} PinVal_t;

typedef enum
{
    GPIO_INPUT=0,
    GPIO_OUTPUT_10MHZ,
    GPIO_OUTPUT_2MHZ,
    GPIO_OUTPUT_50MHZ
} Mode_t;

typedef enum
{
    GPIO_PULLDOWN = 0,
    GPIO_PULLUP,
} PullUpDown_t;

typedef enum
{
    GPIO_INPUT_ANALOG = 0,
    GPIO_INPUT_FLOATING,
    GPIO_INPUT_PULL_UP_DOWN,
    GPIO_OUTPUT_PUSH_PULL = 0,
    GPIO_OUTPUT_OPEN_DRAIN,
    GPIO_ALT_FUNC_PUSH_PULL,
    GPIO_ALT_FUNC_OPEN_DRAIN,
} InputOutputConfig_t;

typedef struct
{
    Port_t Port;
    Pin_t PinNum;
    Mode_t Mode;
    InputOutputConfig_t PinCnf;
    PinVal_t PinInitValue;
    PullUpDown_t PullType;
} GPIO_PinConfig_t;


uint8_t GPIO_u8PinInit(const GPIO_PinConfig_t *PinConfig);

uint8_t GPIO_u8SetPinValue(Port_t Port, Pin_t PinNum, PinVal_t PinVal);

uint8_t GPIO_u8TogglePinValue(Port_t Port, Pin_t PinNum);

uint8_t GPIO_u8ReadPinValue(Port_t Port, Pin_t PinNum, PinVal_t *PinVal);

#endif /* GPIO_INTERFACE_H_ */
