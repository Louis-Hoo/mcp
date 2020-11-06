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
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "common.h"
#include "mempool.h"
#include "str.h"

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
UINT32 STR_StrToNum(const UINT8 *pu8Str)
{
	UINT8 *pu8Char = NULL;
	UINT32 u32Result = 0;
	
	JUDGE_POINTER_RET_U32(pu8Str, ERR_SYSTEM_MEMRY_POINTER_NULL, "Input NULL");

	if (*pu8Str == '0' && (*(pu8Str + 1) == 'x' || *(pu8Str + 1) == 'X'))
	{
		pu8Char = (UINT8 *)pu8Str + 2;
	}
	else if (*pu8Str == '0' && *(pu8Str + 1) != 'x' && *(pu8Str + 1) != 'X')
	{
		return 0;
	}
	else
	{
		pu8Char = (UINT8 *)pu8Str;
	}
	
	while (*pu8Char != '\0')
	{
		if (*pu8Char >= '0' && *pu8Char <= '9')
		{
			u32Result = u32Result * 16 + (*pu8Char - '0');
		}
		else if (*pu8Char >= 'a' && *pu8Char <= 'f')
		{
			u32Result = u32Result * 16 + (*pu8Char - 'a' + 10);
		}
		else if (*pu8Char >= 'A' && *pu8Char <= 'F')
		{
			u32Result = u32Result * 16 + (*pu8Char - 'A' + 10);
		}
		else
		{
			printf("Wrong Char:%c\n", *pu8Char);

			return u32Result;
		}

		pu8Char++;
	}

	return u32Result;
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:
********************************************************************************/
UINT8 *STR_NumToStr(UINT32 num, UINT8 des[])
{
	char ch[32];
	int i = 0,j = 0,k = 0;
	do 
	{
		ch[i++] = num % 10 + '0';
	}while (num /= 10);

	k = i - 1;

	for (j = 0;j<= i;j++,k--)
	{
		des[j] = ch[k];
	}
	
	des[j - 1] = '\0';

	return des;
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:
********************************************************************************/
UINT32 STR_HexToDec(const UINT8 *hex)
{
	const UINT8 *p = hex;
	UINT32 t = 0,n = 0;

	while (*p != '\0')
	{
		if (*p >= '0' && *p <= '9')
		{
			t = t + (*p - '0');
		}
		else if (*p >= 'a' && *p <= 'f')
		{
			t = *p - 'a' + 10;
		}
		else if (*p >= 'A' && *p <= 'F')
		{
			t = *p - 'A' + 10;
		}
		else
		{
			t = 0;
		}
		
		n = n * 16 + t;
		p++;
	}

	return n;
}

void STR_DecToHex(UINT32 dec, UINT32 len, UINT8 s[])
{
	UINT8 cell[] = "0123456789ABCDEF";
	UINT32 i = 0;

	memset(s, '0', len);

	while (dec != 0)
	{
		s[i++] = cell[dec % 16];
		dec = dec / 16;
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
void STR_DecToBin(UINT32 u32Dec, UINT32 u32Len, UINT8 u8Bin[])
{
	UINT32 u32Loop = 0;
	
	memset(u8Bin, '0', u32Len);
	
	while (u32Dec != 0)
	{
		u8Bin[u32Loop++] = u32Dec % 2 + 48;
		u32Dec = u32Dec / 2;
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
UINT32 STR_FileIsExist(const UINT8 *pFilePath)
{
	JUDGE_POINTER_RET_U32(pFilePath, ERR_SYSTEM_MEMRY_POINTER_NULL, "Input File Path NULL.\n");

	if (access((INT8 *)pFilePath, F_OK) == 0)
	{
		return STR_FILE_IS_EXIST;
	}

	return STR_FILE_NO_EXIST;
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:
********************************************************************************/
void STR_DelBlank(UINT8 u8Str[])
{
	UINT8 *u8q, *u8p = u8Str;
	UINT32 u32flag = 0;

	while (*u8p == ' ')
	{
		u8q = u8p;
		while (*u8q != '\0')
		{
			*u8q = *(u8q + 1);
			u8q++;
		}
		
		*(--u8q) = '\0';
	}

	u8p = u8Str;

	while (*u8p != '\0')
	{
		if (*u8p == ' ' && *(u8p + 1) == ' ')
		{
			u32flag = 1;
			u8q = u8p + 1;

			while (*u8q != '\0')
			{
				*u8q = *(u8q + 1);
				u8q++;
			}
		}
		else
		{
			u32flag = 0;
		}

		if (u32flag == 0)
		{
			u8p++;
		}
	}

	u8p = u8Str;
	while (*u8p != '\0')
	{
		if (*u8p == '\n')
		{
			*u8p = '\0';
		}

		u8p++;
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
UINT8 *STR_Reverse(UINT8 str[])
{
	char c;
	int i,j = strlen((INT8 *)str) - 1;

	for (i = 0;i < j;i++,j--) {
		c = str[i];
		str[i] = str[j];
		str[j] = c;
	}

	return str;
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:
********************************************************************************/
UINT32 STR_CharPos(UINT8 *pStr, UINT8 u8Ch)
{
	UINT8 *p = pStr;
	UINT8 index = 0,flag = 1;

	while (*p != '\0')
	{
		if (*p != u8Ch) \
		{
			index++;
			p++;
			flag = 0;
		}
		else
		{
			index += 1;
			break;
		}
	}
	
	if (flag == 0)
	{
		index = 0;
	}
	
	return index;
}	

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:
********************************************************************************/
UINT8 *STR_MaxPubSubStr(const UINT8 *str1, const UINT8 *str2, UINT8 maxstr[]) 
{
	UINT32 num, max, len;
	const UINT8 *p, *q, *p1, *q1;
	UINT8 *tmp;

	if (strlen((INT8 *)str1) >= strlen((INT8 *)str2))
	{
		len = strlen((INT8 *)str1);
	}
	else
	{
		len = strlen((INT8 *)str2);
	}
	
	tmp = (UINT8 *)MP_Malloc(sizeof(UINT8) * len + 1);
	
	p = str1; 
	q = str2;
	max = 0;

	while (*p != '\0' && *q != '\0') 
	{
		q1 = q; 
		p1 = str1;

		while (*q1 != '\0' && *p1 != '\0') 
		{
			num = 0;

			while (*p1 == *q1) 
			{
				tmp[num] = *p1;
				p1++; 
				q1++; 
				num++;

				if (num > max) 
				{
					max = num;
					memcpy(maxstr,tmp,max);
				}
			}
			p1 = p1 - num + 1;
			q1 = q;
		}
		
		p++;
		q++;
	}

	maxstr[max] = '\0';
	
	free(tmp);

	return maxstr;
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:
********************************************************************************/
UINT8 *STR_MaxSubStr(const UINT8 *str, UINT8 s[]) 
{
	int len, max;
	const UINT8 *p, *q, *t;
	
	p = str;

	if (p == NULL)
	{
		return NULL;
	}
	
	q = p; 
	max = 0;

	while (*p != '\0')
	{

		len = 0;
		t = p;

		while (*t == *p) 
		{
			p++; 
			len++;
		}

		if (len > max) 
		{
			max = len;
			q = t;
		}
	}

	strcpy((INT8 *)s, (INT8 *)q);
	s[max] = '\0';

	return s;
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:
********************************************************************************/
void STR_NCat(UINT8 *des, const UINT8 *src, int n) 
{
	UINT8 *p1 = des;
	const UINT8 *p2 = src;
	UINT8 i = 0;

	while (*p1 != '\0')
	{
		p1++;
	}

	while (*p2 != '\0' && i < n)
	{
		*p1++ = *p2++;
		i++;
	}

	*p1 = '\0';

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
UINT8 *STR_Cpy(UINT8 *des, const UINT8 *src)
{
	UINT8 *p = des;

	if (des == NULL || src == NULL)
	{
		return NULL ;
	}
	
	while (*src != '\0')
	{
		*des++ = *src++;
	}
	
	*des = '\0';

	return p;
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:
********************************************************************************/
UINT32 STR_NCmp(const UINT8 *des, const UINT8 *src, UINT32 len)
{
	const UINT8 *p = des, *q = src;
	UINT32 flag, i = 0;

	if (len == 0)
	{
		return 0;
	}
	
	if (des == NULL && src == NULL)
	{
		return 0;
	}
	
	if (des == NULL)
	{
		return -1;
	}
	
	if (src == NULL)
	{
		return 1;
	}
	
	do 
	{
		if (i > len) 
		{
			break;
		}
		else
		{
			if (*p > *q) 
			{
				flag = 1;
				break;
			}
			else if (*p < *q)
			{
				flag = -1;
				break;
			} 
			else
			{
				flag = 0;
			}
			
			p++;
			q++;
		}
	}while (*p != '\0' || *q != '\0');

	return flag;
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:
********************************************************************************/
UINT32 STR_Len(const UINT8 *pch)
{
	UINT32 i = 0;

	if (pch == NULL)
	{
		return 0;
	}

	while ( *pch != '\0') 
	{
		pch++;
		i++;
	}

	return i;
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:
********************************************************************************/
UINT8 *STR_NCpy(UINT8 *dest, const UINT8 *source, UINT32 count)
{
	UINT8 *start = dest;

	while (count && (*dest++ = *source++))    /* copy string */
		count--;

	if (count)                              /* pad out with zeroes */
	{
		while (--count)
		{
			*dest++ = '\0';
		}
	}
	
	return(start);
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:press the string,instead the char \r \n \t blank of one blank
********************************************************************************/
UINT8 *STR_ShrinkSpace(UINT8 *dest, const UINT8 *src, UINT32 len)
{
	UINT8 *p = dest;
	const UINT8 *q = src;

	if (len <= 0 || q == NULL)
	{
		return NULL;
	}

	while (*q != '\0') 
	{
		if (*q == ' ' || *q == '\t' || *q == '\n' || *q == '\r') 
		{
			*p++ = ' ';
			q++;
			len--;

			while (*q == ' ' || *q == '\t' || *q == '\n' || *q == '\r') 
			{
				q++;
				len--;
			}
		} 
		else
		{
			*p++ = *q++;
			len--;
		}

		if (len == 0)
		{
			break;
		}
	}

	*p = '\0';

	return dest;
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:
********************************************************************************/
void STR_DeleteChar(UINT8 *str, UINT8 ch)
{
	UINT32 i, j, flag = 0, len = strlen((INT8 *)str);

	for (i = 0; i < len + 1;) 
	{
		flag = 0;

		if (str[i] == ch)
		{
			for (j = i;j < len + 1;j++) 
			{
				str[j] = str[j + 1];
				flag = 1;
			}
		}

		if (flag == 0)
		{
			i++;
		}
	}
}

/******************************************************************************
*
* @brief	:
* @param in	:
* @param out:
* @return 	:
* @note		:
********************************************************************************/
void STR_ShiftLeft(UINT8 *src, UINT32 k)
{
	UINT32 i,j;
	UINT8 ch;

	if (src == NULL || k == 0)
		return;

	for (i = 0; i < k; i++)
	{
		ch = src[0];

		for (j = 0; src[j + 1] != '\0'; j++)
		{
			src[j] = src[j + 1];
		}
		
		src[j] = ch;
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
void STR_ShiftRight(UINT8 *src, UINT32 k)
{
	UINT32 i, j, len;
	UINT8 ch;

	if (src == NULL || k == 0)
	{
		return;
	}
	
	len = strlen((INT8 *)src);

	for (i = 0; i < k; i++)
	{
		ch = src[len - 1];

		for (j = len - 1;j > 0;j--)
		{
			src[j] = src[j - 1];
		}
		
		src[0] = ch;
	}

	return;
}

