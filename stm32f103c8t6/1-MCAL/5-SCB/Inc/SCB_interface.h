#ifndef SCB_INTERFACE_H_
#define SCB_INTERFACE_H_

#include <stdint.h>

typedef enum
{
    SIXTEEN_GROUPS_ONE_SUBS = 3,
    EIGHT_GROUPS_TWO_SUBS,
    FOUR_GROUPS_FOUR_SUBS,
    TWO_GROUPS_EIGHT_SUBS,
    ONE_GROUPS_SIXTEEN_SUBS
} PriorityGrouping_t;

uint8_t SCB_u8SetPriorityGrouping(PriorityGrouping_t Copy_PriorityGrouping);

#endif /* SCB_INTERFACE_H_ */