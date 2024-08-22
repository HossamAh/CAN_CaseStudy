/*---------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------
 *         File:  Mcu_Hw.h
 *       Module:  Mcu_Hw
 *  Description:  Microcontroller Registers definition header file    
---------------------------------------------------------------------------------------------------------------------*/
#ifndef MCU_HW_H
#define MCU_HW_H
/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/
#include "Std_Types.h"

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL CONSTANT MACROS
---------------------------------------------------------------------------------------------------------------------*/
#define CORTEXM4_PERI_BASE_ADDRESS             0xE000E000
#define APINT                                  *((volatile uint32*)(CORTEXM4_PERI_BASE_ADDRESS+0xD0C))
#define INTCTRL                                *((volatile INTCTRL_Tag*)(CORTEXM4_PERI_BASE_ADDRESS+0xD04))
#define NVIC_PRI_BASE                          (CORTEXM4_PERI_BASE_ADDRESS+0x400)
#define SYSPRI1                                *((volatile uint32*)(CORTEXM4_PERI_BASE_ADDRESS+0xD18))
#define SYSPRI2                                *((volatile uint32*)(CORTEXM4_PERI_BASE_ADDRESS+0xD1C))
#define SYSPRI3                                *((volatile uint32*)(CORTEXM4_PERI_BASE_ADDRESS+0xD20))
#define NVIC_EN_BASE                           (CORTEXM4_PERI_BASE_ADDRESS+0x100)
#define NVIC_DIS_BASE                           (CORTEXM4_PERI_BASE_ADDRESS+0x180)
#define SCB_SYSHNDCTRL                          *((volatile uint32*)CORTEXM4_PERI_BASE_ADDRESS+0xD24)


#define APB

#ifdef APB
#define GPIO_BASE_ADDRESS_COMMON       (0x40004000)
#define GPIO_BASE_ADDRESS              (0x40024000)
#endif

#ifdef AHB 
#define GPIO_BASE_ADDRESS       (0x40058000)
#endif

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL FUNCTION MACROS
---------------------------------------------------------------------------------------------------------------------*/
#ifdef APB
#define GPIO_ADDRESS(x)        ((x<4)?GPIO_BASE_ADDRESS_COMMON+(0x1000*x):GPIO_BASE_ADDRESS+(0x1000*(x-4)))
#endif

#ifdef AHB
#define GPIO_ADDRESS(x)        (GPIO_BASE_ADDRESS+(0x1000*x))
#endif
/*---------------------------------------------------------------------------------------------------------------------
 *  GPIO Registers
---------------------------------------------------------------------------------------------------------------------*/
#define GPIODATA(portId)    (*((volatile uint32*)(GPIO_ADDRESS(portId))))
#define GPIODIR(portId)    (*((volatile uint32*)(GPIO_ADDRESS(portId)+0x400)))
#define GPIOIS(portId)    (*((volatile uint32*)(GPIO_ADDRESS(portId)+0x404)))
#define GPIOIBE(portId)    (*((volatile uint32*)(GPIO_ADDRESS(portId)+0x408)))
#define GPIOIEV(portId)    (*((volatile uint32*)(GPIO_ADDRESS(portId)+0x40c)))
#define GPIOIM(portId)    (*((volatile uint32*)(GPIO_ADDRESS(portId)+0x410)))
#define GPIORIS(portId)    (*((volatile uint32*)(GPIO_ADDRESS(portId)+0x414)))
#define GPIOMIS(portId)    (*((volatile uint32*)(GPIO_ADDRESS(portId)+0x418)))
#define GPIOICR(portId)    (*((volatile uint32*)(GPIO_ADDRESS(portId)+0x41C)))
#define GPIOAFSEL(portId)    (*((volatile uint32*)(GPIO_ADDRESS(portId)+0x420)))
#define GPIOR2R(portId)    (*((volatile uint32*)(GPIO_ADDRESS(portId)+0x500)))
#define GPIOR4R(portId)    (*((volatile uint32*)(GPIO_ADDRESS(portId)+0x504)))
#define GPIOR8R(portId)    (*((volatile uint32*)(GPIO_ADDRESS(portId)+0x508)))
#define GPIOODR(portId)    (*((volatile uint32*)(GPIO_ADDRESS(portId)+0x50C)))
#define GPIOPUR(portId)    (*((volatile uint32*)(GPIO_ADDRESS(portId)+0x510)))
#define GPIOPDR(portId)    (*((volatile uint32*)(GPIO_ADDRESS(portId)+0x514)))
#define GPIOSLR(portId)    (*((volatile uint32*)(GPIO_ADDRESS(portId)+0x518)))
#define GPIODEN(portId)    (*((volatile uint32*)(GPIO_ADDRESS(portId)+0x51C)))
#define GPIOLOCK(portId)    (*((volatile uint32*)(GPIO_ADDRESS(portId)+0x520)))
#define GPIOCR(portId)    (*((volatile uint32*)(GPIO_ADDRESS(portId)+0x524)))
#define GPIOAMSEL(portId)    (*((volatile uint32*)(GPIO_ADDRESS(portId)+0x528)))
#define GPIOPCTL(portId)    (*((volatile uint32*)(GPIO_ADDRESS(portId)+0x52C)))
#define GPIOADCCTL(portId)  (*((volatile uint32*)(GPIO_ADDRESS(portId)+0x530)))
#endif