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
#include <mqueue.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

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
* @param out	:
* @return 	:
* @note		:
********************************************************************************/
UINT32 OSS_open(const UINT8 *pu8PathName, UINT32 u32Flags, UINT32 u32Mode)
{
	INT32 s32RetErr = 0;
	
	s32RetErr = open((INT8 *)pu8PathName, u32Flags, u32Mode);
	if (-1 == s32RetErr)
	{
		return ERR_FILE_OPEN_FAILED;
	}
	return (UINT32)s32RetErr;
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:
********************************************************************************/
UINT32 OSS_read(UINT32 u32fd, void *buff, UINT32 u32len)
{
	INT32 s32ReadLen = 0;;
	
	s32ReadLen = read(u32fd, buff, u32len);
	if (-1 == s32ReadLen)
	{
		return ERR_FILE_READ_FAILED;
	}

	return s32ReadLen;
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:
********************************************************************************/
UINT32 OSS_write(UINT32 u32fd, const void *buff, UINT32 u32len)
{
	INT32 s32WriteLen = 0;;
	
	s32WriteLen = write(u32fd, buff, u32len);
	if (-1 == s32WriteLen)
	{
		return ERR_FILE_WRITE_FAILED;
	}

	return s32WriteLen;
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:
********************************************************************************/
UINT32 OSS_lseek(UINT32 u32fd, UINT32 u32Pos, UINT32 u32Flag)
{
	INT32 s32RetValue = 0;;
	
	s32RetValue = lseek(u32fd, u32Pos, u32Flag);
	if (-1 == s32RetValue)
	{
		return ERR_FILE_LSEEK_FAILED;
	}

	return s32RetValue;
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:
********************************************************************************/
UINT32 OSS_fstat(UINT32 u32fd, void *statbuf)
{
	INT32 s32RetValue = 0;
	
	s32RetValue = fstat(u32fd, statbuf);
	if (-1 == s32RetValue)
	{
		return ERR_FILE_FSTAT_FAILED;
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
UINT32 OSS_close(UINT32 u32fd)
{
	INT32 s32RetValue = 0;;
	
	s32RetValue = close(u32fd);
	if (-1 == s32RetValue)
	{
		return ERR_FILE_CLOSE_FAILED;
	}

	return s32RetValue;
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:
********************************************************************************/
UINT32 OSS_pthread_create(UINT32 *pu32ID, const void *attr, PFUNC_start_routine pf_routine, void *arg)
{
	INT32 s32RetValue = 0;
	
	s32RetValue = pthread_create((pthread_t *)pu32ID, attr, pf_routine, arg);
	if (0 != s32RetValue)
	{
		return ERR_THREAD_CREATE_FAILED;
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
UINT32 OSS_mq_open(const UINT8 *pMQName, UINT32 u32Oflag, const void *attr)
{
	INT32 s32MQid = 0;

	s32MQid = mq_open((INT8 *)pMQName, u32Oflag, attr);
	if (s32MQid < 0)
	{
		return ERR_MSGQUEUE_CREATE_FAILED;
	}

	return (UINT32)s32MQid;
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:
********************************************************************************/
UINT32 OSS_mq_send(UINT32 u32MQID, const void *pMsgBuff, UINT32 u32MsgLength, UINT32 u32MsgPrio)
{
	INT32 s32RetValue = 0;

	s32RetValue = mq_send(u32MQID, pMsgBuff, u32MsgLength, u32MsgPrio);
	if (-1 == s32RetValue)
	{
		return ERR_MSGQUEUE_SEND_FAILED;
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
UINT32 OSS_mq_receive(UINT32 u32MQID, UINT8 *pMsgBuff, UINT32 u32MsgLength, UINT32 *pu32MsgPrio)
{
	INT32 s32RetValue = 0;

	s32RetValue = mq_receive(u32MQID, (INT8 *)pMsgBuff, u32MsgLength, pu32MsgPrio);
	if (-1 == s32RetValue)
	{
		return ERR_MSGQUEUE_RECEIVE_FAILED;
	}

	return (UINT32)s32RetValue;
}

