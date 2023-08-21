#ifndef SYSTICK_PRV_H_
#define SYSTICK_PRV_H_

/* Private Macros Defintions */
#define TIMER_TOP_VALUE                 (16777215UL)
#define UINT_MAX_VALUE                  (4294967295UL)

#define ENABLE_SYSTICK                  (1U)
#define DISABLE_SYSTICK                 (0U)

#define FLAG_UP                         (1U)
#define FLAG_DOWN                       (0U)

#define INITIALIZED                     (1U)
#define NOT_INITIALIZED                 (0U)

#define ENABLE_POS                      (0U)

#define TICKINT_POS                     (1U)

#define CLKSOURCE_POS                   (2U)

#define COUNTFLAG_POS                   (16U)

#define CLKSOURCE_TICKINT_ENABLE_MASK   (0x07U)

#define SYSCLK_MHZ                      (8UL)
#define SYSTICK_PRESCALER               (8UL)
#define TICK_TIME_NS                    (SYSTICK_PRESCALER * 1000UL / SYSCLK_MHZ)

#define ZERO_UNDERFLOWS                 (0U)

/* Private Functions Defintion */
static void Systick_Init(void);

#endif /* SYSTICK_PRV_H_ */