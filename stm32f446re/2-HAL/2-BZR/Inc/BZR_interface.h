#ifndef BZR_INTERFACE_H_
#define BZR_INTERFACE_H_

#include <stdint.h>

typedef enum
{
    BZR_SINK_CONNECTION = 0,
    BZR_SOURCE_CONNECTION
} BZR_Connection_t;

typedef struct BZR
{
    uint8_t Port;
    uint8_t Pin;
    BZR_Connection_t ConnectionType;
} BZR_t;

uint8_t BZR_u8TurnOn(BZR_t *BzrConfig);

uint8_t BZR_u8TurnOff(BZR_t *BzrConfig);

uint8_t BZR_u8Toggle(BZR_t *BzrConfig);

uint8_t BZR_u8Beep(BZR_t *BzrConfig, uint16_t Copy_u16BeepsNumber, uint16_t Copy_u16BeepTimeMs);

#endif /* BZR_INTERFACE_H_ */
