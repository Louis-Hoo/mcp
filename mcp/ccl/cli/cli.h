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

#ifndef _CLI_H
#define _CLI_H

/******************************************************************************
*
* Code Segment: Macro define
*
*******************************************************************************/
#define CLI_CMD_LENGTH			16				/* CMD Operation String Length	*/
#define CLI_ARG_NUM				8
#define CLI_ARG_LENGTH			16
#define CLI_HEALP_LENGTH		128

#define CLI_MAX_LENGTH			(CLI_CMD_LENGTH + CLI_ARG_NUM * CLI_ARG_LENGTH)

/******************************************************************************
*
* Code Segment: typedef
*
*******************************************************************************/
typedef UINT32 (*PFUNC_CLI_EXEC)(UINT8 (*UINT8)[CLI_ARG_LENGTH], UINT32 u32ArgNum);

typedef struct tag_CLI_OPTION
{
	UINT32 u32ArgNum;
	UINT8 u8CmdArgList[CLI_ARG_NUM][CLI_ARG_LENGTH];
	PFUNC_CLI_EXEC pfCli;
}CLI_OPTION;

typedef struct tag_CLI_REGINFO
{
	UINT8 u8Cmd[CLI_CMD_LENGTH];		/* The whole cmd context */
	UINT32 u32ArgNum;					/* cmd operation string and parameter */
	PFUNC_CLI_EXEC pfCli;				/* the callback function of cmd */
	UINT8 u8HelpInfo[CLI_HEALP_LENGTH];	/* the help info of cmd */
}CLI_REGINFO;

/******************************************************************************
*
* Code Segment: function declare
*
*******************************************************************************/
UINT32 CLI_Add(CLI_REGINFO struCli);

void CLI_Run(void);

#endif

