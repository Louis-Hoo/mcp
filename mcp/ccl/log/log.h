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

#ifndef _LOG_H
#define _LOG_H

/******************************************************************************
*
* Code Segment: Macro define
*
*******************************************************************************/
#define LOG_LEVEL_NOTHING				0
#define LOG_LEVEL_INFO					1
#define LOG_LEVEL_DEBUG					2
#define LOG_LEVEL_WARNING				3
#define LOG_LEVEL_ERROR					4
#define LOG_LEVEL_CRIT					5

#define LOG_OUTPUT_POS_TERMINAL			0
#define LOG_OUTPUT_POS_FILE				1
#define LOG_OUTPUT_POS_NETWORK			2

#define LOG_MAX_STRING_LENGTH			256
#define LOG_MAX_FILE_NAME				128

#define LOG_FILE_PATH					"./"

#ifdef SWITCH_LOG
#define LOG(level, fmt, ...)	\
	LOG_Print(level, (UINT8 *)__FILE__, (UINT8 *)__LINE__, (UINT8 *)__LINE__, fmt, ##__VA_ARGS__)
#else
#define LOG(level, fmt, ...)
#endif
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
UINT32 LOG_Init(UINT32 u32LogLevel, UINT32 u32LogPos);

void LOG_Print(UINT32 u32LogLevel, 
			   const UINT8 *pu8File,
			   UINT32 u32Line,
			   const UINT8 *pu8Function, 
			   const UINT8 *pu8LogContext, 
			   ...);

#endif

