/******************************************************************************
*
* Copyright (C) Louis.hoo
* All Rights Reserved. Confidential
*
*******************************************************************************
*
* Project: <>
* Subproject: <>
* File Name: <>
* Author: <>
* Creation Date: <>
* Revision: <>
* Last modified by: <>
*
*******************************************************************************/

#ifndef _COMMON_H
#define _COMMON_H

/******************************************************************************
*
* Code Segment: Macro define
*
*******************************************************************************/
#define ERR_SUCCESS								0x00


#define ERR_SYSTEM								(0x01 << 24)
#define ERR_SYSTEM_MEMRY_POINTER_NULL			(ERR_SYSTEM | 0x01)
#define ERR_SYSTEM_MEMORY_ALLOC_FAILED			(ERR_SYSTEM | 0x02)

#define ERR_FILE								(0x02 << 24)
#define ERR_FILE_OPEN_FAILED					(ERR_FILE | 0x01)
#define ERR_FILE_READ_FAILED					(ERR_FILE | 0x02)
#define ERR_FILE_WRITE_FAILED					(ERR_FILE | 0x03)
#define ERR_FILE_CLOSE_FAILED					(ERR_FILE | 0x04)
#define ERR_FILE_LSEEK_FAILED					(ERR_FILE | 0x05)
#define ERR_FILE_FSTAT_FAILED					(ERR_FILE | 0x05)
#define ERR_FILE_TRUNCATE_FAILED				(ERR_FILE | 0x02)

#define ERR_SERVICE								(0x03 << 24)
#define ERR_SERVICE_DATA_DUPLICATION			(ERR_SERVICE | 0x01)

#define ERR_PARAMETER							(0x04 << 24)
#define ERR_PARAMETER_NUM						(ERR_PARAMETER | 0X01)
#define ERR_PARAMETER_CMDSTR					(ERR_PARAMETER | 0X02)

#define ERR_THREAD								(0x05 << 24)
#define ERR_THREAD_CREATE_FAILED				(ERR_THREAD |0x01)

#define ERR_MSGQUEUE							(0x06 << 24)
#define ERR_MSGQUEUE_CREATE_FAILED				(ERR_THREAD |0x01)
#define ERR_MSGQUEUE_SEND_FAILED				(ERR_THREAD |0x02)
#define ERR_MSGQUEUE_RECEIVE_FAILED				(ERR_THREAD |0x03)



#define JUDGE_U32_RET_U32(RetVar, RetValue, Desc)\
	if (ERR_SUCCESS != RetVar)\
	{\
		printf("%s", Desc);\
		return RetValue;\
	}

#define JUDGE_U32_RET_S32(RetVar, RetValue, Desc)\
	if (ERR_SUCCESS != RetVar)\
	{\
		printf("%s", Desc);\
		return (INT32)RetValue;\
	}

#define JUDGE_POINTER_RET_U32(RetVar, RetValue, Desc)\
	if (NULL == RetVar)\
	{\
		printf("%s", Desc);\
		return RetValue;\
	}

#define JUDGE_POINTER_RET_NULL(RetVar, Desc)\
	if (NULL == RetVar)\
	{\
		printf("%s", Desc);\
		return NULL;\
	}

#define JUDGE_POINTER_RET_VOID(RetVar, Desc)\
	if (NULL == RetVar)\
	{\
		printf("%s", Desc);\
		return;\
	}	

#define JUDGE_U32_RET_VOID(RetVar, Desc)\
	if (ERR_SUCCESS != RetVar)\
	{\
		printf("%s", Desc);\
		return;\
	}			

#define MARK_VALUE_INVALID					0xFFFFFFFE;

/******************************************************************************
*
* Code Segment: typedef
*
*******************************************************************************/

typedef char 					INT8;
typedef short int 				INT16;
typedef int						INT32;
typedef long					LONG;

typedef unsigned char 			UINT8;
typedef unsigned short int		UINT16;
typedef unsigned int			UINT32;
typedef unsigned long			ULONG;


/******************************************************************************
*
* Code Segment: function declare
*
*******************************************************************************/

#endif
