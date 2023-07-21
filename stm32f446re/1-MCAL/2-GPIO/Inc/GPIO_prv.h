#ifndef GPIO_PRV_H_
#define GPIO_PRV_H_


#define VALID       1
#define NOT_VALID   0

#define GPIO_PERIPHERLA_NUM		8U

#define MODER_MASK				0b11U
#define MODER_PIN_ACCESS		2U

#define PUPDR_MASK				0b11U
#define PUPDR_PIN_ACCESS		2U

#define OTYPER_MASK				0b01U

#define OSPEEDR_MASK			0b11U
#define OSPEEDR_PIN_ACCESS		2U

#define AFR_MASK			    0b1111U
#define AFR_PIN_ACCESS		    4U
#define AFR_PIN_SHIFTING	    8U

#define BSRR_RESET_POS          16U

#endif /* GPIO_PRV_H_ */
