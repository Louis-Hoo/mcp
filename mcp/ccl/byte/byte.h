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

#ifndef _BYTE_H
#define _BYTE_H

/******************************************************************************
*
* Code Segment: Macro define
*
*******************************************************************************/
#define BYTE_GET_BITS(num, m, n)	(((num) >> (n)) & (~(0xFFFFFFFF << (32 - (m) + (n)))))

#define BYTE_GET_BITN(num, n)		(((num) >> (n)) & 0x1)

#define BYTE_SET_BITN(num, n)		((a) | (1 << n))

#define BYTE4_REVERT(num)		  ((((num) & 0x000000FF) << 24)\
								  |(((num) & 0x0000FF00) << 8)	\
								  |(((num) & 0x00FF0000) >> 8)	\
								  |(((num) & 0xFF000000) >> 24))

#define BYTE3_REVERT(num)		  ((((num) & 0x00FF0000) >> 16)\
								   |(((num) & 0x000000FF) << 16)\
								   |(((num) & 0x0000FF00)))

#define BYTE2_REVERT(num)		  ((((num) & 0x0000FF00) >> 8)\
								   |(((num) & 0x000000FF) << 8))
								  
#define OFFSET_OF(TYPE, MEMBER)	((unsigned long) &((TYPE *)0)->MEMBER)
#define CONTAINER_OF(ptr, type, member)	((type *)((INT8 *)ptr - OFFSET_OF(type, member)))
#define COUNTOF(array)	(sizeof(array) / sizeof(array[0]))


#define BYTE_ORDER_BIGEDIAN				0
#define BYTE_ORDER_LITTLEEDIAN			1

#define BYTE_POWER2_NO					0
#define BYTE_POWER2_IS					1

#define BYTE_SPACE_IS					0
#define BYTE_SPACE_NO					1

#define BYTE_DIGIT_IS					0
#define BYTE_DIGIT_NO					1

/******************************************************************************
*
* Code Segment: typedef
*
*******************************************************************************/



/******************************************************************************
*
* Code Segment: function declare
*
*******************************************************************************/
void BYTE_Print(const void *pFrame, UINT32 u32Length);

UINT32 BYTE_OrderType(void);

UINT32 BYTE_RightShift(UINT32 a, UINT32 node);

UINT32 BYTE_LeftShift(UINT32 a, UINT32 n);

UINT32 BYTE_IsPower2(UINT32 a);

UINT32 BYTE_CountBit1(UINT32 x);

UINT32 BYTE_LeftShiftLoop(UINT32 num, UINT32 n);

void *BYTE_MemMove_(void *pdest, const void *psource, ULONG count);

UINT32 BYTE_IsSpace(UINT8 ch);

UINT32 BYTE_IsDigit(UINT8 u8Ch);

UINT32 BYTE_Factorial(UINT32 n);

#endif

