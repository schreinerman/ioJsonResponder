//
//  ioJsonResponder.c
//  ioJsonResponder
//
//  Created by Manuel Schreiner on 07.02.16.
//  Copyright © 2016 io-expert.com. All rights reserved.
//
// 1. Redistributions of source code must retain the above copyright notice,
//    this condition and the following disclaimer.
//
// This software is provided by the copyright holder and contributors "AS IS"
// and any warranties related to this software are DISCLAIMED.
// The copyright owner or contributors be NOT LIABLE for any damages caused
// by use of this software.

#include "ioJsonResponder.h"
#include <string.h>
static stc_iojsonresponder_item_t* pstcRoot = NULL;


/**
	Init IoJsonResponder
	@param pstcHandle       Has to be NULL for default handle or has to reference to a handle
 */
void IoJsonResponder_Init(stc_iojsonresponder_handle_t* pstcHandle)

{
    if (pstcHandle != NULL)
    {
        pstcHandle->pstcRoot = NULL;
    }
}


/**
	Adds a list of variables
	@param pstcHandle       Has to be NULL for default handle or has to reference to a handle
	@param astcJsonItems    List of JSON variables
	@param u8Count          Number of variables (list size)
 */
void IoJsonResponder_AddVariables(stc_iojsonresponder_handle_t* pstcHandle, stc_iojsonresponder_item_t astcJsonItems[],uint8_t u8Count)
{
    uint8_t i;
    stc_iojsonresponder_item_t* _pstcRoot;
    stc_iojsonresponder_item_t* pLastItem;
    
    if (pstcHandle == NULL)
    {
        _pstcRoot = pstcRoot;
    }
    else
    {
        _pstcRoot = pstcHandle->pstcRoot;
    }
    pLastItem = _pstcRoot;
    
    if (_pstcRoot != NULL)
    {
        while(pLastItem->pstcNextItem != NULL)
        {
            pLastItem = pLastItem->pstcNextItem;
        }
    }
    for(i = 0;i <u8Count;i++)
    {
        if (_pstcRoot == NULL)
        {
            if (pstcHandle == NULL)
            {
                pstcRoot = &astcJsonItems[i];;
            }
            else
            {
                pstcHandle->pstcRoot = &astcJsonItems[i];;
            }
            _pstcRoot = &astcJsonItems[i];
            pLastItem = _pstcRoot;
            astcJsonItems[i].pstcNextItem = NULL;
        }
        else
        {
            pLastItem->pstcNextItem = &astcJsonItems[i];
            pLastItem = pLastItem->pstcNextItem;
        }
    }
}


/**
	<#Description#>
	@param pstcHandle       Has to be NULL for default handle or has to reference to a handle
	@param pcStringBuffer   Buffer to return the JSON string
	@param u32MaxLen        Maximum length of the buffer
 */
void IoJsonResponder_GetJsonString(stc_iojsonresponder_handle_t* pstcHandle, char_t* pcStringBuffer, uint32_t u32MaxLen)
{
    int tmp = 0;
    int l = 0;
    stc_iojsonresponder_item_t* pstcCurrent;
    if (pstcHandle == NULL)
    {
        pstcCurrent = pstcRoot;
    }
    else
    {
        pstcCurrent = pstcHandle->pstcRoot;
    }
    memset(pcStringBuffer,0,u32MaxLen);
    tmp = sprintf(pcStringBuffer,"{");
    l += tmp;
    pcStringBuffer += tmp;
    while((pstcCurrent != NULL) && (u32MaxLen - l) > 32)
    {
        tmp = sprintf(pcStringBuffer,"\"%s\":",pstcCurrent->pcIdentifier);
        l += tmp;
        pcStringBuffer += tmp;
        switch(pstcCurrent->enVariableType)
        {
            
            case enIoJsonResponderVarInt:
                tmp = sprintf(pcStringBuffer,"\"%d\"",*((int*)(pstcCurrent->pVariable)));
                break;
            case enIoJsonResponderVarInt8:
                tmp = sprintf(pcStringBuffer,"\"%d\"",*((int8_t*)(pstcCurrent->pVariable)));
                break;
            case enIoJsonResponderVarInt16:
                tmp = sprintf(pcStringBuffer,"\"%d\"",*((int16_t*)(pstcCurrent->pVariable)));
                break;
            case enIoJsonResponderVarInt32:
                tmp = sprintf(pcStringBuffer,"\"%d\"",*((int32_t*)(pstcCurrent->pVariable)));
                break;
            case enIoJsonResponderVarInt64:
                tmp = sprintf(pcStringBuffer,"\"%d\"",*((int32_t*)(pstcCurrent->pVariable)));
                break;
            case enIoJsonResponderVarUInt8:
                tmp = sprintf(pcStringBuffer,"\"%d\"",*((uint8_t*)(pstcCurrent->pVariable)));
                break;
            case enIoJsonResponderVarUInt16:
                tmp = sprintf(pcStringBuffer,"\"%d\"",*((uint16_t*)(pstcCurrent->pVariable)));
                break;
            case enIoJsonResponderVarUInt32:
                tmp = sprintf(pcStringBuffer,"\"%d\"",*((uint16_t*)(pstcCurrent->pVariable)));
                break;
            case enIoJsonResponderVarUInt64:
                tmp = sprintf(pcStringBuffer,"\"%d\"",*((uint32_t*)(pstcCurrent->pVariable)));
                break;
            case enIoJsonResponderVarBoolean:
                tmp = sprintf(pcStringBuffer,"\"%d\"",*((boolean_t*)(pstcCurrent->pVariable)));
                break;
            case enIoJsonResponderVarString:
                tmp = sprintf(pcStringBuffer,"\"%s\"",*((char_t**)(pstcCurrent->pVariable)));
                break;
            case enIoJsonResponderVarFloat:
                tmp = sprintf(pcStringBuffer,"\"%f\"",*((float*)(pstcCurrent->pVariable)));
                break;
            case enIoJsonResponderVarFloat32:
                tmp = sprintf(pcStringBuffer,"\"%f\"",*((float32_t*)(pstcCurrent->pVariable)));
                break;
            case enIoJsonResponderVarFloat64:
                tmp = sprintf(pcStringBuffer,"\"%f\"",*((float64_t*)(pstcCurrent->pVariable)));
                break;
        }
        pcStringBuffer += tmp;
        l += tmp;
        tmp = sprintf(pcStringBuffer,",");
        pcStringBuffer += tmp;
        l += tmp;

        pstcCurrent = pstcCurrent->pstcNextItem;
    }
    pcStringBuffer--;
    *pcStringBuffer = '\0';
    l--;
    tmp = sprintf(pcStringBuffer,"}");
    pcStringBuffer += tmp;
    l += tmp;
}