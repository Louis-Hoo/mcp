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
#include "mempool.h"
#include "list.h"

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
node *List_Init(void)
{
	node *head = (node *)MP_Malloc(sizeof(node));

	head->pData = NULL;
	head->pnext = NULL;

	return head;
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:
********************************************************************************/
UINT32 List_InsertToTail(node *pHead, void *pElementData, PFUNC_MALLOC pfMalloc)
{
	node *pCursor = pHead;
	node *pNewNode = NULL;
	UINT32 u32RetErr = ERR_SUCCESS;

	JUDGE_POINTER_RET_U32(pHead, ERR_SYSTEM_MEMRY_POINTER_NULL, "Point is NULL\n");

	while (NULL != pCursor->pnext)
	{
		pCursor = pCursor->pnext;
	}

	if (NULL == pfMalloc)
	{
		pNewNode = (node *)MP_Malloc(sizeof(node));
	}
	else
	{
		pNewNode = (node *)pfMalloc(sizeof(node));
	}
	
	JUDGE_POINTER_RET_U32(pNewNode, ERR_SYSTEM_MEMORY_ALLOC_FAILED, "Malloc Failed\n");

	pNewNode->pData = pElementData;
	pNewNode->pnext = NULL;
	pCursor->pnext = pNewNode;

	return u32RetErr;
}

/******************************************************************************
*
* @brief	:
* @param in	:	
* @param out:
* @return 	:
* @note		:
********************************************************************************/
UINT32 List_InsertToHead(node *pHead, void *pElementData, PFUNC_MALLOC pfMalloc)
{
	node *pCursor = pHead;
	node *pNewNode = NULL;
	UINT32 u32RetErr = ERR_SUCCESS;

	JUDGE_POINTER_RET_U32(pHead, ERR_SYSTEM_MEMRY_POINTER_NULL, "Point is NULL\n");

	pCursor = pHead->pnext;

	if (NULL == pfMalloc)
	{
		pNewNode = (node *)MP_Malloc(sizeof(node));
	}
	else
	{
		pNewNode = (node *)pfMalloc(sizeof(node));
	}
	
	JUDGE_POINTER_RET_U32(pNewNode, ERR_SYSTEM_MEMORY_ALLOC_FAILED, "Malloc Failed\n");

	pNewNode->pData = pElementData;
	pHead->pnext = pNewNode;
	pNewNode->pnext = pCursor;

	return u32RetErr;
}

/******************************************************************************
*
* @brief	:
* @param in	:	
* @param out:
* @return 	:
* @note		:
********************************************************************************/
UINT32 List_DeleteFromTail(node *pHead, PFUNC_FREE pfFree)
{
	node *pCursor = pHead;
	UINT32 u32RetErr = ERR_SUCCESS;

	JUDGE_POINTER_RET_U32(pHead, ERR_SYSTEM_MEMRY_POINTER_NULL, "Point is NULL\n");

	if (NULL == pHead->pnext)
	{
		return ERR_SUCCESS;
	}
	
	while (NULL != pCursor->pnext->pnext)
	{
		pCursor = pCursor->pnext;
	}

	if (NULL == pfFree)
	{
		MP_Free(pCursor->pnext->pData);
		MP_Free(pCursor->pnext);
	}
	else
	{
		pfFree(pCursor->pnext->pData);
		pfFree(pCursor->pnext);
	}

	pCursor->pnext = NULL;
	
	return u32RetErr;
}

/******************************************************************************
*
* @brief	:
* @param in	:	
* @param out:
* @return 	:
* @note		:
********************************************************************************/
UINT32 List_DeleteFromHead(node *pHead, PFUNC_FREE pfFree)
{
	node *pCursor = pHead;
	UINT32 u32RetErr = ERR_SUCCESS;

	JUDGE_POINTER_RET_U32(pHead, ERR_SYSTEM_MEMRY_POINTER_NULL, "Point is NULL\n");

	pCursor = pCursor->pnext->pnext;

	if (NULL == pfFree)
	{
		MP_Free(pHead->pnext->pData);
		MP_Free(pHead->pnext);
	}
	else
	{
		pfFree(pHead->pnext->pData);
		pfFree(pHead->pnext);
	}

	pHead->pnext = pCursor;

	return u32RetErr;
}

/******************************************************************************
*
* @brief	:
* @param in	:	
* @param out:
* @return 	:
* @note		:
********************************************************************************/
void *List_SearchData(node *pHead, const void *pSearchData, PFUNC_CompareData pfCmpData)
{
	node *pCursor = pHead->pnext;

	JUDGE_POINTER_RET_NULL(pfCmpData, "Point is NULL\n");
	
	while (NULL != pCursor)
	{
		if (LIST_CMPDATA_EQUAL == pfCmpData(pCursor->pData, pSearchData))
		{
			return pCursor->pData;
		}
		
		pCursor = pCursor->pnext;
	}

	return NULL;
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:
********************************************************************************/
UINT32 List_Display(node *pHead, PFUNC_DisplayData pfDisplay)
{
	node *pCursor = pHead->pnext;
	UINT32 u32RetErr = ERR_SUCCESS;
	UINT32 u32Count = 0;

	JUDGE_POINTER_RET_U32(pHead, ERR_SYSTEM_MEMRY_POINTER_NULL, "Point is NULL\n");
	JUDGE_POINTER_RET_U32(pfDisplay, ERR_SYSTEM_MEMRY_POINTER_NULL, "Point is NULL\n");

	while (NULL != pCursor)
	{
		pfDisplay(u32Count, pCursor->pData);

		pCursor = pCursor->pnext;
		u32Count++;
	}
	
	return u32RetErr;
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:
********************************************************************************/
UINT32 List_IsEmpty(node *pHead)
{
	JUDGE_POINTER_RET_U32(pHead, ERR_SYSTEM_MEMRY_POINTER_NULL, "Point is NULL\n");

	if (NULL == pHead->pnext)
	{
		return LIST_EMPTY;
	}
	else
	{
		return LIST_NOT_EMPTY;
	}
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:
********************************************************************************/
UINT32 List_GetLength(node *pHead)
{
	UINT32 u32Count = 0;
	node *pCursor = NULL;

	pCursor = pHead->pnext;
	while (NULL != pCursor)
	{
		u32Count++;
		
		pCursor = pCursor->pnext;
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
node *List_Reverse(node *pHead)
{
	node *p = NULL;;
	node *r = NULL;

	JUDGE_POINTER_RET_NULL(pHead, "List Have NO Head.\n");
	JUDGE_POINTER_RET_NULL(pHead->pnext, "List Is Empty.\n");

	p = pHead->pnext;
	pHead->pnext = NULL;

	while (p != NULL)
	{
		r = p->pnext;
		p->pnext = pHead->pnext;
		pHead->pnext = p;
		p = r;
	}

	return pHead;
}

