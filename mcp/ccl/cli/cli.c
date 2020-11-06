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
#include <string.h>
#include <stdlib.h>

#include "common.h"
#include "mempool.h"
#include "str.h"
#include "list.h"
#include "cli.h"




/******************************************************************************
*
* Code Segment: global var
*
*******************************************************************************/
static node *g_pList = NULL;

/******************************************************************************
*
* Code Segment: static function declare
*
*******************************************************************************/
static UINT32 CLI_CompareData(const void *pListData, const void *pSearchData);

static void CLI_Welcome(void);

static void CLI_Exec(CLI_OPTION struCliOpn);

static CLI_OPTION CLI_Parse(UINT8 au8Str[]);

static UINT32 CLI_Born(UINT8 (*pu8Cmd)[CLI_ARG_LENGTH], UINT32 u32ArgNum);

static UINT32 CLI_Help(UINT8 (*pu8Cmd)[CLI_ARG_LENGTH], UINT32 u32ArgNum);

static void CLI_DisplayData(UINT32 u32NodeIndex, void *pElementData);

static UINT32 CLI_DefaultCmd(void);
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
static CLI_OPTION CLI_Parse(UINT8 au8Str[])
{
	UINT32 u32Loop = 0;
	UINT8 *pu8Ch = au8Str;
	CLI_OPTION struCli;
	UINT8 *pu8Arr[CLI_ARG_NUM] = {NULL};

	memset((void *)&struCli, 0, sizeof(CLI_OPTION));

	STR_DelBlank(au8Str);

	pu8Arr[u32Loop++] = au8Str;

	while (*pu8Ch != '\0')
	{
		if (*pu8Ch == ' ')
		{
			pu8Arr[u32Loop++] = pu8Ch + 1;
			*pu8Ch = '\0';
		}

		pu8Ch++;
	}

	struCli.u32ArgNum = u32Loop;

	u32Loop = 0;
	while (pu8Arr[u32Loop] != NULL)
	{
		memcpy(struCli.u8CmdArgList[u32Loop], pu8Arr[u32Loop], strlen((INT8 *)pu8Arr[u32Loop]));

		u32Loop++;
	}

	return struCli;
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out	:
* @return 	:
* @note		:
********************************************************************************/
UINT32 CLI_Add(CLI_REGINFO struCli)
{
	CLI_REGINFO *pCliRegInfo = NULL;
	UINT32 u32RetErr = ERR_SUCCESS;

	if (NULL == g_pList)
	{
		g_pList = List_Init();
		JUDGE_POINTER_RET_U32(g_pList, ERR_SYSTEM_MEMRY_POINTER_NULL, "Point Is NULL\n");	
	}

	pCliRegInfo = List_SearchData(g_pList, struCli.u8Cmd, CLI_CompareData);
	if (NULL != pCliRegInfo)
	{
		printf("Cmd:%s Exist\n", struCli.u8Cmd);

		return ERR_SERVICE_DATA_DUPLICATION;
	}
	
	pCliRegInfo = (CLI_REGINFO *)MP_Malloc(sizeof(CLI_REGINFO));
	JUDGE_POINTER_RET_U32(pCliRegInfo, ERR_SYSTEM_MEMRY_POINTER_NULL, "Point Is NULL\n");

	memcpy((void *)pCliRegInfo, (void *)&struCli, sizeof(CLI_REGINFO));
	
	u32RetErr = List_InsertToHead(g_pList, (void *)pCliRegInfo, NULL);
	JUDGE_U32_RET_U32(u32RetErr, u32RetErr, "List Insert Failed\n");

	return u32RetErr;
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out	:
* @return 	:
* @note		:
********************************************************************************/
static UINT32 CLI_CompareData(const void *pListData, const void *pSearchData)
{
	const CLI_REGINFO *pCliRegInfo = NULL;

	JUDGE_POINTER_RET_U32(pListData, ERR_SYSTEM_MEMRY_POINTER_NULL, "List Data Pointer Is NULL\n");
	JUDGE_POINTER_RET_U32(pSearchData, ERR_SYSTEM_MEMRY_POINTER_NULL, "pSearchData Pointer Is NULL\n");

	pCliRegInfo = pListData;
	if (strcmp((INT8 *)pCliRegInfo->u8Cmd, (INT8 *)pSearchData) == 0)
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
void CLI_Run(void)
{
	UINT8 u8Buff[CLI_MAX_LENGTH];
	CLI_OPTION struCliOpn;

	CLI_DefaultCmd();
	
	CLI_Welcome();
	
	while (1)
	{
		printf("MCP:/>");

		memset((void *)u8Buff, 0, CLI_MAX_LENGTH);

		fgets((INT8 *)u8Buff, CLI_MAX_LENGTH, stdin);
		
		if (u8Buff[0] == '\n')
		{
			continue;
		}

		struCliOpn = CLI_Parse(u8Buff);
		CLI_Exec(struCliOpn);
	}

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
static void CLI_Exec(CLI_OPTION struCliOpn)
{
	UINT32 u32RetErr = ERR_SUCCESS;
	CLI_REGINFO *pCliRegInfo = NULL;

	JUDGE_POINTER_RET_VOID(g_pList, "No Cmd Can Run\n");
	
	pCliRegInfo = List_SearchData(g_pList, struCliOpn.u8CmdArgList[0], CLI_CompareData);
	if (NULL == pCliRegInfo)
	{
		printf("Command Is Not EWxist\n");

		return;
	}

	printf("=====================================================================\n");
	u32RetErr = pCliRegInfo->pfCli(struCliOpn.u8CmdArgList, struCliOpn.u32ArgNum);
	printf("=====================================================================\n");
	if (ERR_SUCCESS != u32RetErr)
	{
		printf("Command Exec Failed.\n");
	}

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
static void CLI_Welcome(void)
{
	printf("=================================================================\n");
	printf("=========                 Welcome MCP Cli                ========\n");
	printf("=================================================================\n");

	return;
}

/******************************************************************************
*
* @brief	:
* @param in :
* @param out	:
* @return	:
* @note 	:
********************************************************************************/
static UINT32 CLI_Born(UINT8 (*pu8Cmd)[CLI_ARG_LENGTH], UINT32 u32ArgNum)
{
	printf("Compile Time:%s:%s\n", __DATE__, __TIME__);

	return ERR_SUCCESS;
}

/******************************************************************************
*
* @brief	:
* @param in :
* @param out	:
* @return	:
* @note 	:
********************************************************************************/
static UINT32 CLI_Help(UINT8 (*pu8Cmd)[CLI_ARG_LENGTH], UINT32 u32ArgNum)
{
	return List_Display(g_pList, CLI_DisplayData);
}

/******************************************************************************
*
* @brief	:
* @param in :
* @param out	:
* @return	:
* @note 	:
********************************************************************************/
static void CLI_DisplayData(UINT32 u32NodeIndex, void *pElementData)
{
	CLI_REGINFO *pCliRegInfo = NULL;

	JUDGE_POINTER_RET_VOID(pElementData, "List Data NULL\n");

	pCliRegInfo = (CLI_REGINFO *)pElementData;

	printf("%s\t\t\t%s\n", pCliRegInfo->u8Cmd, pCliRegInfo->u8HelpInfo);

	return;
}

/******************************************************************************
*
* @brief	:
* @param in :
* @param out	:
* @return	:
* @note 	:
********************************************************************************/
static UINT32 CLI_DefaultCmd(void)
{
	CLI_REGINFO struCli;
	UINT32 u32RetErr = ERR_SUCCESS;
	
	struCli.pfCli = CLI_Born;
	struCli.u32ArgNum = 1;
	sprintf((INT8 *)struCli.u8Cmd, "%s", "born");
	sprintf((INT8 *)struCli.u8HelpInfo, "%s", "born");
	
	u32RetErr = CLI_Add(struCli);
	JUDGE_U32_RET_U32(u32RetErr, u32RetErr, "Add Cli Failed\n");

	struCli.pfCli = CLI_Help;
	struCli.u32ArgNum = 1;
	sprintf((INT8 *)struCli.u8Cmd, "%s", "help");
	sprintf((INT8 *)struCli.u8HelpInfo, "%s", "help");
	
	u32RetErr = CLI_Add(struCli);
	JUDGE_U32_RET_U32(u32RetErr, u32RetErr, "Add Cli Failed\n");

	struCli.pfCli = CLI_Help;
	struCli.u32ArgNum = 1;
	sprintf((INT8 *)struCli.u8Cmd, "%s", "?");
	sprintf((INT8 *)struCli.u8HelpInfo, "%s", "?");
	
	u32RetErr = CLI_Add(struCli);
	JUDGE_U32_RET_U32(u32RetErr, u32RetErr, "Add Cli Failed\n");

	return u32RetErr;
}
