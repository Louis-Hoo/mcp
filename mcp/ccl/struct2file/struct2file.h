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

#ifndef _STRUCT2FILE_H
#define _STRUCT2FILE_H

/******************************************************************************
*
* Code Segment: Macro define
*
*******************************************************************************/
#define STRUCT2FILE_FILE_NAME_LENGTH		64
#define STRUCT2FILE_STRUCT_NAME_LENGTH		64


#define STRU2FILE_INIT(pu8FileName, StructName)\
	STRU2FILE_Init(pu8FileName, #StructName, sizeof(StructName))

/* Write U8 data type API	*/
#define STRU2FILE_WRITE_U8(StructName, MemberName, Value)\
	*(UINT8 *)((UINT8 *)STRU2FILE_GetStructAddr(#StructName) + OFFSET_OF(StructName, MemberName)) = Value;\
	msync(STRU2FILE_GetStructAddr(#StructName), sizeof(StructName), MS_ASYNC);

/* Write U16 data type API	*/
#define STRU2FILE_WRITE_U16(StructName, MemberName, Value)\
	*(UINT16 *)((UINT16 *)STRU2FILE_GetStructAddr(#StructName) + OFFSET_OF(StructName, MemberName)) = Value;\
	msync(STRU2FILE_GetStructAddr(#StructName), sizeof(StructName), MS_ASYNC);

/* Write U32 data type API	*/
#define STRU2FILE_WRITE_U32(StructName, MemberName, Value)\
	*(UINT32 *)((UINT32 *)STRU2FILE_GetStructAddr(#StructName) + OFFSET_OF(StructName, MemberName)) = Value;\
	msync(STRU2FILE_GetStructAddr(#StructName), sizeof(StructName), MS_ASYNC);

/* Write string data type API	*/
#define STRU2FILE_WRITE_STRING(StructName, MemberName, Value)\
	memcpy((void *)((UINT8 *)STRU2FILE_GetStructAddr(#StructName) + OFFSET_OF(StructName, MemberName)),\
			(void *)Value,\
			sizeof(Value));\
	msync(STRU2FILE_GetStructAddr(#StructName), sizeof(StructName), MS_ASYNC);

/* Write Whole Struct API	*/
#define STRU2FILE_WRITE_WHOLE_STRUCT(StructName, StructValue)\
	*((StructName *)STRU2FILE_GetStructAddr(#StructName)) = StructValue;\
	msync(STRU2FILE_GetStructAddr(#StructName), sizeof(StructName), MS_ASYNC);

/* Read U8 data type API	*/
#define STRU2FILE_READ_U8(StructName, MemberName)\
	*(UINT8 *)((UINT8 *)STRU2FILE_GetStructAddr(#StructName) + OFFSET_OF(StructName, MemberName))

/* Read U16 data type API	*/
#define STRU2FILE_READ_U16(StructName, MemberName)\
	*(UINT16 *)((UINT16 *)STRU2FILE_GetStructAddr(#StructName) + OFFSET_OF(StructName, MemberName))

/* Read U32 data type API	*/
#define STRU2FILE_READ_U32(StructName, MemberName)\
	*(UINT32 *)((UINT32 *)STRU2FILE_GetStructAddr(#StructName) + OFFSET_OF(StructName, MemberName))

/* Read string data type API	*/
#define STRU2FILE_READ_STRING(StructName, MemberName)\
	(void *)((UINT8 *)STRU2FILE_GetStructAddr(#StructName) + OFFSET_OF(StructName, MemberName))

/* Read Whole Struct API	*/
#define STRU2FILE_READ_WHOLE_STRUCT(StructName, MemberName)\
	*((StructName *)STRU2FILE_GetStructAddr(#StructName))

/******************************************************************************
*
* Code Segment: typedef
*
*******************************************************************************/
typedef struct tag_STRU2FILE
{
	void *pStructMapAddr;
	UINT8 u8FileName[STRUCT2FILE_FILE_NAME_LENGTH];
	UINT8 u8StructName[STRUCT2FILE_STRUCT_NAME_LENGTH];
}Stru2FileInfo;

/******************************************************************************
*
* Code Segment: function declare
*
*******************************************************************************/
UINT32 STRU2FILE_Init(const UINT8 *pu8FileName, const UINT8 *pu8StruName, UINT32 u32StruLen);

void *STRU2FILE_GetStructAddr(const UINT8 *pu8StructName);

#endif

