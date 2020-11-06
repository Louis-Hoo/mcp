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
#include "list.h"
#include "mempool.h"

/******************************************************************************
*
* Code Segment: global var
*
*******************************************************************************/
static node *g_list = NULL;

static UINT32 g_ListLen = 31;


/******************************************************************************
*
* Code Segment: static function declare
*
*******************************************************************************/
static UINT32 UT_List_CmpData(const void *pListData, const void *pSearchData);

void UT_List_Display(UINT32 u32Index, void *pElementData);

/******************************************************************************
*
* Code Segment: function body
*
*******************************************************************************/

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out	:
* @return 	:
* @note		:
********************************************************************************/
TEST(list, init)
{
	UINT32 u32RetErr = ERR_SUCCESS;
	
	g_list = List_Init();
	if (NULL == g_list)
	{
		u32RetErr = ERR_SYSTEM_MEMRY_POINTER_NULL;
	}
	
	EXPECT_EQ(ERR_SUCCESS, u32RetErr);
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out	:
* @return 	:
* @note		:
********************************************************************************/
void UT_List_Display(UINT32 u32Index, void *pElementData)
{
	printf("node-%d\t%d\n", u32Index, *(UINT32 *)pElementData);

	return;
}


/******************************************************************************
*
* @brief	:
* @param in	:
* @param out	:
* @return 	:
* @note		:
********************************************************************************/
TEST(list, List_InsertToTail)
{
	UINT32 u32RetErr = ERR_SUCCESS;
	UINT32 u32Loop = 0;
	UINT32 *pElementData = NULL;
	
	for (u32Loop = 0; u32Loop < g_ListLen; u32Loop++)
	{
		pElementData = (UINT32 *)MP_Malloc(sizeof(UINT32));
		if (NULL == pElementData)
		{
			u32RetErr = ERR_SYSTEM_MEMRY_POINTER_NULL;
		}
		
		EXPECT_EQ(ERR_SUCCESS, u32RetErr);
		
		*pElementData = (1 << u32Loop);
		
		u32RetErr = List_InsertToTail(g_list, pElementData, NULL);
		EXPECT_EQ(ERR_SUCCESS, u32RetErr);
	}

	//printf("List_InsertToTail:\n");
	//List_Display(g_list , UT_List_Display);
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out	:
* @return 	:
* @note		:
********************************************************************************/
TEST(list, List_DeleteFromTail)
{
	UINT32 u32RetErr = ERR_SUCCESS;
	UINT32 u32Count = 0;
	UINT32 u32ListLenth = 0;
	
	while (LIST_NOT_EMPTY == List_IsEmpty(g_list))
	{
		u32RetErr = List_DeleteFromTail(g_list, NULL);
		EXPECT_EQ(ERR_SUCCESS, u32RetErr);

		u32Count++;
	}

	EXPECT_EQ(u32Count, g_ListLen);

	u32ListLenth = List_GetLength(g_list);
	EXPECT_EQ(0, u32ListLenth);
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out	:
* @return 	:
* @note		:
********************************************************************************/
TEST(list, List_InsertToHead)
{
	UINT32 u32RetErr = ERR_SUCCESS;
	UINT32 u32Loop = 0;
	UINT32 *pElementData = NULL;
	UINT32 u32ListLength = 0;
	
	for (u32Loop = 0; u32Loop < g_ListLen; u32Loop++)
	{
		pElementData = (UINT32 *)MP_Malloc(sizeof(UINT32));
		*pElementData = (1 << u32Loop);
		
		u32RetErr = List_InsertToHead(g_list, pElementData, NULL);
		EXPECT_EQ(ERR_SUCCESS, u32RetErr);
	}

	u32ListLength = List_GetLength(g_list);
	EXPECT_EQ(g_ListLen, u32ListLength);
	
	//printf("List_InsertToHead:\n");
	//List_Display(g_list , UT_List_Display);
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out	:
* @return 	:
* @note		:
********************************************************************************/
TEST(list, List_Reverse)
{
	List_Reverse(g_list);
	
	//printf("List_Revert :\n");
	//List_Display(g_list , UT_List_Display);
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out	:
* @return 	:
* @note		:
********************************************************************************/
static UINT32 UT_List_CmpData(const void *pListData, const void *pSearchData)
{
	if (*(UINT32 *)pListData == *(UINT32 *)pSearchData)
	{
		return LIST_CMPDATA_EQUAL;
	}
	else
	{
		return LIST_CMPDATA_NO_EQUAL;
	}
}
	

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out	:
* @return 	:
* @note		:
********************************************************************************/
TEST(list, List_SearchData)
{
	UINT32 u32RetErr = ERR_SUCCESS;
	UINT32 u32ElementData = 0;
	void *pListElement = NULL;
	UINT32 u32Loop = 0;
	UINT32 u32Value = 0;
	
	for (u32Loop = 0; u32Loop < g_ListLen; u32Loop++)
	{
		u32ElementData = 1 << u32Loop;
		pListElement = List_SearchData(g_list, (void *)&u32ElementData, UT_List_CmpData);
		if (NULL == pListElement)
		{
			u32RetErr = ERR_SYSTEM_MEMRY_POINTER_NULL;
		}

		EXPECT_EQ(ERR_SUCCESS, u32RetErr);

		u32Value = *(UINT32 *)pListElement;
		EXPECT_EQ(u32ElementData, u32Value);
	}
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out	:
* @return 	:
* @note		:
********************************************************************************/
TEST(list, List_DeleteFromHead)
{
	UINT32 u32RetErr = ERR_SUCCESS;
	UINT32 u32ListLength = 0;
	
	while (LIST_NOT_EMPTY == List_IsEmpty(g_list))
	{
		u32RetErr = List_DeleteFromHead(g_list, NULL);
		EXPECT_EQ(ERR_SUCCESS, u32RetErr);
	}

	u32ListLength = List_GetLength(g_list);
	EXPECT_EQ(0, u32ListLength);
}

