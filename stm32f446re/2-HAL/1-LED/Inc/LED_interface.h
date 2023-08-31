#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

#include <stdint.h>

typedef enum
{
    LED_SINK_CONNECTION = 0,
    LED_SOURCE_CONNECTION
} LED_Connection_t;

typedef struct LED
{
    uint8_t Port;
    uint8_t Pin;
    LED_Connection_t ConnectionType;
} LED_t;

uint8_t LED_u8TurnOn(LED_t *LedConfig);

uint8_t LED_u8TurnOff(LED_t *LedConfig);

uint8_t LED_u8Toggle(LED_t *LedConfig);

#endif /* LED_INTERFACE_H_ */
