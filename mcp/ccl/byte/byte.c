/******************************************************************************
*
* Copyright (C) Louis.hoo
* All Rights Reserved. Confidential
*
*******************************************************************************
*
* Project: <MCP>
* Subproject: <sw module>
* File Name: <>
* Author: <Louis.hoo>
* Creation Date: <>
* Revision: <V0.1>
* Last modified by: <>
*
*******************************************************************************/

/******************************************************************************
*
* Code Segment: include
*
*******************************************************************************/
#include <stdio.h>

#include "common.h"
#include "byte.h"

/******************************************************************************
*
* Code Segment: global var
*
*******************************************************************************/


/******************************************************************************
*
* Code Segment: static function declare
*
*******************************************************************************/


/******************************************************************************
*
* Code Segment: function body
*
*******************************************************************************/

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:
********************************************************************************/
void BYTE_Print(const void *pFrame, UINT32 u32Length)
{
	UINT32 u32Loop = 0;
	UINT8 *pByte = (UINT8 *)pFrame;

	JUDGE_POINTER_RET_VOID(pFrame, "Point Is NULL\n");

	printf("\r\n------------------------------------------------------------\r\n");
	printf("Addr      0--3    \t4--7    \t8--11    \t12--15");
	printf("\r\n------------------------------------------------------------\r\n");

	for (u32Loop = 0; u32Loop < u32Length; u32Loop++)
	{
		if ((u32Loop % 16 == 0) && u32Loop != 0)
		{
			printf("\r\n");
		}

		if ((u32Loop % 4 == 0) && (u32Loop != 0) && (u32Loop % 16 !=0))
		{
			printf("\r\n");
		}

		if (u32Loop % 16 == 0)
		{
			printf("%08X:", (UINT32)((ULONG)pByte + u32Loop));
		}

		printf("%02X", *(pByte + u32Loop));
	}

	printf("\r\n============================================================\r\n\r\n");

	return;
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:
********************************************************************************/
UINT32 BYTE_OrderType(void)
{
	UINT32 u32Num = 1;

	if (*(UINT8 *)&u32Num == 0)
	{
		return BYTE_ORDER_LITTLEEDIAN;
	}

	return BYTE_ORDER_BIGEDIAN;
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:
********************************************************************************/
UINT32 BYTE_RightShift(UINT32 a, UINT32 n)
{
	int b,c;

	b = (~(~0 << n) & a) << (32 - n);
	a >>= n;
	a &= ~((~0) << (32 - n));
	c = a | b;

	return c;
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:
********************************************************************************/
UINT32 BYTE_LeftShift(UINT32 a, UINT32 n)
{
	int b,c;

	b = a >> (32 - n);
	b = b & ~(~0 << n);
	a = a << n;
	c = a | b;

	return c;
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:
********************************************************************************/
UINT32 BYTE_IsPower2(UINT32 a)
{
	if ((a & (a - 1)) == 0)
	{
		return BYTE_POWER2_IS;
	}

	return BYTE_POWER2_NO;
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:
********************************************************************************/
UINT32 BYTE_CountBit1(UINT32 x)
{
	UINT32 u32Count = 0;
	UINT32 u32Pos = 0;

	while ((x & u32Pos) != 0) 
	{
		u32Pos <<= 1;
		u32Count++;
	}

	return u32Count;
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:
********************************************************************************/
UINT32 BYTE_LeftShiftLoop(UINT32 num, UINT32 n)
{
	ULONG a,b,c,d;
	
	a = (~0) << (32 - n) & num;
	b = a >> (32 - n);
	c = b & (~((~0) << n));
	d = num << n;

	return (c | d);
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:
********************************************************************************/
void *BYTE_MemMove_(void *pdest, const void *psource, ULONG count)
{
	UINT8 *dest = (UINT8 *)pdest;
	const UINT8 *source = (const UINT8 *)psource;
	UINT8 *ret = dest;
	
    if (dest <= source || dest >= (source + count))
    {
    	//Non-Overlapping Buffers
    	//copy from lower addresses to higher addresses
        while (count --)
    	{
        	*dest++ = *source++;
    	}
    }
    else
    {
	     //Overlapping Buffers
    	 //copy from higher addresses to lower addresses
	     dest += count - 1;
	     source += count - 1;
       	 while (count--)
       	 {
 	        *dest-- = *source--;
       	 }
    }
    
    return (void *)ret;
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:
********************************************************************************/
UINT32 BYTE_IsSpace(UINT8 u8Ch)
{
	if (u8Ch == ' ')
	{
		return BYTE_SPACE_IS;
	}

	return BYTE_SPACE_NO;
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:
********************************************************************************/
UINT32 BYTE_IsDigit(UINT8 u8Ch)
{
	if ((u8Ch >= '0' ) && (u8Ch <= '9' ))
	{
		return BYTE_DIGIT_IS;
	}

	return BYTE_DIGIT_NO;
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:
********************************************************************************/
UINT32 BYTE_Factorial(UINT32 n)
{
	if (n <= 1)
	{
		return 1;
	}
	else
	{
		return BYTE_Factorial(n - 1) * n;
	}
}