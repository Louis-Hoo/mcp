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

#ifndef _REG_H
#define _REG_H

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
typedef struct tag_REG_CHECK
{
	UINT32 u32BaseAddr;
	UINT32 u32Offset;
	UINT32 u32WriteValue;
	UINT32 u32ReadValue;
}REG_CHECK;

/******************************************************************************
*
* Code Segment: function declare
*
*******************************************************************************/
UINT32 REG_Read(UINT32 u32BaseAddr, UINT32 u32AddrOffset);

void REG_Write(UINT32 u32BaseAddr, UINT32 u32AddrOffset, UINT32 u32WRData);

UINT32 REG_Check(REG_CHECK *pRegList, UINT32 u32ItemNum);

#endif

