#ifndef __POWER_MGR_HEADER_
#define __POWER_MGR_HEADER_

#include <mach/am_regs.h>
#include <mach/clock.h>
#include <linux/spinlock.h>
/* clock gate control */

#define __CLK_GATE_ON(_MOD) \
	do{                     \
		if(GCLK_ref[GCLK_IDX_##_MOD]++ == 0){ \
			if (0) printk(KERN_INFO "gate on %s %x, %x\n", GCLK_NAME_##_MOD, GCLK_REG_##_MOD, GCLK_MASK_##_MOD); \
			SET_CBUS_REG_MASK(GCLK_REG_##_MOD, GCLK_MASK_##_MOD); \
		} \
	}while(0)


#define __CLK_GATE_OFF(_MOD) \
	do{                             \
		if(GCLK_ref[GCLK_IDX_##_MOD] <= 0){ \
			if (0) printk(KERN_INFO "gate off %s %x, %x\n", GCLK_NAME_##_MOD, GCLK_REG_##_MOD, GCLK_MASK_##_MOD); \
			CLEAR_CBUS_REG_MASK(GCLK_REG_##_MOD, GCLK_MASK_##_MOD); \
			GCLK_ref[GCLK_IDX_##_MOD] = 0; \
		} \
	}while(0)

#define IS_CLK_GATE_ON(_MOD) (READ_CBUS_REG(GCLK_REG_##_MOD) & (GCLK_MASK_##_MOD))
#define GATE_INIT(_MOD) GCLK_ref[GCLK_IDX_##_MOD] = IS_CLK_GATE_ON(_MOD)?1:0
	
extern spinlock_t gate_lock;

#define CLK_GATE_ON(_MOD) \
	do{                     \
		unsigned long flags; \
		spin_lock_irqsave(&gate_lock, flags); \
		__CLK_GATE_ON(_MOD); \
		spin_unlock_irqrestore(&gate_lock, flags); \
	}while(0)
	
#define CLK_GATE_OFF(_MOD) \
	do{                     \
		unsigned long flags; \
		spin_lock_irqsave(&gate_lock, flags); \
		__CLK_GATE_OFF(_MOD); \
		spin_unlock_irqrestore(&gate_lock, flags); \
	}while(0)

#define GCLK_IDX_DDR         0
#define GCLK_NAME_DDR      "DDR"
#define GCLK_DEV_DDR      "CLKGATE_DDR"
#define GCLK_REG_DDR      (HHI_GCLK_MPEG0)
#define GCLK_MASK_DDR      (1<<0)

#define GCLK_IDX_DOS         1
#define GCLK_NAME_DOS      "DOS"
#define GCLK_DEV_DOS      "CLKGATE_DOS"
#define GCLK_REG_DOS      (HHI_GCLK_MPEG0)
#define GCLK_MASK_DOS      (1<<1)

#define GCLK_IDX_RESERVED0_0         2
#define GCLK_NAME_RESERVED0_0      "RESERVED0_0"
#define GCLK_DEV_RESERVED0_0      "CLKGATE_RESERVED0_0"
#define GCLK_REG_RESERVED0_0      (HHI_GCLK_MPEG0)
#define GCLK_MASK_RESERVED0_0      (1<<2)

#define GCLK_IDX_RESERVED0_1         3
#define GCLK_NAME_RESERVED0_1      "RESERVED0_1"
#define GCLK_DEV_RESERVED0_1      "CLKGATE_RESERVED0_1"
#define GCLK_REG_RESERVED0_1      (HHI_GCLK_MPEG0)
#define GCLK_MASK_RESERVED0_1      (1<<3)

#define GCLK_IDX_AHB_BRIDGE         4
#define GCLK_NAME_AHB_BRIDGE      "AHB_BRIDGE"
#define GCLK_DEV_AHB_BRIDGE      "CLKGATE_AHB_BRIDGE"
#define GCLK_REG_AHB_BRIDGE      (HHI_GCLK_MPEG0)
#define GCLK_MASK_AHB_BRIDGE      (1<<4)

#define GCLK_IDX_ISA         5
#define GCLK_NAME_ISA      "ISA"
#define GCLK_DEV_ISA      "CLKGATE_ISA"
#define GCLK_REG_ISA      (HHI_GCLK_MPEG0)
#define GCLK_MASK_ISA      (1<<5)

//NEW ADD
#define GCLK_IDX_PL310_CBUS         6
#define GCLK_NAME_PL310_CBUS      "PL310_CBUS"
#define GCLK_DEV_PL310_CBUS      "CLKGATE_PL310_CBUS"
#define GCLK_REG_PL310_CBUS      (HHI_GCLK_MPEG0)
#define GCLK_MASK_PL310_CBUS      (1<<6)

#define GCLK_IDX_PERIPHS_TOP     7
#define GCLK_NAME_PERIPHS_TOP      "PERIPHS_TOP"
#define GCLK_DEV_PERIPHS_TOP      "CLKGATE_PERIPHS_TOP"
#define GCLK_REG_PERIPHS_TOP      (HHI_GCLK_MPEG0)
#define GCLK_MASK_PERIPHS_TOP      (1<<7)

#define GCLK_IDX_SPICC         8
#define GCLK_NAME_SPICC      "SPICC"
#define GCLK_DEV_SPICC      "CLKGATE_SPICC"
#define GCLK_REG_SPICC      (HHI_GCLK_MPEG0)
#define GCLK_MASK_SPICC      (1<<8)

#define GCLK_IDX_I2C         9
#define GCLK_NAME_I2C      "I2C"
#define GCLK_DEV_I2C      "CLKGATE_I2C"
#define GCLK_REG_I2C      (HHI_GCLK_MPEG0)
#define GCLK_MASK_I2C      (1<<9)

#define GCLK_IDX_SAR_ADC         10
#define GCLK_NAME_SAR_ADC      "SAR_ADC"
#define GCLK_DEV_SAR_ADC      "CLKGATE_SAR_ADC"
#define GCLK_REG_SAR_ADC      (HHI_GCLK_MPEG0)
#define GCLK_MASK_SAR_ADC      (1<<10)

#define GCLK_IDX_SMART_CARD_MPEG_DOMAIN         11
#define GCLK_NAME_SMART_CARD_MPEG_DOMAIN      "SMART_CARD_MPEG_DOMAIN"
#define GCLK_DEV_SMART_CARD_MPEG_DOMAIN      "CLKGATE_SMART_CARD_MPEG_DOMAIN"
#define GCLK_REG_SMART_CARD_MPEG_DOMAIN      (HHI_GCLK_MPEG0)
#define GCLK_MASK_SMART_CARD_MPEG_DOMAIN      (1<<11)

#define GCLK_IDX_RANDOM_NUM_GEN         12
#define GCLK_NAME_RANDOM_NUM_GEN      "RANDOM_NUM_GEN"
#define GCLK_DEV_RANDOM_NUM_GEN      "CLKGATE_RANDOM_NUM_GEN"
#define GCLK_REG_RANDOM_NUM_GEN      (HHI_GCLK_MPEG0)
#define GCLK_MASK_RANDOM_NUM_GEN      (1<<12)

#define GCLK_IDX_UART0         13
#define GCLK_NAME_UART0      "UART0"
#define GCLK_DEV_UART0      "CLKGATE_UART0"
#define GCLK_REG_UART0      (HHI_GCLK_MPEG0)
#define GCLK_MASK_UART0      (1<<13)

#define GCLK_IDX_SDHC         14
#define GCLK_NAME_SDHC      "SDHC"
#define GCLK_DEV_SDHC      "CLKGATE_SDHC"
#define GCLK_REG_SDHC      (HHI_GCLK_MPEG0)
#define GCLK_MASK_SDHC      (1<<14)

#define GCLK_IDX_STREAM         15
#define GCLK_NAME_STREAM      "STREAM"
#define GCLK_DEV_STREAM      "CLKGATE_STREAM"
#define GCLK_REG_STREAM      (HHI_GCLK_MPEG0)
#define GCLK_MASK_STREAM      (1<<15)

#define GCLK_IDX_ASYNC_FIFO         16
#define GCLK_NAME_ASYNC_FIFO      "ASYNC_FIFO"
#define GCLK_DEV_ASYNC_FIFO      "CLKGATE_ASYNC_FIFO"
#define GCLK_REG_ASYNC_FIFO      (HHI_GCLK_MPEG0)
#define GCLK_MASK_ASYNC_FIFO      (1<<16)

#define GCLK_IDX_SDIO         17
#define GCLK_NAME_SDIO      "SDIO"
#define GCLK_DEV_SDIO      "CLKGATE_SDIO"
#define GCLK_REG_SDIO      (HHI_GCLK_MPEG0)
#define GCLK_MASK_SDIO      (1<<17)

#define GCLK_IDX_AUD_BUF         18
#define GCLK_NAME_AUD_BUF      "AUD_BUF"
#define GCLK_DEV_AUD_BUF      "CLKGATE_AUD_BUF"
#define GCLK_REG_AUD_BUF      (HHI_GCLK_MPEG0)
#define GCLK_MASK_AUD_BUF      (1<<18)

#define GCLK_IDX_HIU_PARSER         19
#define GCLK_NAME_HIU_PARSER      "HIU_PARSER"
#define GCLK_DEV_HIU_PARSER      "CLKGATE_HIU_PARSER"
#define GCLK_REG_HIU_PARSER      (HHI_GCLK_MPEG0)
#define GCLK_MASK_HIU_PARSER      (1<<19)

#define GCLK_IDX_RESERVED0_2         20
#define GCLK_NAME_RESERVED0_2      "RESERVED0_2"
#define GCLK_DEV_RESERVED0_2      "CLKGATE_RESERVED0_2"
#define GCLK_REG_RESERVED0_2      (HHI_GCLK_MPEG0)
#define GCLK_MASK_RESERVED0_2      (1<<20)

//NEW ADD
#define GCLK_IDX_RESERVED0_3         21
#define GCLK_NAME_RESERVED0_3      "RESERVED0_3 "
#define GCLK_DEV_RESERVED0_3      "CLKGATE_RESERVED0_3 "
#define GCLK_REG_RESERVED0_3      (HHI_GCLK_MPEG0)
#define GCLK_MASK_RESERVED0_3      (1<<21)

#define GCLK_IDX_RESERVED0_4         22
#define GCLK_NAME_RESERVED0_4      "RESERVED0_4"
#define GCLK_DEV_RESERVED0_4      "CLKGATE_RESERVED0_4"
#define GCLK_REG_RESERVED0_4      (HHI_GCLK_MPEG0)
#define GCLK_MASK_RESERVED0_4      (1<<22)

#define GCLK_IDX_ASSIST_MISC         23
#define GCLK_NAME_ASSIST_MISC      "ASSIST_MISC"
#define GCLK_DEV_ASSIST_MISC      "CLKGATE_ASSIST_MISC"
#define GCLK_REG_ASSIST_MISC      (HHI_GCLK_MPEG0)
#define GCLK_MASK_ASSIST_MISC      (1<<23)


#define GCLK_IDX_RESERVED0_5         24
#define GCLK_NAME_RESERVED0_5      "RESERVED0_5"
#define GCLK_DEV_RESERVED0_5     "CLKGATE_RESERVED0_5"
#define GCLK_REG_RESERVED0_5      (HHI_GCLK_MPEG0)
#define GCLK_MASK_RESERVED0_5      (1<<24)

#define GCLK_IDX_RESERVED0_6         25
#define GCLK_NAME_RESERVED0_6      "RESERVED0_6"
#define GCLK_DEV_RESERVED0_6      "CLKGATE_RESERVED0_6"
#define GCLK_REG_RESERVED0_6      (HHI_GCLK_MPEG0)
#define GCLK_MASK_RESERVED0_6      (1<<25)

#define GCLK_IDX_RESERVED0_7         26
#define GCLK_NAME_RESERVED0_7      "RESERVED0_7"
#define GCLK_DEV_RESERVED0_7      "CLKGATE_RESERVED0_7"
#define GCLK_REG_RESERVED0_7      (HHI_GCLK_MPEG0)
#define GCLK_MASK_RESERVED0_7      (1<<26)

#define GCLK_IDX_RESERVED0_8         27
#define GCLK_NAME_RESERVED0_8      "RESERVED0_8"
#define GCLK_DEV_RESERVED0_8      "CLKGATE_RESERVED0_8"
#define GCLK_REG_RESERVED0_8      (HHI_GCLK_MPEG0)
#define GCLK_MASK_RESERVED0_8      (1<<27)

#define GCLK_IDX_RESERVED0_9         28
#define GCLK_NAME_RESERVED0_9      "RESERVED0_9"
#define GCLK_DEV_RESERVED0_9      "CLKGATE_RESERVED0_9"
#define GCLK_REG_RESERVED0_9      (HHI_GCLK_MPEG0)
#define GCLK_MASK_RESERVED0_9      (1<<28)

#define GCLK_IDX_RESERVED0_A         29
#define GCLK_NAME_RESERVED0_A      "RESERVED0_A"
#define GCLK_DEV_RESERVED0_A      "CLKGATE_RESERVED0_A"
#define GCLK_REG_RESERVED0_A      (HHI_GCLK_MPEG0)
#define GCLK_MASK_RESERVED0_A      (1<<29)

#define GCLK_IDX_SPI         30
#define GCLK_NAME_SPI      "SPI"
#define GCLK_DEV_SPI      "CLKGATE_SPI"
#define GCLK_REG_SPI      (HHI_GCLK_MPEG0)
#define GCLK_MASK_SPI      (1<<30)

#define GCLK_IDX_RESERVED0_B         31
#define GCLK_NAME_RESERVED0_B      "RESERVED0_B"
#define GCLK_DEV_RESERVED0_B      "CLKGATE_RESERVED0_B"
#define GCLK_REG_RESERVED0_B      (HHI_GCLK_MPEG0)
#define GCLK_MASK_RESERVED0_B      (1<<31)

/**************************************************************/

#define GCLK_IDX_RESERVED1_1         32
#define GCLK_NAME_RESERVED1_1      "RESERVED1_1"
#define GCLK_DEV_RESERVED1_1      "CLKGATE_RESERVED1_1"
#define GCLK_REG_RESERVED1_1      (HHI_GCLK_MPEG1)
#define GCLK_MASK_RESERVED1_1      (1<<0)


#define GCLK_IDX_RESERVED1_2         33
#define GCLK_NAME_RESERVED1_2      "RESERVED1_2"
#define GCLK_DEV_RESERVED1_2      "CLKGATE_RESERVED1_2"
#define GCLK_REG_RESERVED1_2      (HHI_GCLK_MPEG1)
#define GCLK_MASK_RESERVED1_2      (1<<1)


#define GCLK_IDX_AUD_IN         34
#define GCLK_NAME_AUD_IN      "AUD_IN"
#define GCLK_DEV_AUD_IN      "CLKGATE_AUD_IN"
#define GCLK_REG_AUD_IN      (HHI_GCLK_MPEG1)
#define GCLK_MASK_AUD_IN      (1<<2)

#define GCLK_IDX_ETHERNET         35
#define GCLK_NAME_ETHERNET      "ETHERNET"
#define GCLK_DEV_ETHERNET      "CLKGATE_ETHERNET"
#define GCLK_REG_ETHERNET      (HHI_GCLK_MPEG1)
#define GCLK_MASK_ETHERNET      (1<<3)

#define GCLK_IDX_DEMUX         36
#define GCLK_NAME_DEMUX      "DEMUX"
#define GCLK_DEV_DEMUX      "CLKGATE_DEMUX"
#define GCLK_REG_DEMUX      (HHI_GCLK_MPEG1)
#define GCLK_MASK_DEMUX      (1<<4)

#define GCLK_IDX_RESERVED1_3         37
#define GCLK_NAME_RESERVED1_3      "RESERVED1_3"
#define GCLK_DEV_RESERVED1_3      "CLKGATE_RESERVED1_3"
#define GCLK_REG_RESERVED1_3      (HHI_GCLK_MPEG1)
#define GCLK_MASK_RESERVED1_3      (1<<5)

#define GCLK_IDX_AIU_AI_TOP_GLUE         38
#define GCLK_NAME_AIU_AI_TOP_GLUE      "AIU_AI_TOP_GLUE"
#define GCLK_DEV_AIU_AI_TOP_GLUE      "CLKGATE_AIU_AI_TOP_GLUE"
#define GCLK_REG_AIU_AI_TOP_GLUE      (HHI_GCLK_MPEG1)
#define GCLK_MASK_AIU_AI_TOP_GLUE      (1<<6)

#define GCLK_IDX_AIU_IEC958         39
#define GCLK_NAME_AIU_IEC958      "AIU_IEC958"
#define GCLK_DEV_AIU_IEC958      "CLKGATE_AIU_IEC958"
#define GCLK_REG_AIU_IEC958      (HHI_GCLK_MPEG1)
#define GCLK_MASK_AIU_IEC958      (1<<7)

#define GCLK_IDX_AIU_I2S_OUT         40
#define GCLK_NAME_AIU_I2S_OUT      "AIU_I2S_OUT"
#define GCLK_DEV_AIU_I2S_OUT      "CLKGATE_AIU_I2S_OUT"
#define GCLK_REG_AIU_I2S_OUT      (HHI_GCLK_MPEG1)
#define GCLK_MASK_AIU_I2S_OUT      (1<<8)

#define GCLK_IDX_AIU_AMCLK_MEASURE         41
#define GCLK_NAME_AIU_AMCLK_MEASURE      "AIU_AMCLK_MEASURE"
#define GCLK_DEV_AIU_AMCLK_MEASURE      "CLKGATE_AIU_AMCLK_MEASURE"
#define GCLK_REG_AIU_AMCLK_MEASURE      (HHI_GCLK_MPEG1)
#define GCLK_MASK_AIU_AMCLK_MEASURE      (1<<9)

#define GCLK_IDX_AIU_AIFIFO2         42
#define GCLK_NAME_AIU_AIFIFO2      "AIU_AIFIFO2"
#define GCLK_DEV_AIU_AIFIFO2      "CLKGATE_AIU_AIFIFO2"
#define GCLK_REG_AIU_AIFIFO2      (HHI_GCLK_MPEG1)
#define GCLK_MASK_AIU_AIFIFO2      (1<<10)

#define GCLK_IDX_AIU_AUD_MIXER         43
#define GCLK_NAME_AIU_AUD_MIXER      "AIU_AUD_MIXER"
#define GCLK_DEV_AIU_AUD_MIXER      "CLKGATE_AIU_AUD_MIXER"
#define GCLK_REG_AIU_AUD_MIXER      (HHI_GCLK_MPEG1)
#define GCLK_MASK_AIU_AUD_MIXER      (1<<11)

#define GCLK_IDX_AIU_MIXER_REG         44
#define GCLK_NAME_AIU_MIXER_REG      "AIU_MIXER_REG"
#define GCLK_DEV_AIU_MIXER_REG      "CLKGATE_AIU_MIXER_REG"
#define GCLK_REG_AIU_MIXER_REG      (HHI_GCLK_MPEG1)
#define GCLK_MASK_AIU_MIXER_REG      (1<<12)

#define GCLK_IDX_AIU_ADC         45
#define GCLK_NAME_AIU_ADC      "AIU_ADC"
#define GCLK_DEV_AIU_ADC      "CLKGATE_AIU_ADC"
#define GCLK_REG_AIU_ADC      (HHI_GCLK_MPEG1)
#define GCLK_MASK_AIU_ADC      (1<<13)

#define GCLK_IDX_BLK_MOV         46
#define GCLK_NAME_BLK_MOV      "BLK_MOV"
#define GCLK_DEV_BLK_MOV      "CLKGATE_BLK_MOV"
#define GCLK_REG_BLK_MOV      (HHI_GCLK_MPEG1)
#define GCLK_MASK_BLK_MOV      (1<<14)

//NEW ADD
#define GCLK_IDX_AIU_TOP_LEVEL         47
#define GCLK_NAME_AIU_TOP_LEVEL      "AIU_TOP_LEVEL"
#define GCLK_DEV_AIU_TOP_LEVEL      "CLKGATE_AIU_TOP_LEVEL"
#define GCLK_REG_AIU_TOP_LEVEL      (HHI_GCLK_MPEG1)
#define GCLK_MASK_AIU_TOP_LEVEL      (1<<15)

#define GCLK_IDX_UART1         48
#define GCLK_NAME_UART1      "UART1"
#define GCLK_DEV_UART1      "CLKGATE_UART1"
#define GCLK_REG_UART1      (HHI_GCLK_MPEG1)
#define GCLK_MASK_UART1      (1<<16)

#define GCLK_IDX_RESERVED1_4         49
#define GCLK_NAME_RESERVED1_4      "RESERVED1_4"
#define GCLK_DEV_RESERVED1_4      "CLKGATE_RESERVED1_4"
#define GCLK_REG_RESERVED1_4      (HHI_GCLK_MPEG1)
#define GCLK_MASK_RESERVED1_4      (1<<17)

//NEW ADD 
#define GCLK_IDX_RESERVED1_5         50
#define GCLK_NAME_RESERVED1_5      "RESERVED1_5"
#define GCLK_DEV_RESERVED1_5      "CLKGATE_RESERVED1_5"
#define GCLK_REG_RESERVED1_5      (HHI_GCLK_MPEG1)
#define GCLK_MASK_RESERVED1_5      (1<<18)

#define GCLK_IDX_RESERVED1_6         51
#define GCLK_NAME_RESERVED1_6      "RESERVED1_6"
#define GCLK_DEV_RESERVED1_6      "CLKGATE_RESERVED1_6"
#define GCLK_REG_RESERVED1_6      (HHI_GCLK_MPEG1)
#define GCLK_MASK_RESERVED1_6      (1<<19)

#define GCLK_IDX_GE2D         52
#define GCLK_NAME_GE2D      "GE2D"
#define GCLK_DEV_GE2D      "CLKGATE_GE2D"
#define GCLK_REG_GE2D      (HHI_GCLK_MPEG1)
#define GCLK_MASK_GE2D      (1<<20)

#define GCLK_IDX_USB0         53
#define GCLK_NAME_USB0      "USB0"
#define GCLK_DEV_USB0      "CLKGATE_USB0"
#define GCLK_REG_USB0      (HHI_GCLK_MPEG1)
#define GCLK_MASK_USB0      (1<<21)

#define GCLK_IDX_USB1         54
#define GCLK_NAME_USB1      "USB1"
#define GCLK_DEV_USB1      "CLKGATE_USB1"
#define GCLK_REG_USB1      (HHI_GCLK_MPEG1)
#define GCLK_MASK_USB1      (1<<22)

#define GCLK_IDX_RESET         55
#define GCLK_NAME_RESET      "RESET"
#define GCLK_DEV_RESET      "CLKGATE_RESET"
#define GCLK_REG_RESET      (HHI_GCLK_MPEG1)
#define GCLK_MASK_RESET      (1<<23)

#define GCLK_IDX_NAND         56
#define GCLK_NAME_NAND      "NAND"
#define GCLK_DEV_NAND      "CLKGATE_NAND"
#define GCLK_REG_NAND      (HHI_GCLK_MPEG1)
#define GCLK_MASK_NAND      (1<<24)

#define GCLK_IDX_HIU_PARSER_TOP         57
#define GCLK_NAME_HIU_PARSER_TOP      "HIU_PARSER_TOP"
#define GCLK_DEV_HIU_PARSER_TOP      "CLKGATE_HIU_PARSER_TOP"
#define GCLK_REG_HIU_PARSER_TOP      (HHI_GCLK_MPEG1)
#define GCLK_MASK_HIU_PARSER_TOP      (1<<25)

//NEW ADD 
#define GCLK_IDX_USB_GENERAL         58
#define GCLK_NAME_USB_GENERAL      "USB_GENERAL"
#define GCLK_DEV_USB_GENERAL      "CLKGATE_USB_GENERAL"
#define GCLK_REG_USB_GENERAL      (HHI_GCLK_MPEG1)
#define GCLK_MASK_USB_GENERAL      (1<<26)

#define GCLK_IDX_RESERVED1_7         59
#define GCLK_NAME_RESERVED1_7      "RESERVED1_7"
#define GCLK_DEV_RESERVED1_7      "CLKGATE_RESERVED1_7"
#define GCLK_REG_RESERVED1_7      (HHI_GCLK_MPEG1)
#define GCLK_MASK_RESERVED1_7      (1<<27)

#define GCLK_IDX_VDIN1         60
#define GCLK_NAME_VDIN1      "VDIN1"
#define GCLK_DEV_VDIN1      "CLKGATE_VDIN1"
#define GCLK_REG_VDIN1      (HHI_GCLK_MPEG1)
#define GCLK_MASK_VDIN1      (1<<28)

#define GCLK_IDX_AHB_ARB0         61
#define GCLK_NAME_AHB_ARB0      "AHB_ARB0"
#define GCLK_DEV_AHB_ARB0      "CLKGATE_AHB_ARB0"
#define GCLK_REG_AHB_ARB0      (HHI_GCLK_MPEG1)
#define GCLK_MASK_AHB_ARB0      (1<<29)

#define GCLK_IDX_EFUSE         62
#define GCLK_NAME_EFUSE      "EFUSE"
#define GCLK_DEV_EFUSE      "CLKGATE_EFUSE"
#define GCLK_REG_EFUSE      (HHI_GCLK_MPEG1)
#define GCLK_MASK_EFUSE      (1<<30)

#define GCLK_IDX_ROM_CLK         63
#define GCLK_NAME_ROM_CLK      "ROM_CLK"
#define GCLK_DEV_ROM_CLK      "CLKGATE_ROM_CLK"
#define GCLK_REG_ROM_CLK      (HHI_GCLK_MPEG1)
#define GCLK_MASK_ROM_CLK      (1<<31)

/**************************************************************/

#define GCLK_IDX_RESERVED2_0         64
#define GCLK_NAME_RESERVED2_0      "RESERVED2_0"
#define GCLK_DEV_RESERVED2_0      "CLKGATE_RESERVED2_0"
#define GCLK_REG_RESERVED2_0      (HHI_GCLK_MPEG2)
#define GCLK_MASK_RESERVED2_0      (1<<0)

#define GCLK_IDX_AHB_DATA_BUS         65
#define GCLK_NAME_AHB_DATA_BUS      "AHB_DATA_BUS"
#define GCLK_DEV_AHB_DATA_BUS      "CLKGATE_AHB_DATA_BUS"
#define GCLK_REG_AHB_DATA_BUS      (HHI_GCLK_MPEG2)
#define GCLK_MASK_AHB_DATA_BUS      (1<<1)

#define GCLK_IDX_AHB_CONTROL_BUS         66
#define GCLK_NAME_AHB_CONTROL_BUS      "AHB_CONTROL_BUS"
#define GCLK_DEV_AHB_CONTROL_BUS      "CLKGATE_AHB_CONTROL_BUS"
#define GCLK_REG_AHB_CONTROL_BUS      (HHI_GCLK_MPEG2)
#define GCLK_MASK_AHB_CONTROL_BUS      (1<<2)

#define GCLK_IDX_HDMI_INTR_SYNC         67
#define GCLK_NAME_HDMI_INTR_SYNC      "HDMI_INTR_SYNC"
#define GCLK_DEV_HDMI_INTR_SYNC      "CLKGATE_HDMI_INTR_SYNC"
#define GCLK_REG_HDMI_INTR_SYNC      (HHI_GCLK_MPEG2)
#define GCLK_MASK_HDMI_INTR_SYNC      (1<<3)

#define GCLK_IDX_HDMI_PCLK         68
#define GCLK_NAME_HDMI_PCLK      "HDMI_PCLK"
#define GCLK_DEV_HDMI_PCLK      "CLKGATE_HDMI_PCLK"
#define GCLK_REG_HDMI_PCLK      (HHI_GCLK_MPEG2)
#define GCLK_MASK_HDMI_PCLK      (1<<4)

#define GCLK_IDX_RESERVED2_1         69
#define GCLK_NAME_RESERVED2_1      "RESERVED2_1"
#define GCLK_DEV_RESERVED2_1      "CLKGATE_RESERVED2_1"
#define GCLK_REG_RESERVED2_1      (HHI_GCLK_MPEG2)
#define GCLK_MASK_RESERVED2_1      (1<<5)

#define GCLK_IDX_RESERVED2_2        70
#define GCLK_NAME_RESERVED2_2     "RESERVED2_2"
#define GCLK_DEV_RESERVED2_2     "CLKGATE_RESERVED2_2"
#define GCLK_REG_RESERVED2_2     (HHI_GCLK_MPEG2)
#define GCLK_MASK_RESERVED2_2     (1<<6)

#define GCLK_IDX_RESERVED2_3         71
#define GCLK_NAME_RESERVED2_3      "RESERVED2_3"
#define GCLK_DEV_RESERVED2_3      "CLKGATE_RESERVED2_3"
#define GCLK_REG_RESERVED2_3      (HHI_GCLK_MPEG2)
#define GCLK_MASK_RESERVED2_3      (1<<7)

#define GCLK_IDX_MISC_USB1_TO_DDR         72
#define GCLK_NAME_MISC_USB1_TO_DDR      "MISC_USB1_TO_DDR"
#define GCLK_DEV_MISC_USB1_TO_DDR      "CLKGATE_MISC_USB1_TO_DDR"
#define GCLK_REG_MISC_USB1_TO_DDR      (HHI_GCLK_MPEG2)
#define GCLK_MASK_MISC_USB1_TO_DDR      (1<<8)

#define GCLK_IDX_MISC_USB0_TO_DDR         73
#define GCLK_NAME_MISC_USB0_TO_DDR      "MISC_USB0_TO_DDR"
#define GCLK_DEV_MISC_USB0_TO_DDR      "CLKGATE_MISC_USB0_TO_DDR"
#define GCLK_REG_MISC_USB0_TO_DDR      (HHI_GCLK_MPEG2)
#define GCLK_MASK_MISC_USB0_TO_DDR      (1<<9)

#define GCLK_IDX_RESERVED2_4        74
#define GCLK_NAME_RESERVED2_4      "RESERVED2_4"
#define GCLK_DEV_RESERVED2_4      "CLKGATE_RESERVED2_4"
#define GCLK_REG_RESERVED2_4      (HHI_GCLK_MPEG2)
#define GCLK_MASK_RESERVED2_4      (1<<10)

#define GCLK_IDX_MMC_PCLK         75
#define GCLK_NAME_MMC_PCLK      "MMC_PCLK"
#define GCLK_DEV_MMC_PCLK      "CLKGATE_MMC_PCLK"
#define GCLK_REG_MMC_PCLK      (HHI_GCLK_MPEG2)
#define GCLK_MASK_MMC_PCLK      (1<<11)

#define GCLK_IDX_MISC_DVIN         76
#define GCLK_NAME_MISC_DVIN      "MISC_DVIN"
#define GCLK_DEV_MISC_DVIN      "CLKGATE_MISC_DVIN"
#define GCLK_REG_MISC_DVIN      (HHI_GCLK_MPEG2)
#define GCLK_MASK_MISC_DVIN      (1<<12)

#define GCLK_IDX_RESERVED2_5         77
#define GCLK_NAME_RESERVED2_5      "RESERVED2_5"
#define GCLK_DEV_RESERVED2_5      "CLKGATE_RESERVED2_5"
#define GCLK_REG_RESERVED2_5      (HHI_GCLK_MPEG2)
#define GCLK_MASK_RESERVED2_5      (1<<13)

#define GCLK_IDX_RESERVED2_6         78
#define GCLK_NAME_RESERVED2_6      "RESERVED2_6"
#define GCLK_DEV_RESERVED2_6      "CLKGATE_RESERVED2_6"
#define GCLK_REG_RESERVED2_6      (HHI_GCLK_MPEG2)
#define GCLK_MASK_RESERVED2_6      (1<<14)

#define GCLK_IDX_UART2         79
#define GCLK_NAME_UART2      "UART2"
#define GCLK_DEV_UART2      "CLKGATE_UART2"
#define GCLK_REG_UART2      (HHI_GCLK_MPEG2)
#define GCLK_MASK_UART2      (1<<15)

#define GCLK_IDX_RESERVED2_7         80
#define GCLK_NAME_RESERVED2_7      "RESERVED2_7"
#define GCLK_DEV_RESERVED2_7      "CLKGATE_RESERVED2_7"
#define GCLK_REG_RESERVED2_7      (HHI_GCLK_MPEG2)
#define GCLK_MASK_RESERVED2_7      (1<<16)

#define GCLK_IDX_RESERVED2_8         81
#define GCLK_NAME_RESERVED2_8      "RESERVED2_8"
#define GCLK_DEV_RESERVED2_8      "CLKGATE_RESERVED2_8"
#define GCLK_REG_RESERVED2_8      (HHI_GCLK_MPEG2)
#define GCLK_MASK_RESERVED2_8      (1<<17)

#define GCLK_IDX_RESERVED2_9         82
#define GCLK_NAME_RESERVED2_9      "RESERVED2_9"
#define GCLK_DEV_RESERVED2_9      "CLKGATE_RESERVED2_9"
#define GCLK_REG_RESERVED2_9      (HHI_GCLK_MPEG2)
#define GCLK_MASK_RESERVED2_9      (1<<18)

#define GCLK_IDX_RESERVED2_A         83
#define GCLK_NAME_RESERVED2_A      "RESERVED2_A"
#define GCLK_DEV_RESERVED2_A      "CLKGATE_RESERVED2_A"
#define GCLK_REG_RESERVED2_A      (HHI_GCLK_MPEG2)
#define GCLK_MASK_RESERVED2_A      (1<<19)

#define GCLK_IDX_RESERVED2_B         84
#define GCLK_NAME_RESERVED2_B      "RESERVED2_B"
#define GCLK_DEV_RESERVED2_B      "CLKGATE_RESERVED2_B"
#define GCLK_REG_RESERVED2_B      (HHI_GCLK_MPEG2)
#define GCLK_MASK_RESERVED2_B      (1<<20)

#define GCLK_IDX_RESERVED2_C         85
#define GCLK_NAME_RESERVED2_C      "RESERVED2_C"
#define GCLK_DEV_RESERVED2_C      "CLKGATE_RESERVED2_C"
#define GCLK_REG_RESERVED2_C      (HHI_GCLK_MPEG2)
#define GCLK_MASK_RESERVED2_C      (1<<21)

#define GCLK_IDX_SANA        86
#define GCLK_NAME_SANA      "SANA"
#define GCLK_DEV_SANA      "CLKGATE_SANA"
#define GCLK_REG_SANA      (HHI_GCLK_MPEG2)
#define GCLK_MASK_SANA      (1<<22)

#define GCLK_IDX_RESERVED2_D        87
#define GCLK_NAME_RESERVED2_D      "RESERVED2_D"
#define GCLK_DEV_RESERVED2_D      "CLKGATE_RESERVED2_D"
#define GCLK_REG_RESERVED2_D      (HHI_GCLK_MPEG2)
#define GCLK_MASK_RESERVED2_D      (1<<23)

#define GCLK_IDX_RESERVED2_E        88
#define GCLK_NAME_RESERVED2_E      "RESERVED2_E"
#define GCLK_DEV_RESERVED2_E      "CLKGATE_RESERVED2_E"
#define GCLK_REG_RESERVED2_E      (HHI_GCLK_MPEG2)
#define GCLK_MASK_RESERVED2_E      (1<<24)

#define GCLK_IDX_VPU_INTR        89
#define GCLK_NAME_VPU_INTR      "VPU_INTR"
#define GCLK_DEV_VPU_INTR      "CLKGATE_VPU_INTR"
#define GCLK_REG_VPU_INTR      (HHI_GCLK_MPEG2)
#define GCLK_MASK_VPU_INTR      (1<<25)

#define GCLK_IDX_SECURE_AHP_APB3        90
#define GCLK_NAME_SECURE_AHP_APB3      "SECURE_AHP_APB3"
#define GCLK_DEV_SECURE_AHP_APB3      "CLKGATE_SECURE_AHP_APB3"
#define GCLK_REG_SECURE_AHP_APB3      (HHI_GCLK_MPEG2)
#define GCLK_MASK_SECURE_AHP_APB3      (1<<26)

#define GCLK_IDX_RESERVED2_F        91
#define GCLK_NAME_RESERVED2_F      "RESERVED2_F"
#define GCLK_DEV_RESERVED2_F      "CLKGATE_RESERVED2_F"
#define GCLK_REG_RESERVED2_F      (HHI_GCLK_MPEG2)
#define GCLK_MASK_RESERVED2_F      (1<<27)

#define GCLK_IDX_RESERVED2_10        92
#define GCLK_NAME_RESERVED2_10      "RESERVED2_10"
#define GCLK_DEV_RESERVED2_10      "CLKGATE_RESERVED2_10"
#define GCLK_REG_RESERVED2_10      (HHI_GCLK_MPEG2)
#define GCLK_MASK_RESERVED2_10      (1<<28)

#define GCLK_IDX_CLK81_TO_A9        93
#define GCLK_NAME_CLK81_TO_A9      "CLK81_TO_A9"
#define GCLK_DEV_CLK81_TO_A9      "CLKGATE_CLK81_TO_A9"
#define GCLK_REG_CLK81_TO_A9      (HHI_GCLK_MPEG2)
#define GCLK_MASK_CLK81_TO_A9      (1<<29)

#define GCLK_IDX_RESERVED2_11        94
#define GCLK_NAME_RESERVED2_11      "RESERVED2_11"
#define GCLK_DEV_RESERVED2_11      "CLKGATE_RESERVED2_11"
#define GCLK_REG_RESERVED2_11      (HHI_GCLK_MPEG2)
#define GCLK_MASK_RESERVED2_11      (1<<30)

#define GCLK_IDX_RESERVED2_12        95
#define GCLK_NAME_RESERVED2_12      "RESERVED2_12"
#define GCLK_DEV_RESERVED2_12      "CLKGATE_RESERVED2_12"
#define GCLK_REG_RESERVED2_12      (HHI_GCLK_MPEG2)
#define GCLK_MASK_RESERVED2_12      (1<<31)

/**************************************************************/

#define GCLK_IDX_RESERVED3_0        96
#define GCLK_NAME_RESERVED3_0      "RESERVED3_0"
#define GCLK_DEV_RESERVED3_0      "CLKGATE_RESERVED3_0"
#define GCLK_REG_RESERVED3_0      (HHI_GCLK_MPEG2)
#define GCLK_MASK_RESERVED3_0      (1<<0)

#define GCLK_IDX_VCLK2_VENCI         97
#define GCLK_NAME_VCLK2_VENCI      "VCLK2_VENCI"
#define GCLK_DEV_VCLK2_VENCI      "CLKGATE_VCLK2_VENCI"
#define GCLK_REG_VCLK2_VENCI      (HHI_GCLK_OTHER)
#define GCLK_MASK_VCLK2_VENCI      (1<<1)

#define GCLK_IDX_VCLK2_VENCI1         98
#define GCLK_NAME_VCLK2_VENCI1      "VCLK2_VENCI1"
#define GCLK_DEV_VCLK2_VENCI1      "CLKGATE_VCLK2_VENCI1"
#define GCLK_REG_VCLK2_VENCI1      (HHI_GCLK_OTHER)
#define GCLK_MASK_VCLK2_VENCI1      (1<<2)

#define GCLK_IDX_VCLK2_VENCP         99
#define GCLK_NAME_VCLK2_VENCP      "VCLK2_VENCP"
#define GCLK_DEV_VCLK2_VENCP      "CLKGATE_VCLK2_VENCP"
#define GCLK_REG_VCLK2_VENCP      (HHI_GCLK_OTHER)
#define GCLK_MASK_VCLK2_VENCP      (1<<3)

#define GCLK_IDX_VCLK2_VENCP1         100
#define GCLK_NAME_VCLK2_VENCP1      "VCLK2_VENCP1"
#define GCLK_DEV_VCLK2_VENCP1      "CLKGATE_VCLK2_VENCP1"
#define GCLK_REG_VCLK2_VENCP1      (HHI_GCLK_OTHER)
#define GCLK_MASK_VCLK2_VENCP1      (1<<4)

#define GCLK_IDX_VCLK2_VENCT         101
#define GCLK_NAME_VCLK2_VENCT      "VCLK2_VENCT"
#define GCLK_DEV_VCLK2_VENCT      "CLKGATE_VCLK2_VENCT"
#define GCLK_REG_VCLK2_VENCT      (HHI_GCLK_OTHER)
#define GCLK_MASK_VCLK2_VENCT      (1<<5)

#define GCLK_IDX_VCLK2_VENCT1         102
#define GCLK_NAME_VCLK2_VENCT1      "VCLK2_VENCT1"
#define GCLK_DEV_VCLK2_VENCT1      "CLKGATE_VCLK2_VENCT1"
#define GCLK_REG_VCLK2_VENCT1      (HHI_GCLK_OTHER)
#define GCLK_MASK_VCLK2_VENCT1      (1<<6)

#define GCLK_IDX_VCLK2_OTHER         103
#define GCLK_NAME_VCLK2_OTHER      "VCLK2_OTHER"
#define GCLK_DEV_VCLK2_OTHER      "CLKGATE_VCLK2_OTHER"
#define GCLK_REG_VCLK2_OTHER      (HHI_GCLK_OTHER)
#define GCLK_MASK_VCLK2_OTHER      (1<<7)

#define GCLK_IDX_VCLK2_ENCI         104
#define GCLK_NAME_VCLK2_ENCI      "VCLK2_ENCI"
#define GCLK_DEV_VCLK2_ENCI      "CLKGATE_VCLK2_ENCI"
#define GCLK_REG_VCLK2_ENCI      (HHI_GCLK_OTHER)
#define GCLK_MASK_VCLK2_ENCI      (1<<8)

#define GCLK_IDX_VCLK2_ENCP         105
#define GCLK_NAME_VCLK2_ENCP      "VCLK2_ENCP"
#define GCLK_DEV_VCLK2_ENCP      "CLKGATE_VCLK2_ENCP"
#define GCLK_REG_VCLK2_ENCP      (HHI_GCLK_OTHER)
#define GCLK_MASK_VCLK2_ENCP      (1<<9)

#define GCLK_IDX_DAC_CLK         106
#define GCLK_NAME_DAC_CLK      "DAC_CLK"
#define GCLK_DEV_DAC_CLK      "CLKGATE_DAC_CLK"
#define GCLK_REG_DAC_CLK      (HHI_GCLK_OTHER)
#define GCLK_MASK_DAC_CLK      (1<<10)

#define GCLK_IDX_RESERVED3_1        107
#define GCLK_NAME_RESERVED3_1      "RESERVED3_1"
#define GCLK_DEV_RESERVED3_1      "CLKGATE_RESERVED3_1"
#define GCLK_REG_RESERVED3_1      (HHI_GCLK_MPEG2)
#define GCLK_MASK_RESERVED3_1      (1<<11)

#define GCLK_IDX_RESERVED3_2        108
#define GCLK_NAME_RESERVED3_2      "RESERVED3_2"
#define GCLK_DEV_RESERVED3_2      "CLKGATE_RESERVED3_2"
#define GCLK_REG_RESERVED3_2      (HHI_GCLK_MPEG2)
#define GCLK_MASK_RESERVED3_2      (1<<12)

#define GCLK_IDX_RESERVED3_3        109
#define GCLK_NAME_RESERVED3_3      "RESERVED3_3"
#define GCLK_DEV_RESERVED3_3      "CLKGATE_RESERVED3_3"
#define GCLK_REG_RESERVED3_3      (HHI_GCLK_MPEG2)
#define GCLK_MASK_RESERVED3_3      (1<<13)

#define GCLK_IDX_AIU_AOCLK         110
#define GCLK_NAME_AIU_AOCLK      "AIU_AOCLK"
#define GCLK_DEV_AIU_AOCLK      "CLKGATE_AIU_AOCLK"
#define GCLK_REG_AIU_AOCLK      (HHI_GCLK_OTHER)
#define GCLK_MASK_AIU_AOCLK      (1<<14)

#define GCLK_IDX_RESERVED3_4         111
#define GCLK_NAME_RESERVED3_4      "RESERVED3_4"
#define GCLK_DEV_RESERVED3_4      "CLKGATE_RESERVED3_4"
#define GCLK_REG_RESERVED3_4      (HHI_GCLK_OTHER)
#define GCLK_MASK_RESERVED3_4      (1<<15)

#define GCLK_IDX_AIU_ICE958_AMCLK         112
#define GCLK_NAME_AIU_ICE958_AMCLK      "AIU_ICE958_AMCLK"
#define GCLK_DEV_AIU_ICE958_AMCLK      "CLKGATE_AIU_ICE958_AMCLK"
#define GCLK_REG_AIU_ICE958_AMCLK      (HHI_GCLK_OTHER)
#define GCLK_MASK_AIU_ICE958_AMCLK      (1<<16)

#define GCLK_IDX_RESERVED3_5         113
#define GCLK_NAME_RESERVED3_5      "RESERVED3_5"
#define GCLK_DEV_RESERVED3_5      "CLKGATE_RESERVED3_5"
#define GCLK_REG_RESERVED3_5      (HHI_GCLK_OTHER)
#define GCLK_MASK_RESERVED3_5      (1<<17)

#define GCLK_IDX_RESERVED3_6         114
#define GCLK_NAME_RESERVED3_6      "RESERVED3_6"
#define GCLK_DEV_RESERVED3_6      "CLKGATE_RESERVED3_6"
#define GCLK_REG_RESERVED3_6      (HHI_GCLK_OTHER)
#define GCLK_MASK_RESERVED3_6      (1<<18)

#define GCLK_IDX_RESERVED3_7         115
#define GCLK_NAME_RESERVED3_7      "RESERVED3_7"
#define GCLK_DEV_RESERVED3_7      "CLKGATE_RESERVED3_7"
#define GCLK_REG_RESERVED3_7      (HHI_GCLK_OTHER)
#define GCLK_MASK_RESERVED3_7      (1<<19)

#define GCLK_IDX_ENC480P         116
#define GCLK_NAME_ENC480P      "ENC480P"
#define GCLK_DEV_ENC480P      "CLKGATE_ENC480P"
#define GCLK_REG_ENC480P      (HHI_GCLK_OTHER)
#define GCLK_MASK_ENC480P      (1<<20)

#define GCLK_IDX_RANDOM_NUM_GEN1         117
#define GCLK_NAME_RANDOM_NUM_GEN1      "RANDOM_NUM_GEN1"
#define GCLK_DEV_RANDOM_NUM_GEN1      "CLKGATE_RANDOM_NUM_GEN1"
#define GCLK_REG_RANDOM_NUM_GEN1      (HHI_GCLK_OTHER)
#define GCLK_MASK_RANDOM_NUM_GEN1      (1<<21)

#define GCLK_IDX_GCLK_VENCL_INT         118
#define GCLK_NAME_GCLK_VENCL_INT      "GCLK_VENCL_INT"
#define GCLK_DEV_GCLK_VENCL_INT      "CLKGATE_GCLK_VENCL_INT"
#define GCLK_REG_GCLK_VENCL_INT      (HHI_GCLK_OTHER)
#define GCLK_MASK_GCLK_VENCL_INT      (1<<22)

#define GCLK_IDX_RESERVED3_8         119
#define GCLK_NAME_RESERVED3_8      "RESERVED3_8"
#define GCLK_DEV_RESERVED3_8      "CLKGATE_RESERVED3_8"
#define GCLK_REG_RESERVED3_8      (HHI_GCLK_OTHER)
#define GCLK_MASK_RESERVED3_8      (1<<23)

#define GCLK_IDX_MMC_CLK         120
#define GCLK_NAME_MMC_CLK      "MMC_CLK"
#define GCLK_DEV_MMC_CLK      "CLKGATE_MMC_CLK"
#define GCLK_REG_MMC_CLK      (HHI_GCLK_OTHER)
#define GCLK_MASK_MMC_CLK      (1<<24)

#define GCLK_IDX_VCLK2_VENCL         121
#define GCLK_NAME_VCLK2_VENCL      "VCLK2_VENCL"
#define GCLK_DEV_VCLK2_VENCL      "CLKGATE_VCLK2_VENCL"
#define GCLK_REG_VCLK2_VENCL      (HHI_GCLK_OTHER)
#define GCLK_MASK_VCLK2_VENCL      (1<<25)

#define GCLK_IDX_VCLK2_OTHER1         122
#define GCLK_NAME_VCLK2_OTHER1      "VCLK2_OTHER1"
#define GCLK_DEV_VCLK2_OTHER1      "CLKGATE_VCLK2_OTHER1"
#define GCLK_REG_VCLK2_OTHER1      (HHI_GCLK_OTHER)
#define GCLK_MASK_VCLK2_OTHER1      (1<<26)

#define GCLK_IDX_RESERVED3_9         123
#define GCLK_NAME_RESERVED3_9      "RESERVED3_9"
#define GCLK_DEV_RESERVED3_9      "CLKGATE_RESERVED3_9"
#define GCLK_REG_RESERVED3_9      (HHI_GCLK_OTHER)
#define GCLK_MASK_RESERVED3_9      (1<<27)

#define GCLK_IDX_RESERVED3_A         124
#define GCLK_NAME_RESERVED3_A      "RESERVED3_A"
#define GCLK_DEV_RESERVED3_A      "CLKGATE_RESERVED3_A"
#define GCLK_REG_RESERVED3_A      (HHI_GCLK_OTHER)
#define GCLK_MASK_RESERVED3_A      (1<<28)

#define GCLK_IDX_RESERVED3_B         125
#define GCLK_NAME_RESERVED3_B      "RESERVED3_B"
#define GCLK_DEV_RESERVED3_B      "CLKGATE_RESERVED3_B"
#define GCLK_REG_RESERVED3_B      (HHI_GCLK_OTHER)
#define GCLK_MASK_RESERVED3_B      (1<<29)

#define GCLK_IDX_RESERVED3_C         126
#define GCLK_NAME_RESERVED3_C      "RESERVED3_C"
#define GCLK_DEV_RESERVED3_C      "CLKGATE_RESERVED3_C"
#define GCLK_REG_RESERVED3_C      (HHI_GCLK_OTHER)
#define GCLK_MASK_RESERVED3_C      (1<<30)

#define GCLK_IDX_EDP_CLK         127
#define GCLK_NAME_EDP_CLK      "EDP_CLK"
#define GCLK_DEV_EDP_CLK      "CLKGATE_EDP_CLK"
#define GCLK_REG_EDP_CLK      (HHI_GCLK_OTHER)
#define GCLK_MASK_EDP_CLK      (1<<31)

/**************************************************************/

#define GCLK_IDX_MEDIA_CPU         128
#define GCLK_NAME_MEDIA_CPU      "MEDIA_CPU"
#define GCLK_DEV_MEDIA_CPU      "CLKGATE_MEDIA_CPU"
#define GCLK_REG_MEDIA_CPU      (HHI_GCLK_AO)
#define GCLK_MASK_MEDIA_CPU      (1<<0)

#define GCLK_IDX_AHB_SRAM         129
#define GCLK_NAME_AHB_SRAM      "AHB_SRAM"
#define GCLK_DEV_AHB_SRAM      "CLKGATE_AHB_SRAM"
#define GCLK_REG_AHB_SRAM      (HHI_GCLK_AO)
#define GCLK_MASK_AHB_SRAM      (1<<1)

#define GCLK_IDX_AHB_BUS         130
#define GCLK_NAME_AHB_BUS      "AHB_BUS"
#define GCLK_DEV_AHB_BUS      "CLKGATE_AHB_BUS"
#define GCLK_REG_AHB_BUS      (HHI_GCLK_AO)
#define GCLK_MASK_AHB_BUS      (1<<2)

#define GCLK_IDX_AO_REGS         131
#define GCLK_NAME_AO_REGS      "AO_REGS"
#define GCLK_DEV_AO_REGS      "CLKGATE_AO_REGS"
#define GCLK_REG_AO_REGS      (HHI_GCLK_AO)
#define GCLK_MASK_AO_REGS      (1<<3)

#define GCLK_IDX_MAX 132
extern short GCLK_ref[GCLK_IDX_MAX];

#define REGISTER_CLK(_MOD) \
static struct clk CLK_##_MOD = {            \
	.name       = GCLK_NAME_##_MOD,             \
	.clock_index = GCLK_IDX_##_MOD,          \
	.clock_gate_reg_adr = GCLK_REG_##_MOD,  \
	.clock_gate_reg_mask = GCLK_MASK_##_MOD,    \
}

#define CLK_LOOKUP_ITEM(_MOD) \
	{           \
		.dev_id = GCLK_DEV_##_MOD, \
		.con_id = GCLK_NAME_##_MOD, \
		.clk    = &CLK_##_MOD,   \
	}



/**********************/
/* internal audio dac control */
#define ADAC_RESET                      (0x5000+0x00*4)
#define ADAC_LATCH                      (0x5000+0x01*4)
#define ADAC_POWER_CTRL_REG1            (0x5000+0x10*4)
#define ADAC_POWER_CTRL_REG2            (0x5000+0x11*4)

extern int audio_internal_dac_disable(void);

/* video dac control */
extern int  video_dac_enable(unsigned char enable_mask);

extern int  video_dac_disable(void);


#endif
