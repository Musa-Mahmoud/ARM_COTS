#ifndef DMA_RRV_H_
#define DMA_RRV_H_

#define INVALID                     (0U)
#define VALID                       (1U)

#define OVER                        (0U)
#define NOT_OVER                    (1U)

#define FLAG_NOT_RAISED             (0U)
#define FLAG_RAISED                 (1U)

#define LOW_REG_INDEX               (0U)
#define HIGH_REG_INDEX              (1U)

#define DMA_PERIPHERAL_NUMBERS      (2U)
#define STREAM_NUMBERS              (8U)
#define CALLBACK_NUMBERS            (5U)

#define CR                          (0U)    /* Configuration Register       */
#define NDTR                        (1U)    /* Number of Data Register      */
#define PAR                         (2U)    /* Peripheral Address Register  */
#define M0AR                        (3U)    /* Memory 0 Address Register    */
#define M1AR                        (4U)    /* Memory 1 Address register    */
#define FCR                         (5U)    /* FIFO Control Register        */

#define FLAG0_INDEX                 (0U)
#define FLAG1_INDEX                 (6U)
#define FLAG2_INDEX                 (16U)
#define FLAG3_INDEX                 (22U)

#define FLAG_INDEX_REG_ACCESS_MASK  (0x03U)

#define IR_REG_ACCESS               (2U)    /* Interrupt Register Access */

#define ISR_REG_ACCESS              (2U)    /* Interrupt Status Register Access */

#define IFCR_REG_ACCESS             (2U)    /* Interrupt Flag Clear Register Access */
#define IFCR_BITS_ACCESS            (1U)

#define FLAG_CLEAR_MASK             (0x3DU)

/* DMA stream x configuration register(DMA_SxCR) Bits */
#define CR_CHSEL_POS                (25U) 
#define CR_CHSEL_MASK               (0x03U) 
#define CR_CHSEL                    (CR_CHSEL_MASK << CR_CHSEL_POS) /* Channel Selection */

#define CR_MBURST_POS               (23U) 
#define CR_MBURST_MASK              (0x03U) 
#define CR_MBURST                   (CR_MBURST_MASK << CR_MBURST_POS) /* Memory Burst Transfer Configuration */

#define CR_PBURST_POS               (21U) 
#define CR_PBURST_MASK              (0x03U) 
#define CR_PBURST                   (CR_PBURST_MASK << CR_PBURST_POS) /* Peripheral Burst Transfer Configuration */

#define CR_PL_POS                   (16U) 
#define CR_PL_MASK                  (0x03U) 
#define CR_PL                       (CR_PL_MASK << CR_PL_POS) /* Priority Level */

#define CR_MSIZE_POS                (13U) 
#define CR_MSIZE_MASK               (0x03U) 
#define CR_MSIZE                    (CR_MSIZE_MASK << CR_MSIZE_POS) /* Memory Data Size */

#define CR_PSIZE_POS                (11U) 
#define CR_PSIZE_MASK               (0x03U) 
#define CR_PSIZE                    (CR_PSIZE_MASK << CR_PSIZE_POS) /* Peripheral Data Size */

#define CR_MINC_POS                 (10U) 
#define CR_MINC_MASK                (0x01U) 
#define CR_MINC                     (CR_MINC_MASK << CR_MINC_POS) /* Memory Increment Mode */

#define CR_PINC_POS                 (9U) 
#define CR_PINC_MASK                (0x01U) 
#define CR_PINC                     (CR_PINC_MASK << CR_PINC_POS) /* Peripheral Increment Mode */

#define CR_CIRC_POS                 (8U) 
#define CR_CIRC_MASK                (0x01U) 
#define CR_CIRC                     (CR_CIRC_MASK << CR_CIRC_POS) /* Circular Mode */

#define CR_DIR_POS                  (6U) 
#define CR_DIR_MASK                 (0x03U) 
#define CR_DIR                      (CR_DIR_MASK << CR_DIR_POS) /* Data Transfer Direction */

#define CR_PFCTRL_POS               (5U) 
#define CR_PFCTRL_MASK              (0x01U) 
#define CR_PFCTRL                   (CR_PFCTRL_MASK << CR_PFCTRL_POS) /* Peripheral Flow Controller */

#define CR_TCIE_POS                 (4U) 
#define CR_TCIE_MASK                (0x01U) 
#define CR_TCIE                     (CR_TCIE_MASK << CR_TCIE_POS) /* Transfer Complete Interrupt Enable */

#define CR_HTIE_POS                 (3U) 
#define CR_HTIE_MASK                (0x01U) 
#define CR_HTIE                     (CR_HTIE_MASK << CR_HTIE_POS) /* Half Transfer Interrupt Enable */

#define CR_TEIE_POS                 (2U) 
#define CR_TEIE_MASK                (0x01U) 
#define CR_TEIE                     (CR_TEIE_MASK << CR_TEIE_POS) /* Transfer Error Interrupt Enable */

#define CR_DMEIE_POS                (1U) 
#define CR_DMEIE_MASK               (0x01U) 
#define CR_DMEIE                    (CR_DMEIE_MASK << CR_DMEIE_POS) /* Direct Mode Error Interrupt Enable */

#define CR_EN_POS                   (0U) 
#define CR_EN_MASK                  (0x00U) 
#define CR_EN                       (CR_EN_MASK << CR_EN_POS) /* Stream Enable */

/* DMA stream x FIFO control register (DMA_SxFCR) Bits */
#define FCR_FEIE_POS                (7U) 
#define FCR_FEIE_MASK               (0x01U) 
#define FCR_FEIE                    (FCR_FEIE_MASK << FCR_FEIE_POS) /* FIFO Error Interrupt Enable */

#define FCR_FS_POS                  (3U) 
#define FCR_FS_MASK                 (0x07U) 
#define FCR_FS                      (FCR_FS_MASK << FCR_FS_POS) /* FIFO Status */

#define FCR_DMDIS_POS               (2U) 
#define FCR_DMDIS_MASK              (0x01U) 
#define FCR_DMDIS                   (FCR_DMDIS_MASK << FCR_DMDIS_POS) /* Direct Mode Disable */

#define FCR_FTH_POS                 (0U) 
#define FCR_FTH_MASK                (0x03U) 
#define FCR_FTH                     (FCR_FTH_MASK << FCR_FTH_POS) /* FIFO Threshold Selection */

/* DMA low and high interrupt status register(DMA_LISR and DMA_HISR) base position */
#define ISR_TCIF_POS                (5U)
#define ISR_HTIF_POS                (4U)
#define ISR_TEIF_POS                (3U)
#define ISR_DMEIF_POS               (2U)
#define ISR_FEIF_POS                (0U)

/* DMA low and high interrupt flag clear register(DMA_LIFCR and DMA_HIFCR) base position */
#define IFCR_TCIF_POS               (5U)
#define IFCR_TCIF_MASK              (0x01U)
#define IFCR_TCIF                   (IFCR_TCIF_MASK << IFCR_TCIF_POS)

#define IFCR_HTIF_POS               (4U)
#define IFCR_HTIF_MASK              (0x01U)
#define IFCR_HTIF                   (IFCR_HTIF_MASK << IFCR_HTIF_POS)

#define IFCR_TEIF_POS               (3U)
#define IFCR_TEIF_MASK              (0x01U)
#define IFCR_TEIF                   (IFCR_TEIF_MASK << IFCR_TEIF_POS)

#define IFCR_DMEIF_POS              (2U)
#define IFCR_DMEIF_MASK             (0x01U)
#define IFCR_DMEIF                  (IFCR_DMEIF_MASK << IFCR_DMEIF_POS)

#define IFCR_FEIF_POS               (0U)
#define IFCR_FEIF_MASK              (0x01U)
#define IFCR_FEIF                   (IFCR_FEIF_MASK << IFCR_FEIF_POS)

/* Flags Get Macro */
#define EN_FLAG                     (GET_BIT(DMA[Copy_DMAConfig->DMANumber]->SxR[Copy_DMAConfig->StreamNumber][CR], CR_EN_POS))

/* Function Macro */
#define GET_STREAM_REG(REG)         (DMA[Copy_DMAConfig->DMANumber]->SxR[Copy_DMAConfig->StreamNumber][REG])

#define GET_INT_REG(REG)            (DMA[Copy_DMAConfig->DMANumber]->REG[Copy_DMAConfig->StreamNumber >> IR_REG_ACCESS])

#define GET_FLAG_STATUS(FLAG)       (GET_BIT(DMA[Copy_DMAConfig->DMANumber]->ISR[Copy_DMAConfig->StreamNumber >> IR_REG_ACCESS], (FlagsIndex[Copy_DMAConfig->StreamNumber >> IR_REG_ACCESS] << FLAG)))

#define TC_FLAG                     (GET_BIT(DMA[Copy_DMANum]->ISR[Copy_StrNum >> ISR_REG_ACCESS], (ISR_TCIF_POS  + FlagsIndex[Copy_StrNum & FLAG_INDEX_REG_ACCESS_MASK])))
#define HT_FLAG                     (GET_BIT(DMA[Copy_DMANum]->ISR[Copy_StrNum >> ISR_REG_ACCESS], (ISR_HTIF_POS  + FlagsIndex[Copy_StrNum & FLAG_INDEX_REG_ACCESS_MASK])))
#define TE_FLAG                     (GET_BIT(DMA[Copy_DMANum]->ISR[Copy_StrNum >> ISR_REG_ACCESS], (ISR_TEIF_POS  + FlagsIndex[Copy_StrNum & FLAG_INDEX_REG_ACCESS_MASK])))
#define DME_FLAG                    (GET_BIT(DMA[Copy_DMANum]->ISR[Copy_StrNum >> ISR_REG_ACCESS], (ISR_DMEIF_POS + FlagsIndex[Copy_StrNum & FLAG_INDEX_REG_ACCESS_MASK])))
#define FE_FLAG                     (GET_BIT(DMA[Copy_DMANum]->ISR[Copy_StrNum >> ISR_REG_ACCESS], (ISR_FEIF_POS  + FlagsIndex[Copy_StrNum & FLAG_INDEX_REG_ACCESS_MASK])))

#define HTIE_STATUS                 (GET_BIT(DMA[Copy_DMANum]->SxR[Copy_StrNum][CR], CR_HTIE_POS))

/* Private Functions Prototype */
static void IRQ_Handler(DMA_Number_t Copy_DMANum, DMA_StreamNumber_t Copy_StrNum);

static uint8_t IsDMAConfigValid(const DMA_Config_t *Copy_DMAConfig);

#endif /* DMA_PRV_H_ */
