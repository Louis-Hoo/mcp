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

#ifndef _COMMENT_H
#define _COMMENT_H

#ifdef __cplusplus 
extern "C" {
#endif 

/******************************************************************************
*
* Code Segment: Macro define
*
*******************************************************************************/


/******************************************************************************
*
* Code Segment: typedef
*
*******************************************************************************/
typedef struct tag_MPBlockInfo
{
	UINT32 u32BlockSize;
	UINT32 u32BlockNum;
}MPBlockInfo;

/******************************************************************************
*
* Code Segment: function declare
*
*******************************************************************************/
UINT32 MP_Init(MPBlockInfo *pMPBlockInfo, UINT32 u32Item);

void *MP_Malloc(UINT8 u8MemLen);

void MP_Free(void *pMem);

#ifdef __cplusplus
}
#endif

#endif

