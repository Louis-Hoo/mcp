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

#ifndef _LIST_H
#define _LIST_H

#ifdef __cplusplus 
extern "C" {
#endif 


/******************************************************************************
*
* Code Segment: Macro define
*
*******************************************************************************/
#define LIST_EMPTY				0
#define LIST_NOT_EMPTY			1

#define LIST_CMPDATA_EQUAL		0
#define LIST_CMPDATA_NO_EQUAL	1
/******************************************************************************
*
* Code Segment: typedef
*
*******************************************************************************/
typedef struct tag_node
{
	void *pData;
	struct tag_node *pnext;
}node;

typedef UINT32 (* PFUNC_CompareData)(const void *pListData, const void *pSearchData);

typedef void (* PFUNC_DisplayData)(UINT32 u32NodeIndex, void *pElementData);

typedef void (* PFUNC_FREE)(void *pMem);

typedef void * (*PFUNC_MALLOC)(UINT32 u32Len);
/******************************************************************************
*
* Code Segment: function declare
*
*******************************************************************************/
node *List_Init(void);

UINT32 List_InsertToTail(node *pHead, void *pElementData, PFUNC_MALLOC pfMalloc);

UINT32 List_InsertToHead(node *pHead, void *pElementData, PFUNC_MALLOC pfMalloc);

UINT32 List_DeleteFromTail(node *pHead, PFUNC_FREE pfFree);

UINT32 List_DeleteFromHead(node *pHead, PFUNC_FREE pfFree);

void *List_SearchData(node *pHead, const void *pSearchData, PFUNC_CompareData pfCmpData);

UINT32 List_Display(node *pHead, PFUNC_DisplayData pfDisplay);

UINT32 List_IsEmpty(node *pHead);

UINT32 List_GetLength(node *pHead);

node *List_Reverse(node *pHead);

#ifdef __cplusplus
}
#endif

#endif

