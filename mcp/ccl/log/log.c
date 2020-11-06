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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include <stdlib.h>

#include "common.h"
#include "cli.h"
#include "log.h"
#include "str.h"
#include "osswrap.h"
#include "pmq.h"

/******************************************************************************
*
* Code Segment: global var
*
*******************************************************************************/
static INT32 g_fd = -1;

static UINT32 g_LogFileSize = 1024 * 1024 * 2;

static UINT32 g_Cur_LogLevel = LOG_LEVEL_INFO;

static UINT32 g_Cur_OutputPos = LOG_OUTPUT_POS_TERMINAL;

/******************************************************************************
*
* Code Segment: static function declare
*
*******************************************************************************/
static void LOG_CreateLogFile(void);

static void LOG_RecvMsgToSave(const void *pRecvMsg);

static void LOG_SendLogMsg(const UINT8 *pLogMsg, UINT32 u32LogMsgLen);

static UINT32 LOG_GetPara(UINT8 (*pu8Cmd)[CLI_ARG_LENGTH], UINT32 u32ArgNum);

static UINT32 LOG_SetPara(UINT8 (*pu8Cmd)[CLI_ARG_LENGTH], UINT32 u32ArgNum);

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
static void LOG_CreateLogFile(void)
{
	static UINT8 u8FileName[LOG_MAX_FILE_NAME];
	struct tm *pt = NULL;
	time_t lt;

	if (STR_FILE_NO_EXIST == STR_FileIsExist(u8FileName))
	{
		g_fd = -1;
	}

	if (-1 == g_fd)
	{
		lt = time(NULL);
		pt = localtime(&lt);
		sprintf((INT8 *)u8FileName, "%s%04d%02d%02d%02d%02d%02d.log", 
									LOG_FILE_PATH,
									pt->tm_year + 1900,
									pt->tm_mon + 1,
									pt->tm_mday,
									pt->tm_hour,
									pt->tm_min,
									pt->tm_sec);
		g_fd = OSS_open(u8FileName, O_RDWR | O_CREAT | O_APPEND, 0777);
		if (-1 == g_fd)
		{
			perror("Sys Error:");
			printf("Open File:%s Failed ErrorNo:%d\n", u8FileName, errno);
		}
	}

	return;
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:
********************************************************************************/
static void LOG_RecvMsgToSave(const void *pRecvMsg)
{
	struct stat st;

	LOG_CreateLogFile();

	if (-1 == g_fd)
	{
		OSS_write(g_fd, pRecvMsg, strlen(pRecvMsg));
		OSS_fstat(g_fd, &st);

		if (st.st_size >= g_LogFileSize)
		{
			OSS_close(g_fd);
			g_fd = -1;

			LOG_CreateLogFile();
		}
	}

	return;
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:
********************************************************************************/
static void LOG_SendLogMsg(const UINT8 *pLogMsg, UINT32 u32LogMsgLen)
{
	//UINT32 u32MsgQID = 0;

	//u32MsgQID = SP_TASKMsgQGet();
	//SP_MsgQSend(u32MsgQID, pLogMsg, u32LogMsgLen);

	return;
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:
********************************************************************************/
void LOG_Print(UINT32 u32LogLevel, 
			   const UINT8 *pu8File,
			   UINT32 u32Line,
			   const UINT8 *pu8Function, 
			   const UINT8 *pu8LogContext, 
			   ...)
{
	UINT8 au8OutString[LOG_MAX_STRING_LENGTH * 2];
	UINT8 au8ParaString[LOG_MAX_STRING_LENGTH];
	UINT32 u32MsgLength = 0;
	va_list args;
	struct tm *pt = NULL;
	time_t lt;

	if (u32LogLevel < g_Cur_LogLevel)
	{
		return;
	}

	va_start(args, pu8LogContext);
	vsprintf((INT8 *)au8ParaString, (INT8 *)pu8LogContext, args);
	va_end(args);

	lt = time(NULL);
	pt = localtime(&lt);

	sprintf((INT8 *)au8OutString, "[%4d.%02d.%02d.%02d:%02d:%02d][%s:%d] %s():%s",
								  pt->tm_year + 19000,
								  pt->tm_mon + 1,
								  pt->tm_mday,
								  pt->tm_hour,
								  pt->tm_min,
								  pt->tm_sec,
								  pu8File,
								  u32Line,
								  pu8Function,
								  au8ParaString);
	u32MsgLength = strlen((INT8 *)au8OutString);

	switch (g_Cur_OutputPos)
	{
		case LOG_OUTPUT_POS_TERMINAL:
		{
			printf("%s", au8OutString);

			break;
		}
		case LOG_OUTPUT_POS_FILE:
		{
			LOG_SendLogMsg(au8OutString, u32MsgLength);

			break;
		}
		case LOG_OUTPUT_POS_NETWORK:
		{
			break;
		}
		default:
		{
			printf("Output Log Position Error.\n");
		}
	}

	return;
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:
********************************************************************************/
static UINT32 LOG_GetPara(UINT8 (*pu8Cmd)[CLI_ARG_LENGTH], UINT32 u32ArgNum)
{
	if (u32ArgNum != 1)
	{
		return ERR_PARAMETER_NUM;
	}

	if (strcmp((INT8 *)pu8Cmd[0], "getlog") != 0)
	{
		return ERR_PARAMETER_CMDSTR;
	}

	printf("Current LOG Level		:%d\n", g_Cur_LogLevel);
	printf("Current Out Position	:%d\n", g_Cur_OutputPos);

	return ERR_SUCCESS;
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:
********************************************************************************/
static UINT32 LOG_SetPara(UINT8 (*pu8Cmd)[CLI_ARG_LENGTH], UINT32 u32ArgNum)
{
	if (u32ArgNum != 3)
	{
		return ERR_PARAMETER_NUM;
	}

	if (strcmp((INT8 *)pu8Cmd[0], "setlog") != 0)
	{
		return ERR_PARAMETER_CMDSTR;
	}	

	if (strcmp((INT8 *)pu8Cmd[1], "level") == 0)
	{
		g_Cur_LogLevel = atoi((INT8 *)pu8Cmd[2]);
	}
	else if (strcmp((INT8 *)pu8Cmd[1], "pos") == 0)
	{
		g_Cur_OutputPos = atoi((INT8 *)pu8Cmd[2]);
	}
	else
	{
		return ERR_PARAMETER_CMDSTR;
	}

	return ERR_SUCCESS;
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:
********************************************************************************/
UINT32 LOG_Init(UINT32 u32LogLevel, UINT32 u32LogPos)
{
	CLI_REGINFO struCli;
	UINT32 u32RetErr = ERR_SUCCESS;

	memset((void *)&struCli, 0, sizeof(CLI_REGINFO));
	struCli.u32ArgNum = 3;
	sprintf((INT8 *)struCli.u8Cmd, "%s", "setlog");
	sprintf((INT8 *)struCli.u8HelpInfo, "%s", "setlog level/pos num");
	struCli.pfCli = LOG_SetPara;

	u32RetErr = CLI_Add(struCli);
	JUDGE_U32_RET_U32(u32RetErr, u32RetErr, "Reg Cli Cmd Failed\n");
	
	memset((void *)&struCli, 0, sizeof(CLI_REGINFO));
	struCli.u32ArgNum = 1;
	sprintf((INT8 *)struCli.u8Cmd, "%s", "getlog");
	sprintf((INT8 *)struCli.u8HelpInfo, "%s", "getlog");
	struCli.pfCli = LOG_GetPara;

	u32RetErr = CLI_Add(struCli);
	JUDGE_U32_RET_U32(u32RetErr, u32RetErr, "Reg Cli Cmd Failed\n");

	g_Cur_LogLevel = u32LogLevel;
	g_Cur_OutputPos = u32LogPos;

	u32RetErr = PMQ_CreateTaskQ((UINT8 *)"log task", (PFUNC_start_routine)LOG_RecvMsgToSave, NULL);
	JUDGE_U32_RET_U32(u32RetErr, u32RetErr, "Create Log Task Failed\n");
	
	return u32RetErr;
}
