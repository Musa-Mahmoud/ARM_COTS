#ifndef DMA_INTERFACE_H_
#define DMA_INTERFACE_H_

#include <stdint.h>

typedef void (* DMA_Callback_t) (void);

typedef enum
{
    DMA_1 = 0,
    DMA_2
} DMA_Number_t;

typedef enum
{
    DMA_STREAM_0 = 0,
    DMA_STREAM_1,
    DMA_STREAM_2,
    DMA_STREAM_3,
    DMA_STREAM_4,
    DMA_STREAM_5,
    DMA_STREAM_6,
    DMA_STREAM_7
} DMA_StreamNumber_t;

typedef enum
{
    DMA_CHANNEL_0 = 0,
    DMA_CHANNEL_1,
    DMA_CHANNEL_2,
    DMA_CHANNEL_3,
    DMA_CHANNEL_4,
    DMA_CHANNEL_5,
    DMA_CHANNEL_6,
    DMA_CHANNEL_7
} DMA_ChannelNumber_t;

typedef enum
{
    DMA_SINGLE_TRANSFER = 0,
    DMA_INCREMENT_4,
    DMA_INCREMENT_8,
    DMA_INCREMENT_16
} DMA_BurstTransfer_t;

typedef enum
{
    DMA_LOW = 0,
    DMA_MEDIUM,
    DMA_HIGH,
    DMA_VERY_HIGH
} DMA_Priority_t;

typedef enum
{
    DMA_BYTE = 0,           /* 8-bit  */
    DMA_HALF_WORD,          /* 16-bit */
    DMA_WORD                /* 32-bit */
} DMA_DataSize_t;

typedef enum
{
    DMA_DISABLE = 0,
    DMA_ENABLE
} DMA_ConfigEnable_t;

typedef enum
{
    DMA_NORMAL              = 0,
    DMA_CIRCULAR            = (0x100U),
    DMA_PERIPHE_FLOW_CNTRL  = (0x20U)
} DMA_Mode_t;

typedef enum
{
    DMA_PERIPHERAL_TO_MEMORY = 0,
    DMA_MEMORY_TO_PERIPHERAL,
    DMA_MEMORY_TO_MEMORY
} DMA_DataDirection_t;

typedef enum
{
    DMA_ONE_QUARTER_FIFO = 0,
    DMA_HALF_FIFO,
    DMA_THREE_QUARTER_FIFO,
    DMA_FULL_FIFO
} DMA_FIFOThreshold;

typedef enum
{
    DMA_TRANSFER_CMPLT_CALLBACK_ID = 0,
    DMA_HALF_TRANSFER_CALLBACK_ID,
    DMA_TRANSFER_ERROR_CALLBACK_ID,
    DMA_DIRECT_MODE_ERROR_CALLBACK_ID,
    DMA_FIFO_ERROR_CALLBACK_ID,
} DMA_CallbackID_t;

typedef enum
{
    DMA_TRANSFER_ERROR = 0,
    DMA_DIRECT_MODE_ERROR,
    DMA_FIFO_ERROR
} DMA_Error_t;

typedef enum
{
    DMA_FIFO_ERROR_ID,
    DMA_DIRECT_MODE_ERROR_ID = 2,
    DMA_TRANSFER_ERROR_ID
} DMA_ErrorFlagID_t;

typedef enum
{
    DMA_HALF_TRANSFER_COMPLETE = 0,
    DMA_TRANSFER_FULL_COMPLETE
} DMA_TransferCmpltLvl;

typedef struct 
{
    DMA_Number_t DMANumber;
    DMA_StreamNumber_t StreamNumber;
    DMA_ChannelNumber_t ChannelNumber;
    DMA_BurstTransfer_t MemBurst;
    DMA_BurstTransfer_t PeriphBurst;
    DMA_Priority_t Priority;
    DMA_DataSize_t MemSize;
    DMA_DataSize_t PeriphSize;
    DMA_ConfigEnable_t MemInc;
    DMA_ConfigEnable_t PeriphInc;
    DMA_Mode_t Mode;
    DMA_DataDirection_t Direction;
    DMA_ConfigEnable_t FIFOMode;
    DMA_FIFOThreshold FIFOThreshold;
    DMA_CallbackID_t CallbackID;
    DMA_Callback_t CallbackFunction;
} DMA_Config_t;

uint8_t DMA_u8Init(const DMA_Config_t *Copy_DMAConfig);

uint8_t DMA_u8Start(const DMA_Config_t *Copy_DMAConfig, uint32_t Copy_u32SrcAddress, uint32_t Copy_u32DstAddress, uint16_t Copy_u16DataLength);

uint8_t DMA_u8PollForTransfer(const DMA_Config_t *Copy_DMAConfig, DMA_TransferCmpltLvl Copy_CompleteLevel, uint32_t Copy_u32Timeout);

uint8_t DMA_u8Start_IT(const DMA_Config_t *Copy_DMAConfig, uint32_t Copy_u32SrcAddress, uint32_t Copy_u32DstAddress, uint16_t Copy_u16DataLength);

uint8_t DMA_u8GetError(DMA_Number_t Copy_DMANumber, DMA_StreamNumber_t Copy_StreamNumber, DMA_ErrorFlagID_t Copy_ErrorFlagID, DMA_Error_t *Copy_pError);

#endif /* DMA_INTERFACE_H_ */
