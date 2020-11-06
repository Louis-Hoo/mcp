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
#include <stdlib.h>

#include "common.h"
#include "mempool.h"
#include "list.h"
#include "cli.h"
#include "log.h"

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
INT32 main(void)
{
	UINT32 u32RetErr = ERR_SUCCESS;
	
	u32RetErr = MP_Init(NULL, 0);
	JUDGE_U32_RET_S32(u32RetErr, u32RetErr, "MemPool Init Failed.\n");

	u32RetErr = LOG_Init(LOG_LEVEL_INFO, LOG_OUTPUT_POS_TERMINAL);
	JUDGE_U32_RET_S32(u32RetErr, u32RetErr, "LOG Init Failed.\n");
	
	CLI_Run();
	
	return 0;
}
