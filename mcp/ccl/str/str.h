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

#ifndef _STR_H
#define _STR_H

#ifdef __cplusplus 
extern "C" {
#endif 

/******************************************************************************
*
* Code Segment: Macro define
*
*******************************************************************************/
#define STR_FILE_IS_EXIST			0
#define STR_FILE_NO_EXIST			1

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
UINT32 STR_StrToNum(const UINT8 *pu8Str);

UINT8 *STR_NumToStr(UINT32 num, UINT8 des[]);

UINT32 STR_HexToDec(const UINT8 *hex);

void STR_DecToHex(UINT32 dec, UINT32 len, UINT8 s[]);

void STR_DecToBin(UINT32 u32Dec, UINT32 u32Len, UINT8 u8Bin[]);

UINT32 STR_FileIsExist(const UINT8 *pFilePath);

void STR_DelBlank(UINT8 u8Str[]);

UINT8 *STR_Reverse(UINT8 str[]);

UINT32 STR_CharPos(UINT8 *pStr, UINT8 u8Ch);

UINT8 *STR_MaxPubSubStr(const UINT8 *str1, const UINT8 *str2, UINT8 maxstr[]);

UINT8 *STR_MaxSubStr(const UINT8 *str, UINT8 s[]);

void STR_NCat(UINT8 *des, const UINT8 *src, int n);

UINT8 *STR_Cpy(UINT8 *des, const UINT8 *src);

UINT32 STR_NCmp(const UINT8 *des, const UINT8 *src, UINT32 len);

UINT32 STR_Len(const UINT8 *pch);

UINT8 *STR_NCpy(UINT8 *dest, const UINT8 *source, UINT32 count);

UINT8 *STR_ShrinkSpace(UINT8 *dest, const UINT8 *src, UINT32 len);

void STR_DeleteChar(UINT8 *str, UINT8 ch);

void STR_ShiftRight(UINT8 *src, UINT32 k);

#ifdef __cplusplus
}
#endif

#endif

