//// GPIO ///

#define GPIO_PA_BASE  0x40006000
#define GPIO_PC_BASE  0x40006048
#define GPIO_INT_BASE 0x40006100

// GPIO_PA OFFSETS
#define GPIO_PA_CTRL     0x00
#define GPIO_PA_MODEL    0x04
#define GPIO_PA_MODEH    0x08
#define GPIO_PA_DOUT     0x0c
#define GPIO_PA_DOUTSET  0x10
#define GPIO_PA_DOUTCLR  0x14
#define GPIO_PA_DOUTTGL  0x18
#define GPIO_PA_DIN      0x1c
#define GPIO_PA_PINLOCKN 0x20

// GPIO_PC OFFSETS
#define GPIO_PC_CTRL     0x00
#define GPIO_PC_MODEL    0x04
#define GPIO_PC_MODEH    0x08
#define GPIO_PC_DOUT     0x0c
#define GPIO_PC_DOUTSET  0x10
#define GPIO_PC_DOUTCLR  0x14
#define GPIO_PC_DOUTTGL  0x18
#define GPIO_PC_DIN      0x1c
#define GPIO_PC_PINLOCKN 0x20

// GPIO INTERRUPT
#define GPIO_INT_BASE 0x40006100

// GPIO_INT OFFSETS
#define GPIO_EXTIPSELL   0x00
#define GPIO_EXTIPSELH   0x04
#define GPIO_EXTIRISE    0x08
#define GPIO_EXTIFALL    0x0c
#define GPIO_IEN         0x10
#define GPIO_IFC         0x1c

// CMU

#define CMU_BASE2 0x400c8000

#define CMU_HFPERCLKDIV  ((volatile uint32_t*)(CMU_BASE2 + 0x008))
#define CMU_HFCORECLKEN0 ((volatile uint32_t*)(CMU_BASE2 + 0x040))
#define CMU_HFPERCLKEN0  ((volatile uint32_t*)(CMU_BASE2 + 0x044))
#define CMU_CMD          ((volatile uint32_t*)(CMU_BASE2 + 0x024))

#define CMU2_HFPERCLKEN0_DAC0   (1 << 17)
#define CMU2_HFPERCLKEN0_PRS    (1 << 15)
#define CMU2_HFPERCLKEN0_GPIO   (1 << 13)
#define CMU2_HFPERCLKEN0_TIMER1 (1 << 6)

#define CMU_HFCORECLKEN0_DMA (1 << 0)

// TIMER1

#define TIMER1_BASE 0x40010400

#define TIMER1_CMD ((volatile uint32_t*)(TIMER1_BASE + 0x04))
#define TIMER1_IEN ((volatile uint32_t*)(TIMER1_BASE + 0x0c))
#define TIMER1_IFC ((volatile uint32_t*)(TIMER1_BASE + 0x18))
#define TIMER1_TOP ((volatile uint32_t*)(TIMER1_BASE + 0x1c))
#define TIMER1_CNT ((volatile uint32_t*)(TIMER1_BASE + 0x24))

// NVIC

#define ISER0 ((volatile uint32_t*)0xe000e100)
#define ISER1 ((volatile uint32_t*)0xe000e104)
#define ICER0 ((volatile uint32_t*)0xe000e180)
#define ICER1 ((volatile uint32_t*)0xe000e184)
#define ISPR0 ((volatile uint32_t*)0xe000e200)
#define ISPR1 ((volatile uint32_t*)0xe000e204)
#define ICPR0 ((volatile uint32_t*)0xe000e280)
#define ICPR1 ((volatile uint32_t*)0xe000e284)
#define IABR0 ((volatile uint32_t*)0xe000e300)
#define IABR1 ((volatile uint32_t*)0xe000e304)

// IPR

#define IPR_BASE  0xe000e400

#define IPR0 ((volatile uint32_t*)(IPR_BASE + 0x00))
#define IPR1 ((volatile uint32_t*)(IPR_BASE + 0x04))
#define IPR2 ((volatile uint32_t*)(IPR_BASE + 0x08))
#define IPR3 ((volatile uint32_t*)(IPR_BASE + 0x0c))

// EMU

#define EMU_BASE2 0x400c6000

#define EMU_CTRL ((volatile uint32_t*)(EMU_BASE2 + 0x000))

// DAC0

#define DAC0_BASE2 0x40004000

#define DAC0_CTRL     ((volatile uint32_t*)(DAC0_BASE2 + 0x000))
#define DAC0_CH0CTRL  ((volatile uint32_t*)(DAC0_BASE2 + 0x008))
#define DAC0_CH1CTRL  ((volatile uint32_t*)(DAC0_BASE2 + 0x00c))
#define DAC0_IEN      ((volatile uint32_t*)(DAC0_BASE2 + 0x010))
#define DAC0_IF       ((volatile uint32_t*)(DAC0_BASE2 + 0x014))
#define DAC0_IFS      ((volatile uint32_t*)(DAC0_BASE2 + 0x018))
#define DAC0_IFC      ((volatile uint32_t*)(DAC0_BASE2 + 0x01c))
#define DAC0_CH0DATA  ((volatile uint32_t*)(DAC0_BASE2 + 0x020))
#define DAC0_CH1DATA  ((volatile uint32_t*)(DAC0_BASE2 + 0x024))
#define DAC0_COMBDATA ((volatile uint32_t*)(DAC0_BASE2 + 0x028))

// DMA

#define DMA_BASE 0x400c2000

#define DMA_STATUS      ((volatile uint32_t*)(DMA_BASE + 0x0000))
#define DMA_CONFIG      ((volatile uint32_t*)(DMA_BASE + 0x0004))
#define DMA_CTRLBASE    ((volatile uint32_t*)(DMA_BASE + 0x0008))
#define DMA_ALTCTRLBASE ((volatile uint32_t*)(DMA_BASE + 0x000c))
#define DMA_CHUSEBURSTS ((volatile uint32_t*)(DMA_BASE + 0x0018))
#define DMA_CHUSEBURSTC ((volatile uint32_t*)(DMA_BASE + 0x001c))
#define DMA_REQMASKC    ((volatile uint32_t*)(DMA_BASE + 0x0024))
#define DMA_CHENS       ((volatile uint32_t*)(DMA_BASE + 0x0028))
#define DMA_CHALTC      ((volatile uint32_t*)(DMA_BASE + 0x0034))
#define DMA_IFC         ((volatile uint32_t*)(DMA_BASE + 0x1008))
#define DMA_IEN         ((volatile uint32_t*)(DMA_BASE + 0x100c))
#define DMA_CH0_CTRL    ((volatile uint32_t*)(DMA_BASE + 0x1100))

// PRS

#define PRS_BASE 0x400cc000

#define PRS_CH0_CTRL ((volatile uint32_t*)(PRS_BASE + 0x010))

// System Control Block

#define SCR          ((volatile uint32_t*)0xe000ed10)
#define SYSTICK_CTRL ((volatile uint32_t*)0xe000e010)
#define SYSTICK_LOAD ((volatile uint32_t*)0xe000e014)

