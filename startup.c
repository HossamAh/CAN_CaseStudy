// startup.c 
#include "COTS/LIB/Std_Types.h"
void Rest_Handler() ;
void Default_Handler(){
	Rest_Handler();
}
void NMI_Handler() __attribute__((weak,alias("Default_Handler")));
void H_fault_Handler() __attribute__((weak,alias("Default_Handler")));
void MM_Fault_Handler() __attribute__((weak,alias("Default_Handler")));
void Bus_Fault() __attribute__((weak,alias("Default_Handler")));
void Usage_Fault_Handler() __attribute__((weak,alias("Default_Handler")));
extern uint32 _stak_top;
uint32 vectors[] __attribute__((section(".vectors")))={
	(uint32) &_stak_top, 
	(uint32) &Rest_Handler,
	(uint32) &NMI_Handler,
	(uint32) &H_fault_Handler ,
	(uint32) &MM_Fault_Handler,
	(uint32) &Bus_Fault ,
	(uint32) &Usage_Fault_Handler
};
extern uint32 _E_text;
extern uint32 _S_data;
extern uint32 _E_data;
extern uint32 _S_bss;
extern uint32 _E_bss;
void Rest_Handler()
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




