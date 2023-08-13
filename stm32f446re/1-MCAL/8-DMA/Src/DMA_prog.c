/************************************************************************************
 * @file DMA_prog.c
 * @author Musa Mahmoud
 * @brief The DMA(Direct memory access controller) main source file, including functions' definition
 * @version 1.0
 * @date 2023-08-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdint.h>
#include "stm32f446xx.h"
#include "ErrType.h"
#include "BIT_MATH.h"

#include "DMA_interface.h"
#include "DMA_prv.h"

/* Private Variables */
static DMA_RegDef_t *DMA[DMA_PERIPHERAL_NUMBERS] = {DMA1, DMA2};

static DMA_Callback_t StreamsCallback[DMA_PERIPHERAL_NUMBERS][STREAM_NUMBERS][CALLBACK_NUMBERS] = {NULL};

static uint8_t FlagsIndex[] = {FLAG0_INDEX, FLAG1_INDEX, FLAG2_INDEX, FLAG3_INDEX};

/* Private Functions */
static void IRQ_Handler(DMA_Number_t Copy_DMANum, DMA_StreamNumber_t Copy_StrNum)
{
    /* Check for the transfer complete interrupt */
    if (FLAG_RAISED == TC_FLAG)
    {
        /* Clear the pending flag of TCIF */
        DMA[Copy_DMANum]->IFCR[Copy_StrNum >> IFCR_REG_ACCESS] = (IFCR_TCIF << FlagsIndex[Copy_StrNum & FLAG_INDEX_REG_ACCESS_MASK]);

        /* Call the callback function set by the user */
        if (NULL != StreamsCallback[Copy_DMANum][Copy_StrNum][DMA_TRANSFER_CMPLT_CALLBACK_ID])
        {
            StreamsCallback[Copy_DMANum][Copy_StrNum][DMA_TRANSFER_CMPLT_CALLBACK_ID]();
        }
    }

    /* Check for the half transfer interrupt */
    if (FLAG_RAISED == HT_FLAG && DMA_ENABLE == HTIE_STATUS)
    {
        /* Clear the pending flag of HTIF */
        DMA[Copy_DMANum]->IFCR[Copy_StrNum >> IFCR_REG_ACCESS] = (IFCR_HTIF << FlagsIndex[Copy_StrNum & FLAG_INDEX_REG_ACCESS_MASK]);

        /* Call the callback function set by the user */
        if (NULL != StreamsCallback[Copy_DMANum][Copy_StrNum][DMA_HALF_TRANSFER_CALLBACK_ID])
        {
            StreamsCallback[Copy_DMANum][Copy_StrNum][DMA_HALF_TRANSFER_CALLBACK_ID]();
        }
    }

    /* Check for the transfer error interrupt */
    if (FLAG_RAISED == TE_FLAG)
    {
        /* Clear the pending flag of TEIF */
        DMA[Copy_DMANum]->IFCR[Copy_StrNum >> IFCR_REG_ACCESS] = (IFCR_TEIF << FlagsIndex[Copy_StrNum & FLAG_INDEX_REG_ACCESS_MASK]);

        /* Call the callback function set by the user */
        if (NULL != StreamsCallback[Copy_DMANum][Copy_StrNum][DMA_TRANSFER_ERROR_CALLBACK_ID])
        {
            StreamsCallback[Copy_DMANum][Copy_StrNum][DMA_TRANSFER_ERROR_CALLBACK_ID]();
        }
    }

    /* Check for the direct mode error interrupt */
    if (FLAG_RAISED == DME_FLAG)
    {
        /* Clear the pending flag of DMEIF */
        DMA[Copy_DMANum]->IFCR[Copy_StrNum >> IFCR_REG_ACCESS] = (IFCR_DMEIF << FlagsIndex[Copy_StrNum & FLAG_INDEX_REG_ACCESS_MASK]);

        /* Call the callback function set by the user */
        if (NULL != StreamsCallback[Copy_DMANum][Copy_StrNum][DMA_DIRECT_MODE_ERROR_CALLBACK_ID])
        {
            StreamsCallback[Copy_DMANum][Copy_StrNum][DMA_DIRECT_MODE_ERROR_CALLBACK_ID]();
        }
    }

    /* Check for the FIFO error interrupt */
    if (FLAG_RAISED == FE_FLAG)
    {
        /* Clear the pending flag of FEIF */
        DMA[Copy_DMANum]->IFCR[Copy_StrNum >> IFCR_REG_ACCESS] = (IFCR_FEIF << FlagsIndex[Copy_StrNum & FLAG_INDEX_REG_ACCESS_MASK]);

        /* Call the callback function set by the user */
        if (NULL != StreamsCallback[Copy_DMANum][Copy_StrNum][DMA_FIFO_ERROR_CALLBACK_ID])
        {
            StreamsCallback[Copy_DMANum][Copy_StrNum][DMA_FIFO_ERROR_CALLBACK_ID]();
        }
    }
}

static uint8_t IsDMAConfigValid(const DMA_Config_t *Copy_DMAConfig)
{
    if ((Copy_DMAConfig->CallbackID < DMA_TRANSFER_CMPLT_CALLBACK_ID) || (Copy_DMAConfig->CallbackID > DMA_TRANSFER_ERROR_CALLBACK_ID)
        || (Copy_DMAConfig->ChannelNumber < DMA_CHANNEL_0) || (Copy_DMAConfig->ChannelNumber > DMA_CHANNEL_7)
        || (Copy_DMAConfig->Direction < DMA_PERIPHERAL_TO_MEMORY) || (Copy_DMAConfig->Direction > DMA_MEMORY_TO_MEMORY)
        || (Copy_DMAConfig->DMANumber < DMA_1) || (Copy_DMAConfig->DMANumber > DMA_2) || (Copy_DMAConfig->FIFOMode < DMA_DISABLE) || (Copy_DMAConfig->FIFOMode > DMA_ENABLE)
        || (Copy_DMAConfig->FIFOThreshold < DMA_ONE_QUARTER_FIFO) || (Copy_DMAConfig->FIFOThreshold > DMA_FULL_FIFO) 
        || (Copy_DMAConfig->MemBurst < DMA_SINGLE_TRANSFER) || (Copy_DMAConfig->MemBurst >DMA_INCREMENT_16)
        || (Copy_DMAConfig->MemInc < DMA_DISABLE) || (Copy_DMAConfig->MemInc > DMA_ENABLE) || (Copy_DMAConfig->MemSize < DMA_BYTE) || (Copy_DMAConfig->MemSize > DMA_WORD)
        || (Copy_DMAConfig->Mode < DMA_NORMAL) || (Copy_DMAConfig->Mode > DMA_PERIPHE_FLOW_CNTRL)
        || (Copy_DMAConfig->MemBurst < DMA_SINGLE_TRANSFER) || (Copy_DMAConfig->MemBurst >DMA_INCREMENT_16)
        || (Copy_DMAConfig->PeriphInc < DMA_DISABLE) || (Copy_DMAConfig->PeriphInc > DMA_ENABLE) || (Copy_DMAConfig->PeriphSize < DMA_BYTE) || (Copy_DMAConfig->PeriphSize > DMA_WORD)
        || (Copy_DMAConfig->Priority < DMA_LOW) || (Copy_DMAConfig->Priority > DMA_VERY_HIGH) 
        || (Copy_DMAConfig->StreamNumber < DMA_STREAM_0) ||(Copy_DMAConfig->StreamNumber > DMA_STREAM_7)
        )
    {
        return INVALID;
    }
    
    return VALID;
}

/* Public Functions */
uint8_t DMA_u8Init(const DMA_Config_t *Copy_DMAConfig)
{
    uint32_t Local_u32TmpReg = 0;

    /* Check DMA config, then early return if it's not valid */
    if (NULL == Copy_DMAConfig)
    {
        return NULL_PTR_ERR;
    }
    if (!IsDMAConfigValid(Copy_DMAConfig))
    {
        return NOK;
    }

    /* Disable the DMA */
    CLR_BIT(GET_STREAM_REG(CR), CR_EN_POS);

    /* Read the configuration register(CR) of the desired DMA and stream number */
    Local_u32TmpReg = READ_REG(GET_STREAM_REG(CR));

    /* Clear the following bits of CR register: CHSEL, MBURST, PBURST, PL, MSIZE, PSIZE, MINC, PINC, DIR and EN */
    CLR_BITS(Local_u32TmpReg, CR_CHSEL | CR_MBURST | CR_PBURST | CR_PL | CR_MSIZE | CR_PSIZE | CR_MINC | CR_PINC | CR_DIR);

    /* Set the following bits of CR with desired configuration: CHSEL, MBURST, PBURST, PL, MSIZE, PSIZE, MINC, PINC, DIR and EN */
    SET_BITS(Local_u32TmpReg, ((Copy_DMAConfig->ChannelNumber << CR_CHSEL_POS)   | (Copy_DMAConfig->MemBurst << CR_MBURST_POS) 
                                | (Copy_DMAConfig->PeriphBurst << CR_PBURST_POS) | (Copy_DMAConfig->Priority << CR_PL_POS)
                                | (Copy_DMAConfig->MemSize << CR_MSIZE_POS)      | (Copy_DMAConfig->PeriphSize << CR_PSIZE_POS)
                                | (Copy_DMAConfig->MemInc << CR_MINC_POS)        | (Copy_DMAConfig->PeriphInc << CR_PINC_POS)
                                | (Copy_DMAConfig->Direction << CR_DIR_POS)      | (Copy_DMAConfig->Mode)
    ));

    /* Write the configuration back to configuration register(CR) */
    WRITE_REG(GET_STREAM_REG(CR), Local_u32TmpReg);

    /* Read the FIFO control register(FCR) of the desired DMA and stream number */
    Local_u32TmpReg = READ_REG(GET_STREAM_REG(FCR));

    /* Clear the direct mode and FIFO threshold bits */
    CLR_BITS(Local_u32TmpReg, FCR_DMDIS | FCR_FTH);

    /* Set the direct mode(FIFO mode) configuration */
    SET_BITS(Local_u32TmpReg, (Copy_DMAConfig->FIFOMode << FCR_DMDIS_POS));

    /* Set the the FIFO threshold only if FIFO mode is enabled */
    if (DMA_ENABLE == Copy_DMAConfig->FIFOMode)
    {
        SET_BITS(Local_u32TmpReg, (Copy_DMAConfig->FIFOThreshold << FCR_FTH_POS));
    }

    /* Write the configuration back to FIFO control register(FCR) */
    WRITE_REG(GET_STREAM_REG(FCR), Local_u32TmpReg);

    /* Set the callback functions */
    StreamsCallback[Copy_DMAConfig->DMANumber][Copy_DMAConfig->StreamNumber][Copy_DMAConfig->CallbackID] = Copy_DMAConfig->CallbackFunction;
    
    return OK;
}

uint8_t DMA_u8Start(const DMA_Config_t *Copy_DMAConfig, uint32_t Copy_u32SrcAddress, uint32_t Copy_u32DstAddress, uint16_t Copy_u16DataLength)
{
    /* Check DMA config, then early return if it's not valid */
    if (NULL == Copy_DMAConfig)
    {
        return NULL_PTR_ERR;
    }
    if (!IsDMAConfigValid(Copy_DMAConfig))
    {
        return NOK;
    }
    /* Check the stream state, then return not ok if it's busy */
    if (DMA_ENABLE == EN_FLAG)
    {
        return NOK;
    }

    /* Write the length of data in the number of data register(SxNDTR) */
    WRITE_REG(GET_STREAM_REG(NDTR), (uint32_t) Copy_u16DataLength);

    if (DMA_MEMORY_TO_PERIPHERAL == Copy_DMAConfig->Direction)
    {
        /* Write the source address to the memory 0 address register */
        WRITE_REG(GET_STREAM_REG(M0AR), Copy_u32SrcAddress);

        /* Write the distention address to the peripheral address register */
        WRITE_REG(GET_STREAM_REG(PAR), Copy_u32DstAddress);
    }
    /* If it's peripheral to memory or memory to memory it's treaded as peripheral to memory */
    else
    {
        /* Write the source address to the peripheral address register */
        WRITE_REG(GET_STREAM_REG(PAR), Copy_u32SrcAddress);

        /* Write the destination address to the memory 0 address register */
        WRITE_REG(GET_STREAM_REG(M0AR), Copy_u32DstAddress);
    }

    /* Clearing the interrupt flags for the corresponding stream */
    GET_INT_REG(IFCR) = FLAG_CLEAR_MASK << FlagsIndex[Copy_DMAConfig->StreamNumber >> IFCR_BITS_ACCESS];

    /* Disable Interrupts: transfer complete, half transfer, transfer error and direct mode error */
    CLR_BITS(GET_STREAM_REG(CR), CR_TCIE | CR_HTIE | CR_TEIE | CR_DMEIE);
    
    /* Disable interrupt FIFO error, if FIFO mode is enabled */
    if (DMA_ENABLE == Copy_DMAConfig->FIFOMode)
    {
        CLR_BIT(GET_STREAM_REG(FCR), FCR_FEIE_POS);
    }

    /* Enable the DMA */
    SET_BIT(GET_STREAM_REG(CR), CR_EN_POS);
    
    return OK;
}

uint8_t DMA_u8PollForTransfer(const DMA_Config_t *Copy_DMAConfig, DMA_TransferCmpltLvl Copy_CompleteLevel, uint32_t Copy_u32Timeout)
{
    /* Check DMA config, then early return if it's not valid */
    if (NULL == Copy_DMAConfig)
    {
        return NULL_PTR_ERR;
    }
    if (!IsDMAConfigValid(Copy_DMAConfig) || 0 == Copy_u32Timeout)
    {
        return NOK;
    }

    if (DMA_TRANSFER_FULL_COMPLETE == Copy_CompleteLevel)
    {
        /* Busy wait until the transfer is completed or the timeout is finished */ 
        while(FLAG_NOT_RAISED == GET_FLAG_STATUS(ISR_TCIF_POS) && --Copy_u32Timeout);
    }
    else if (DMA_HALF_TRANSFER_COMPLETE == Copy_CompleteLevel)
    {
        /* Busy wait until the half transfer is completed or the timeout is finished */ 
        while(FLAG_NOT_RAISED == GET_FLAG_STATUS(ISR_HTIF_POS) && --Copy_u32Timeout);
    }
    
    /* Check the timeout, then return TIMEOUT if it's finished */
    if (OVER == Copy_u32Timeout)
    {
        return TIMEOUT;
    }

    return OK;
}

uint8_t DMA_u8Start_IT(const DMA_Config_t *Copy_DMAConfig, uint32_t Copy_u32SrcAddress, uint32_t Copy_u32DstAddress, uint16_t Copy_u16DataLength)
{
    /* Check DMA config, then early return if it's not valid */
    if (NULL == Copy_DMAConfig)
    {
        return NULL_PTR_ERR;
    }
    if (!IsDMAConfigValid(Copy_DMAConfig))
    {
        return NOK;
    }
    /* Check the stream state, then return not ok if it's busy */
    if (DMA_ENABLE == EN_FLAG)
    {
        return NOK;
    }

    /* Write the length of data in the number of data register(SxNDTR) */
    WRITE_REG(GET_STREAM_REG(NDTR), (uint32_t) Copy_u16DataLength);

    if (DMA_MEMORY_TO_PERIPHERAL == Copy_DMAConfig->Direction)
    {
        /* Write the source address to the memory 0 address register */
        WRITE_REG(GET_STREAM_REG(M0AR), Copy_u32SrcAddress);

        /* Write the distention address to the peripheral address register */
        WRITE_REG(GET_STREAM_REG(PAR), Copy_u32DstAddress);
    }
    /* If it's peripheral to memory or memory to memory it's treaded as peripheral to memory */
    else
    {
        /* Write the source address to the peripheral address register */
        WRITE_REG(GET_STREAM_REG(PAR), Copy_u32SrcAddress);

        /* Write the destination address to the memory 0 address register */
        WRITE_REG(GET_STREAM_REG(M0AR), Copy_u32DstAddress);
    }

    /* Clearing the interrupt flags for the corresponding stream */
    GET_INT_REG(IFCR) = FLAG_CLEAR_MASK << FlagsIndex[Copy_DMAConfig->StreamNumber >> IFCR_BITS_ACCESS];

    /* Enable Interrupts: transfer complete, transfer error and direct mode error */
    SET_BITS(GET_STREAM_REG(CR), CR_TCIE | CR_TEIE | CR_DMEIE);

    /* Enable interrupt half transfer, if half transfer callback is used */
    if (DMA_HALF_TRANSFER_CALLBACK_ID == Copy_DMAConfig->CallbackID)
    {
        SET_BIT(GET_STREAM_REG(CR), CR_HTIE_POS);
    }

    /* Enable interrupt FIFO error, if FIFO mode is enabled */
    if (DMA_ENABLE == Copy_DMAConfig->FIFOMode)
    {
        SET_BIT(GET_STREAM_REG(FCR), FCR_FEIE_POS);
    }

    /* Enable the DMA */
    SET_BIT(GET_STREAM_REG(CR), CR_EN_POS);
    
    return OK;
}

uint8_t DMA_u8GetError(DMA_Number_t Copy_DMANumber, DMA_StreamNumber_t Copy_StreamNumber, DMA_ErrorFlagID_t Copy_ErrorFlagID, DMA_Error_t *Copy_pError)
{
    /* Check function arguments, then early return if it's not valid */
    if ((Copy_DMANumber < DMA_1) || (Copy_DMANumber > DMA_2) || (Copy_StreamNumber < DMA_STREAM_0) || (Copy_StreamNumber > DMA_STREAM_7) ||
        (Copy_ErrorFlagID < DMA_TRANSFER_ERROR_ID) || (Copy_ErrorFlagID > DMA_FIFO_ERROR_ID) || (1 == Copy_ErrorFlagID))
    {
        return NOK;
    }
    
    /* Get the error occurrence state for the given error flag ID */
    *Copy_pError = GET_BIT(DMA[Copy_DMANumber]->ISR[Copy_StreamNumber >> ISR_REG_ACCESS], (Copy_ErrorFlagID << FlagsIndex[Copy_StreamNumber & FLAG_INDEX_REG_ACCESS_MASK]));
    
    return OK;
}

/* DMA IRQ Handlers */
void DMA1_Stream0_IRQHandler(void)
{
    IRQ_Handler(DMA_1, DMA_STREAM_0);
}

void DMA1_Stream1_IRQHandler(void)
{
    IRQ_Handler(DMA_1, DMA_STREAM_1);
}

void DMA1_Stream2_IRQHandler(void)
{
    IRQ_Handler(DMA_1, DMA_STREAM_2);
}

void DMA1_Stream3_IRQHandler(void)
{
    IRQ_Handler(DMA_1, DMA_STREAM_3);
}

void DMA1_Stream4_IRQHandler(void)
{
    IRQ_Handler(DMA_1, DMA_STREAM_4);
}

void DMA1_Stream5_IRQHandler(void)
{
    IRQ_Handler(DMA_1, DMA_STREAM_5);
}

void DMA1_Stream6_IRQHandler(void)
{
    IRQ_Handler(DMA_1, DMA_STREAM_6);
}

void DMA1_Stream7_IRQHandler(void)
{
    IRQ_Handler(DMA_1, DMA_STREAM_7);
}


void DMA2_Stream0_IRQHandler(void)
{
    IRQ_Handler(DMA_2, DMA_STREAM_0);
}

void DMA2_Stream1_IRQHandler(void)
{
    IRQ_Handler(DMA_2, DMA_STREAM_1);
}

void DMA2_Stream2_IRQHandler(void)
{
    IRQ_Handler(DMA_2, DMA_STREAM_2);
}

void DMA2_Stream3_IRQHandler(void)
{
    IRQ_Handler(DMA_2, DMA_STREAM_3);
}

void DMA2_Stream4_IRQHandler(void)
{
    IRQ_Handler(DMA_2, DMA_STREAM_4);
}

void DMA2_Stream5_IRQHandler(void)
{
    IRQ_Handler(DMA_2, DMA_STREAM_5);
}

void DMA2_Stream6_IRQHandler(void)
{
    IRQ_Handler(DMA_2, DMA_STREAM_6);
}

void DMA2_Stream7_IRQHandler(void)
{
    IRQ_Handler(DMA_2, DMA_STREAM_7);
}
