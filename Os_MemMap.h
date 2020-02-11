
/*Arm Compiler # Pragmas */
/*
#pragma arm section  code ="Name0",rodata="Name1",rwdata="Name2",zidata="Name3"		 

to place functions and variables in separate  named sections.
 The scatter-loading description file can then be used to locate these at a
particular address in memory.
• code		//Code section
• rodata	//Read only section
• rwdata	//Read write section 
• zidata	//zero initialized 	

#pragma pack(n)		//n aligenment as bytes 1,2,4,8

Packed objects are read and written using unaligned accesses.

#pragma arm section zidata
int i, j; // uninitialized data in non_initialized section (without the pragma,
             would be in .bss section by default)

*/
#define MEMMAP_ERROR 
		/**********************Data Section**********************/
		
/*Init-Aligenment*/
	/*Start*/
 #ifdef OS_START_SEC_VAR_INIT_8
		//define memory aligenment function to 8 bits 
	#undef OS_START_SEC_VAR_INIT_8
	#define START_SECTION_DATA_INIT_8
 
 #elif	OS_START_SEC_VAR_INIT_16
		//define memory aligenment function to 16 bits  
		#undef OS_START_SEC_VAR_INIT_16
		#define START_SECTION_DATA_INIT_16
		
 #elif	OS_START_SEC_VAR_INIT_32
		//define memory aligenment function to 32 bits  
		#undef OS_START_SEC_VAR_INIT_32
		#define START_SECTION_DATA_INIT_32
		
#elif	OS_START_SEC_VAR_INIT_64
		//define memory aligenment function to 64 bits  
		#undef OS_START_SEC_VAR_INIT_64
		#define START_SECTION_DATA_INIT_64
 #endif
	/*Stop*/
 #ifdef OS_STOP_SEC_VAR_INIT_8
		//define memory aligenment function to 8 bits 
	#undef OS_STOP_SEC_VAR_INIT_8
	#define STOP_SECTION_DATA_INIT_8
 
 #elif	OS_STOP_SEC_VAR_INIT_16
		//define memory aligenment function to 16 bits  
		#undef OS_STOP_SEC_VAR_INIT_16
		#define STOP_SECTION_DATA_INIT_16
		
 #elif	OS_STOP_SEC_VAR_INIT_32
		//define memory aligenment function to 32 bits  
		#undef OS_STOP_SEC_VAR_INIT_32
		#define STOP_SECTION_DATA_INIT_32
		
#elif	OS_STOP_SEC_VAR_INIT_64
		//define memory aligenment function to 64 bits  
		#undef OS_STOP_SEC_VAR_INIT_64
		#define STOP_SECTION_DATA_INIT_64
 #endif
/*****************************************/
/*Non_Init-Aligenment*/
	/*Start*/
 #ifdef OS_START_SEC_VAR_NO_INIT_8
		//define memory aligenment function to 8 bits 
	#undef OS_START_SEC_VAR_NO_INIT_8
	#define START_SECTION_DATA_NO_INIT_8
 
 #elif	OS_START_SEC_VAR_NO_INIT_16
		//define memory aligenment function to 16 bits  
		#undef OS_START_SEC_VAR_NO_INIT_16
		#define START_SECTION_DATA_NO_INIT_16
		
 #elif	OS_START_SEC_VAR_NO_INIT_32
		//define memory aligenment function to 32 bits  
		#undef OS_START_SEC_VAR_NO_INIT_32
		#define START_SECTION_DATA_NO_INIT_32
		
#elif	OS_START_SEC_VAR_NO_INIT_64
		//define memory aligenment function to 64 bits  
		#undef OS_START_SEC_VAR_NO_INIT_64
		#define START_SECTION_DATA_NO_INIT_64
 #endif
 /*Stop*/
 #ifdef OS_STOP_SEC_VAR_NO_INIT_8
		//define memory aligenment function to 8 bits 
	#undef OS_STOP_SEC_VAR_NO_INIT_8
	#define STOP_SECTION_DATA_NO_INIT_8
 
 #elif	OS_STOP_SEC_VAR_NO_INIT_16
		//define memory aligenment function to 16 bits  
		#undef OS_STOP_SEC_VAR_NO_INIT_16
		#define STOP_SECTION_DATA_NO_INIT_16
		
 #elif	OS_STOP_SEC_VAR_NO_INIT_32
		//define memory aligenment function to 32 bits  
		#undef OS_STOP_SEC_VAR_NO_INIT_32
		#define STOP_SECTION_DATA_NO_INIT_32
		
#elif	OS_STOP_SEC_VAR_NO_INIT_64
		//define memory aligenment function to 64 bits  
		#undef OS_STOP_SEC_VAR_NO_INIT_64
		#define STOP_SECTION_DATA_NO_INIT_64
 #endif
/*****************************************/
/*Cleared-Aligenment*/
	/*Start*/
 #ifdef OS_START_SEC_VAR_CLEARED_8
		//define memory aligenment function to 8 bits 
	#undef OS_START_SEC_VAR_CLEARED_8
	#define START_SECTION_DATA_CLEARED_8
 
 #elif	OS_START_SEC_VAR_CLEARED_16
		//define memory aligenment function to 16 bits  
		#undef OS_START_SEC_VAR_CLEARED_16
		#define START_SECTION_DATA_CLEARED_16
		
 #elif	OS_START_SEC_VAR_CLEARED_32
		//define memory aligenment function to 32 bits  
		#undef OS_START_SEC_VAR_CLEARED_32
		#define START_SECTION_DATA_CLEARED_32
		
#elif	OS_START_SEC_VAR_CLEARED_64
		//define memory aligenment function to 64 bits  
		#undef OS_START_SEC_VAR_CLEARED_64
		#define START_SECTION_DATA_CLEARED_64
 #endif
 	/*Stop*/
 #ifdef OS_STOP_SEC_VAR_CLEARED_8
		//define memory aligenment function to 8 bits 
	#undef OS_STOP_SEC_VAR_CLEARED_8
	#define STOP_SECTION_DATA_CLEARED_8
 
 #elif	OS_STOP_SEC_VAR_CLEARED_16
		//define memory aligenment function to 16 bits  
		#undef OS_STOP_SEC_VAR_CLEARED_16
		#define STOP_SECTION_DATA_CLEARED_16
		
 #elif	OS_STOP_SEC_VAR_CLEARED_32
		//define memory aligenment function to 32 bits  
		#undef OS_STOP_SEC_VAR_CLEARED_32
		#define STOP_SECTION_DATA_CLEARED_32
		
#elif	OS_STOP_SEC_VAR_CLEARED_64
		//define memory aligenment function to 64 bits  
		#undef OS_STOP_SEC_VAR_CLEARED_64
		#define STOP_SECTION_DATA_CLEARED_64
 #endif
/*****************************************/
 /*Constant-Aligenment*/
	/*Start*/
 #ifdef OS_START_SEC_CONST_8
		//define memory aligenment function to 8 bits 
	#undef OS_START_SEC_CONST_8
	#define START_SECTION_DATA_CONST_8
 
 #elif	OS_START_SEC_CONST_16
		//define memory aligenment function to 16 bits  
		#undef OS_START_SEC_CONST_16
		#define START_SECTION_DATA_CONST_16
		
 #elif	OS_START_SEC_CONST_32
		//define memory aligenment function to 32 bits  
		#undef OS_START_SEC_CONST_32
		#define START_SECTION_DATA_CONST_32
		
#elif	OS_START_SEC_CONST_64
		//define memory aligenment function to 64 bits  
		#undef OS_START_SEC_CONST_64
		#define START_SECTION_DATA_CONST_64
 #endif
 	/*Stop*/
 #ifdef OS_STOP_SEC_CONST_8
		//define memory aligenment function to 8 bits 
	#undef OS_STOP_SEC_CONST_8
	#define STOP_SECTION_DATA_CONST_8
 
 #elif	OS_STOP_SEC_CONST_16
		//define memory aligenment function to 16 bits  
		#undef OS_STOP_SEC_CONST_16
		#define STOP_SECTION_DATA_CONST_16
		
 #elif	OS_STOP_SEC_CONST_32
		//define memory aligenment function to 32 bits  
		#undef OS_STOP_SEC_CONST_32
		#define STOP_SECTION_DATA_CONST_32
		
#elif	OS_STOP_SEC_CONST_64
		//define memory aligenment function to 64 bits  
		#undef OS_STOP_SEC_CONST_64
		#define STOP_SECTION_DATA_CONST_64
 #endif
/*****************************************/
		/**********************Code Section**********************/
		
/*CODE SECTION DECLARATION*/
	/*Start*/
 #ifdef OS_START_SEC_CODE_LOCAL
		//DEFINE MEMORY SECTION AS CODE 
	#undef OS_START_SEC_CODE_LOCAL
	#define START_SEC_CODE_LOCAL
 #endif
	/*Stop*/
 #ifdef OS_STOP_SEC_CODE_LOCAL
		//END THE CODE MEMORY SECTION 
	#undef OS_STOP_SEC_CODE_LOCAL
	#define STOP_START_SEC_CODE_LOCAL

 #endif
/*****************************************/
/**************************************************************************************/
		/**********************Data Section**********************/

/*Assigen pragmas as defined function*/ 
/*Init-Aligenment*/
	/*Start*/
#ifdef START_SECTION_DATA_INIT_8

#pragma arm section  rwdata="RW_Section_8bit"	//Initialized section named RW_Section_8bit  
#pragma pack(1)		//Assigen the aligenment as 1 byte => 8bit
#undef START_SECTION_DATA_INIT_8
#undef MEMMAP_ERROR

#elif	 START_SECTION_DATA_INIT_16

#pragma arm section  rwdata="RW_Section_16bit"	//Initialized section named RW_Section_16bit  
#pragma pack(2)		//Assigen the aligenment as 2 byte => 16bit
#undef START_SECTION_DATA_INIT_16
#undef MEMMAP_ERROR

#elif	 START_SECTION_DATA_INIT_32

#pragma arm section  rwdata="RW_Section_32bit"	//Initialized section named RW_Section_32bit  
#pragma pack(4)		//Assigen the aligenment as 4 byte => 32bit
#undef START_SECTION_DATA_INIT_32
#undef MEMMAP_ERROR

#elif	 START_SECTION_DATA_INIT_64

#pragma arm section  rwdata="RW_Section_64bit"	//Initialized section named RW_Section_64bit  
#pragma pack(8)		//Assigen the aligenment as 8 byte => 64bit
#undef START_SECTION_DATA_INIT_64
#undef MEMMAP_ERROR

#endif
	/*Stop*/
#ifdef STOP_SECTION_DATA_INIT_8

#pragma arm section 	//Default 
#pragma pack(8)			//Default 
#undef STOP_SECTION_DATA_INIT_8
#undef MEMMAP_ERROR

#elif	 STOP_SECTION_DATA_INIT_16

#pragma arm section  //Default section  
#pragma pack(8)		//Default aligenment 
#undef STOP_SECTION_DATA_INIT_16
#undef MEMMAP_ERROR

#elif	 STOP_SECTION_DATA_INIT_32

#pragma arm section   //Default section    
#pragma pack(8)		 //Default aligenment
#undef STOP_SECTION_DATA_INIT_32
#undef MEMMAP_ERROR

#elif	 STOP_SECTION_DATA_INIT_64

#pragma arm section  //Default section  
#pragma pack(8)		//Default aligenment
#undef STOP_SECTION_DATA_INIT_64
#undef MEMMAP_ERROR

#endif
/********************************/
/*Non_Init-Aligenment*/
	/*Start*/
#ifdef START_SECTION_DATA_NO_INIT_8

#pragma arm section  zidata="NI_Section_8bit"	//non Initialized section named NI_Section_8bit  
#pragma pack(1)		//Assigen the aligenment as 1 byte => 8bit
#undef START_SECTION_DATA_NO_INIT_8
#undef MEMMAP_ERROR

#elif	 START_SECTION_DATA_NO_INIT_16

#pragma arm section  zidata="NI_Section_16bit"	//non Initialized section named NI_Section_16bit  
#pragma pack(2)		//Assigen the aligenment as 2 byte => 16bit
#undef START_SECTION_DATA_NO_INIT_16
#undef MEMMAP_ERROR

#elif	 START_SECTION_DATA_NO_INIT_32

#pragma arm section  zidata="NI_Section_32bit"	//non Initialized section named NI_Section_32bit  
#pragma pack(4)		//Assigen the aligenment as 4 byte => 32bit
#undef START_SECTION_DATA_NO_INIT_32
#undef MEMMAP_ERROR

#elif	 START_SECTION_DATA_NO_INIT_64

#pragma arm section  zidata="NI_Section_64bit"	//non Initialized section named NI_Section_64bit  
#pragma pack(8)		//Assigen the aligenment as 8 byte => 64bit
#undef START_SECTION_DATA_NO_INIT_64
#undef MEMMAP_ERROR

#endif
	/*Stop*/
#ifdef STOP_SECTION_DATA_NO_INIT_8

#pragma arm section 	 //Default section  
#pragma pack(8)		    //Default aligenment
#undef STOP_SECTION_DATA_NO_INIT_8
#undef MEMMAP_ERROR

#elif	 STOP_SECTION_DATA_NO_INIT_16

#pragma arm section  	 //Default section  
#pragma pack(8)		    //Default aligenment
#undef STOP_SECTION_DATA_NO_INIT_16
#undef MEMMAP_ERROR

#elif	 STOP_SECTION_DATA_NO_INIT_32

#pragma arm section 	 //Default section  
#pragma pack(8)		    //Default aligenment
#undef START_SECTION_DATA_NO_INIT_32
#undef MEMMAP_ERROR

#elif	 STOP_SECTION_DATA_NO_INIT_64

#pragma arm section  	 //Default section  
#pragma pack(8)		    //Default aligenment
#undef STOP_SECTION_DATA_NO_INIT_64
#undef MEMMAP_ERROR

#endif
/********************************/
/*Cleared-Aligenment*/
	/*Start*/
#ifdef START_SECTION_DATA_CLEARED_8

#pragma arm section  zidata="ZI_Section_8bit"	//Zero Initialized section named ZI_Section_8bit  
#pragma pack(1)		//Assigen the aligenment as 1 byte => 8bit
#undef START_SECTION_DATA_CLEARED_8
#undef MEMMAP_ERROR

#elif	 START_SECTION_DATA_CLEARED_16

#pragma arm section  zidata="ZI_Section_16bit"	//Zero Initialized section named ZI_Section_16bit  
#pragma pack(2)		//Assigen the aligenment as 2 byte => 16bit
#undef START_SECTION_DATA_CLEARED_16
#undef MEMMAP_ERROR

#elif	 START_SECTION_DATA_CLEARED_32

#pragma arm section  zidata="ZI_Section_32bit"	//Zero Initialized section named ZI_Section_32bit  
#pragma pack(4)		//Assigen the aligenment as 4 byte => 32bit
#undef START_SECTION_DATA_CLEARED_32
#undef MEMMAP_ERROR

#elif	 START_SECTION_DATA_CLEARED_64

#pragma arm section  zidata="ZI_Section_64bit"	//Zero Initialized section named ZI_Section_64bit  
#pragma pack(8)		//Assigen the aligenment as 8 byte => 64bit
#undef START_SECTION_DATA_CLEARED_64
#undef MEMMAP_ERROR

#endif
	/*Stop*/
#ifdef STOP_SECTION_DATA_CLEARED_8

#pragma arm section 		 //Default section    
#pragma pack(8)		       //Default aligenment
#undef STOP_SECTION_DATA_CLEARED_8
#undef MEMMAP_ERROR

#elif	 STOP_SECTION_DATA_CLEARED_16

#pragma arm section 	 //Default section  
#pragma pack(8)		   //Default aligenment
#undef STOP_SECTION_DATA_CLEARED_16
#undef MEMMAP_ERROR

#elif	 STOP_SECTION_DATA_CLEARED_32

#pragma arm section 	 //Default section    
#pragma pack(8)		   //Default aligenment
#undef STOP_SECTION_DATA_CLEARED_32
#undef MEMMAP_ERROR

#elif	 STOP_SECTION_DATA_CLEARED_64

#pragma arm section 	 //Default section  
#pragma pack(8)		   //Default aligenment
#undef STOP_SECTION_DATA_CLEARED_64
#undef MEMMAP_ERROR

#endif
/********************************/
/*Constant-Aligenment*/
	/*Start*/
#ifdef START_SECTION_DATA_CONST_8

#pragma arm section  rodata="RO_Section_8bit"	//Read only section named RO_Section_8bit
#pragma pack(1)		//Assigen the aligenment as 1 byte => 8bit
#undef START_SECTION_DATA_CONST_8
#undef MEMMAP_ERROR

#elif	 START_SECTION_DATA_CONST_16

#pragma arm section  rodata="RO_Section_16bit"	//Read only section named RO_Section_16bit
#pragma pack(2)		//Assigen the aligenment as 2 byte => 16bit
#undef START_SECTION_DATA_CONST_16
#undef MEMMAP_ERROR

#elif	 START_SECTION_DATA_CONST_32

#pragma arm section  rodata="RO_Section_32bit"	//Read only section named RO_Section_32bit
#pragma pack(4)		//Assigen the aligenment as 4 byte => 32bit
#undef START_SECTION_DATA_CONST_32
#undef MEMMAP_ERROR

#elif	 START_SECTION_DATA_CONST_64

#pragma arm section  rodata="RO_Section_64bit"	//Read only section named RO_Section_64bit
#pragma pack(8)		//Assigen the aligenment as 8 byte => 64bit
#undef START_SECTION_DATA_CONST_64
#undef MEMMAP_ERROR

#endif
	/*Stop*/
#ifdef STOP_SECTION_DATA_CONST_8

#pragma arm section  	 //Default section   
#pragma pack(8)		   //Default aligenment
#undef STOP_SECTION_DATA_CONST_8
#undef MEMMAP_ERROR

#elif	 STOP_SECTION_DATA_CONST_16

#pragma arm section  	 //Default section   
#pragma pack(8)		   //Default aligenment
#undef STOP_SECTION_DATA_CONST_16
#undef MEMMAP_ERROR

#elif	 STOP_SECTION_DATA_CONST_32

#pragma arm section  	 //Default section   
#pragma pack(8)		   //Default aligenment
#undef STOP_SECTION_DATA_CONST_32
#undef MEMMAP_ERROR

#elif	 STOP_SECTION_DATA_CONST_64

#pragma arm section  	 //Default section   
#pragma pack(8)		   //Default aligenment
#undef STOP_SECTION_DATA_CONST_64
#undef MEMMAP_ERROR

#endif
/********************************/
		/**********************Code Section**********************/
	/*Start*/
#ifdef START_SEC_CODE_LOCAL

#pragma arm section  code="Code_Section"	//define a code section  
#undef START_SEC_CODE_LOCAL
#undef MEMMAP_ERROR

#endif
	/*Stop*/
#ifdef STOP_START_SEC_CODE_LOCAL

#pragma arm section 	 //Default section  
#undef STOP_START_SEC_CODE_LOCAL
#undef MEMMAP_ERROR

#endif
/********************************/
