// startup.c 
#include "COTS/LIB/Std_Types.h"
void Reset_Handler() ;
void Default_Handler(){
	Reset_Handler();
}
void NMI_Handler() __attribute__((weak,alias("Default_Handler")));
void HardFault_Handler() __attribute__((weak,alias("Default_Handler")));
void MemManage_Handler() __attribute__((weak,alias("Default_Handler")));
void BusFault_Handler() __attribute__((weak,alias("Default_Handler")));
void UsageFault_Handler() __attribute__((weak,alias("Default_Handler")));
void USB_HP_CAN1_TX_IRQHandler() __attribute__((weak,alias("Default_Handler")));
void USB_LP_CAN1_RX0_IRQHandler() __attribute__((weak,alias("Default_Handler")));
void CAN1_RX1_IRQHandler() __attribute__((weak,alias("Default_Handler")));
void CAN1_SCE_IRQHandler() __attribute__((weak,alias("Default_Handler")));
void SysTick_Handler() __attribute__((weak,alias("Default_Handler")));
extern uint32 _stak_top;
uint32 vectors[70] __attribute__((section(".vectors")))={
	(uint32) &_stak_top, 
	(uint32) &Reset_Handler,
	(uint32) &NMI_Handler,
	(uint32) &HardFault_Handler ,
	(uint32) &MemManage_Handler,
	(uint32) &BusFault_Handler ,
	(uint32) &UsageFault_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& SysTick_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& USB_HP_CAN1_TX_IRQHandler
   ,(uint32)& USB_LP_CAN1_RX0_IRQHandler
   ,(uint32)& CAN1_RX1_IRQHandler
   ,(uint32)& CAN1_SCE_IRQHandler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
   ,(uint32)& Default_Handler
};

extern uint32 _E_text;
extern uint32 _S_data;
extern uint32 _E_data;
extern uint32 _S_bss;
extern uint32 _E_bss;
void Reset_Handler()
{
	// copy .data from flash to sram
	int i ;
	uint32 data_size = (uint8*)&_E_data - (uint8*)&_S_data ;
	uint8*  P_src =(uint8*)&_E_text;
	uint8* P_dst = (uint8*)&_S_data;
	for ( i = 0; i < data_size; ++i)
	{
		*((uint8*)P_dst++)=*((uint8*)P_src++);
	}
	// init the .bss with zero
	uint32 bss_size = (uint8*)&_E_bss - (uint8*)&_S_bss ;
	P_dst = (uint8*)&_S_bss;
	for ( i = 0; i < bss_size; ++i)
	{
		*((uint8*)P_dst++)=(uint8)0;
	}
	main();
}




