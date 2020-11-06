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

#ifndef _OSSWRAP_H
#define _OSSWRAP_H

/******************************************************************************
*
* Code Segment: Macro define
*
*******************************************************************************/
#define OSS_OS_LINUX		0
#define OSS_OS_WIN			1
#define OSS_OS_VXWORKS		2

#define OSS_OS_CUR			OSS_OS_LINUX

/******************************************************************************
*
* Code Segment: typedef
*
*******************************************************************************/
typedef void *(*PFUNC_start_routine)(void *arg);



/******************************************************************************
*
* Code Segment: function declare
*
*******************************************************************************/
UINT32 OSS_open(const UINT8 *pu8PathName, UINT32 u32Flags, UINT32 u32Mode);

UINT32 OSS_read(UINT32 u32fd, void *buff, UINT32 u32len);

UINT32 OSS_write(UINT32 u32fd, const void *buff, UINT32 u32len);

UINT32 OSS_lseek(UINT32 u32fd, UINT32 u32Pos, UINT32 u32Flag);

UINT32 OSS_fstat(UINT32 u32fd, void *statbuf);

UINT32 OSS_close(UINT32 u32fd);

UINT32 OSS_pthread_create(UINT32 *pu32ID, const void *attr, PFUNC_start_routine pf_routine, void *arg);

UINT32 OSS_mq_open(const UINT8 *pMQName, UINT32 u32Oflag, const void *attr);

UINT32 OSS_mq_send(UINT32 u32MQID, const void *pMsgBuff, UINT32 u32MsgLength, UINT32 u32MsgPrio);

UINT32 OSS_mq_receive(UINT32 u32MQID, UINT8 *pMsgBuff, UINT32 u32MsgLength, UINT32 *pu32MsgPrio);

#endif

