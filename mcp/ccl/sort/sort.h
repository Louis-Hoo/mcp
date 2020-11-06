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

#ifndef _XXXXXXX_H
#define _XXXXXXX_H

/******************************************************************************
*
* Code Segment: Macro define
*
*******************************************************************************/
#define min(a,b) ((a) < (b) ? (a) : (b))

#define max(a,b) ((a) > (b) ? (a) : (b))

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
UINT32 SORT_BinSearch(UINT32 v[], UINT32 n, UINT32 x);

void SORT_Insert(UINT32 a[], UINT32 len);

#endif
