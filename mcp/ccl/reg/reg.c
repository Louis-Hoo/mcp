/******************************************************************************
*
* Copyright (C) Louis.hoo
* All Rights Reserved. Confidential
*
*******************************************************************************
*
* Project: <CMP>
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
#include "reg.h"

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
UINT32 REG_Read(UINT32 u32BaseAddr, UINT32 u32AddrOffset)
{
	UINT32 u32RDData;

	u32RDData = *((UINT32 *)(ULONG)(u32BaseAddr + u32AddrOffset));

	return u32RDData;
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:
********************************************************************************/
void REG_Write(UINT32 u32BaseAddr, UINT32 u32AddrOffset, UINT32 u32WRData)
{
	*((UINT32 *)(ULONG)(u32BaseAddr + u32AddrOffset)) = u32WRData;

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
UINT32 REG_Check(REG_CHECK *pRegList, UINT32 u32ItemNum)
{
	UINT32 u32Loop = 0;
	UINT32 u32RegCurValue = 0;
	UINT32 u32ErrCount = 0;

	printf("BaseAddr\t    Offset\t    WriteValue\t    ReadValue\t\r\n");
	printf("==============================================================\r\n");

	for (u32Loop = 0; u32Loop < u32ItemNum; u32Loop++)
	{
		REG_Write(pRegList[u32Loop].u32BaseAddr, pRegList[u32Loop].u32Offset, pRegList[u32Loop].u32WriteValue);
		u32RegCurValue = REG_Read(pRegList[u32Loop].u32BaseAddr, pRegList[u32Loop].u32Offset);

		if (pRegList[u32Loop].u32ReadValue != u32RegCurValue)
		{
			printf("%08X\t %04X\t %08X\t %08X\t\r\n",
				   (UINT32)pRegList[u32Loop].u32BaseAddr,
				   (UINT32)pRegList[u32Loop].u32Offset,
				   (UINT32)pRegList[u32Loop].u32WriteValue,
				   (UINT32)u32RegCurValue);
			
			u32ErrCount++;
		}
	}

	return u32ErrCount;
}

