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
#include <gtest/gtest.h>

#include "common.h"
#include "str.h"

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
TEST(STR, STR_StrToNum)
{
	const UINT8 *pString1 = (const UINT8 *)"aAdE15";
	const UINT8 *pString2 = (const UINT8 *)"0xaAdE15";
	const UINT8 *pString3 = (const UINT8 *)"0XaAdE15";
	const UINT8 *pString4 = (const UINT8 *)"0eaAdE15";
	UINT32 u32Result = 0;

	u32Result = STR_StrToNum(pString1);
	EXPECT_EQ(u32Result, 11197973);

	u32Result = STR_StrToNum(pString2);
	EXPECT_EQ(u32Result, 11197973);

	u32Result = STR_StrToNum(pString3);
	EXPECT_EQ(u32Result, 11197973);

	u32Result = STR_StrToNum(pString4);
	EXPECT_EQ(u32Result, 0);
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:
********************************************************************************/
TEST(STR, STR_NumToStr)
{
	UINT32 u32Num1 = 1024;
	UINT8 *pu8Num1 = (UINT8 *)"1024";

	UINT32 u32Num2 = 2048;
	UINT8 *pu8Num2 = (UINT8 *)"20489";
	
	UINT8 u8Str[32];
	UINT32 u32StrCmp = 0;

	STR_NumToStr(u32Num1, u8Str);

	u32StrCmp = strcmp((INT8 *)pu8Num1, (INT8 *)u8Str);
	EXPECT_EQ(u32StrCmp, 0);

	STR_NumToStr(u32Num2, u8Str);

	u32StrCmp = strcmp((INT8 *)pu8Num2, (INT8 *)u8Str);
	EXPECT_NE(u32StrCmp, 0);
}

