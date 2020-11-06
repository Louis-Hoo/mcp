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
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include "common.h"
#include "mempool.h"
#include "list.h"
#include "struct2file.h"
/******************************************************************************
*
* Code Segment: global var
*
*******************************************************************************/
static node *g_pStru2FileList = NULL;

/******************************************************************************
*
* Code Segment: static function declare
*
*******************************************************************************/
static UINT32 CmpStructName(const void *pListData, const void *pSearchData);

/******************************************************************************
*
* Code Segment: function body
*
*******************************************************************************/
/******************************************************************************
*
* @brief	:
* @param in 	:
* @param out	:
* @return	:
* @note 	:
********************************************************************************/
UINT32 STRU2FILE_Init(const UINT8 *pu8FileName, const UINT8 *pu8StruName, UINT32 u32StruLen)
{
	INT32 fd = 0;
	Stru2FileInfo *pStru2File = NULL;
	UINT32 u32RetErr = ERR_SUCCESS;

	JUDGE_POINTER_RET_U32(pu8FileName, ERR_SYSTEM_MEMRY_POINTER_NULL, "File Name Is NULL\n");
	JUDGE_POINTER_RET_U32(pu8StruName, ERR_SYSTEM_MEMRY_POINTER_NULL, "Struct Name Is NULL\n");

	fd = open((INT8 *)pu8FileName, O_RDWR | O_CREAT, 0777);
	if (-1 == fd)
	{
		perror("File Error:");
		printf("Open File:%s Failed, Errno:%d\n", pu8FileName, errno);

		return ERR_FILE_OPEN_FAILED;
	}

	if (-1 == ftruncate(fd, u32StruLen))
	{
		perror("ftruncate");

		return ERR_FILE_TRUNCATE_FAILED;
	}

	if (NULL == g_pStru2FileList)
	{
		g_pStru2FileList = List_Init();
		JUDGE_POINTER_RET_U32(g_pStru2FileList, ERR_SYSTEM_MEMRY_POINTER_NULL, "List Init Fialed.\n");
	}

	pStru2File = (Stru2FileInfo *)MP_Malloc(sizeof(Stru2FileInfo));
	JUDGE_POINTER_RET_U32(pStru2File, ERR_SYSTEM_MEMORY_ALLOC_FAILED, "Malloc Fialed\n");

	pStru2File->pStructMapAddr = mmap(NULL,
									  u32StruLen,
									  PROT_READ | PROT_WRITE,
									  MAP_SHARED,
									  fd,
									  0);
	JUDGE_POINTER_RET_U32(pStru2File->pStructMapAddr, ERR_SYSTEM_MEMRY_POINTER_NULL, "MMap NULL.\n");

	memcpy(pStru2File->u8FileName, pu8StruName, strlen((INT8 *)pu8StruName));
	memcpy(pStru2File->u8FileName, pu8FileName, strlen((INT8 *)pu8FileName));

	u32RetErr = List_InsertToTail(g_pStru2FileList, pStru2File, NULL);
	JUDGE_U32_RET_U32(u32RetErr,u32RetErr , "Insert List Failed.\n");

	return u32RetErr;
}

/******************************************************************************
*
* @brief	:
* @param in 	:
* @param out	:
* @return	:
* @note 	:
********************************************************************************/
void *STRU2FILE_GetStructAddr(const UINT8 *pu8StructName)
{
	return List_SearchData(g_pStru2FileList, pu8StructName, CmpStructName);
}

/******************************************************************************
*
* @brief	:
* @param in 	:
* @param out	:
* @return	:
* @note 	:
********************************************************************************/
static UINT32 CmpStructName(const void *pListData, const void *pSearchData)
{
	const Stru2FileInfo *pStru2File = NULL;

	JUDGE_POINTER_RET_U32(pListData, ERR_SYSTEM_MEMRY_POINTER_NULL, "List Data NULL\n");
	JUDGE_POINTER_RET_U32(pSearchData, ERR_SYSTEM_MEMRY_POINTER_NULL, "pSearchData NULL\n");

	pStru2File = pListData;

	if (strcmp((INT8 *)pStru2File->u8StructName, (INT8 *)pSearchData) == 0)
	{
		return LIST_CMPDATA_EQUAL;
	}
	else
	{
		return LIST_CMPDATA_NO_EQUAL;
	}
}

