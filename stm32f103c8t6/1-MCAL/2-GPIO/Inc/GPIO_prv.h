#ifndef GPIO_PRV_H_
#define GPIO_PRV_H_


#define VALID       1
#define NOT_VALID   0

#define GPIO_PERIPHERLA_NUM		5U

#define CR_REG_ACCESS           3U
#define CR_PIN_ACCESS           4U
#define CR_REG_MASK             0x7U
#define CR_REG_NUM              (PinConfig->PinNum >> CR_REG_ACCESS)
#define CR_BIT_NUM              (PinConfig->PinNum & CR_REG_MASK)

#define MODE_MASK				0b11U
#define MODE_PIN_ACCESS		    4U

#define CNF_MASK			    0b11U
#define CNF_PIN_ACCESS		    4U
#define CNF_POS     		    2U

#define PUPDR_MASK				0b11U
#define PUPDR_PIN_ACCESS		2U

#define OTYPER_MASK				0b01U

#define AFR_MASK			    0b1111U
#define AFR_PIN_ACCESS		    4U
#define AFR_PIN_SHIFTING	    8U

#define BSRR_RESET_POS          16U

#endif /* GPIO_PRV_H_ */
