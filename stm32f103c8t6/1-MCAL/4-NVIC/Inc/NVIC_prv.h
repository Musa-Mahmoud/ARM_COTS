#ifndef NVIC_RRV_H_
#define NVIC_RRV_H_

#define ISER_REG_ACCESS             5U
#define ISER_BIT_ACCESS             0x1FU

#define ICER_REG_ACCESS             5U
#define ICER_BIT_ACCESS             0x1FU

#define ISPR_REG_ACCESS             5U
#define ISPR_BIT_ACCESS             0x1FU

#define ICPR_REG_ACCESS             5U
#define ICPR_BIT_ACCESS             0x1FU

#define IABR_REG_ACCESS             5U
#define IABR_BIT_ACCESS             0x1FU

#define IPR_REG_MASK                0xFFFU              
#define IPR_BITS_ACCESS             1U

#define USED_PRIORITY_BITS          4U

#define PRIORITY_MAX_VALUE          15U
#define PRIORITY_MIN_VALUE          0U

#endif /* NVIC_PRV_H_ */