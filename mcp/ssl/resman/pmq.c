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
* Brief:pthread and msg queue
*******************************************************************************/

/******************************************************************************
*
* Code Segment: include
*
*******************************************************************************/
#include <stdio.h>

#include "common.h"
#include "osswrap.h"
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
UINT32 PMQ_CreateTaskQ(UINT8 *pu8TaskName, PFUNC_start_routine pf_routine, void *arg)
{
	UINT32 u32RetErr = ERR_SUCCESS;
	UINT32 u32TaskID = 0;
	
	u32RetErr = OSS_pthread_create(&u32TaskID, NULL, pf_routine, NULL);
	JUDGE_U32_RET_U32(u32RetErr, u32RetErr, "Create Task Failed\n");
	
	return u32RetErr;
}

