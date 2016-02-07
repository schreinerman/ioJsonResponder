//
//  ioJsonResponder.h
//  ioJsonResponder
//
//  Created by Manuel Schreiner on 07.02.16.
//  Copyright © 2016 io-expert.com. All rights reserved.
//

#ifndef ioJsonResponder_h
#define ioJsonResponder_h

#include <stdio.h>
#include "base_types.h"

typedef enum en_iojsonresponder_variable_type
{
    enIoJsonResponderVarInt,
    enIoJsonResponderVarInt8,
    enIoJsonResponderVarInt16,
    enIoJsonResponderVarInt32,
    enIoJsonResponderVarInt64,
    enIoJsonResponderVarUInt8,
    enIoJsonResponderVarUInt16,
    enIoJsonResponderVarUInt32,
    enIoJsonResponderVarUInt64,
    enIoJsonResponderVarString,
    enIoJsonResponderVarFloat,
    enIoJsonResponderVarFloat32,
    enIoJsonResponderVarFloat64,
    enIoJsonResponderVarBoolean,
} en_iojsonresponder_variable_type_t;

struct stc_iojsonresponder_item;

typedef struct stc_iojsonresponder_item
{
    char_t* pcIdentifier;
    void* pVariable;
    en_iojsonresponder_variable_type_t enVariableType;
    uint8_t u8Size;
    struct stc_iojsonresponder_item* pstcNextItem;
} stc_iojsonresponder_item_t;

typedef struct stc_iojsonresponder_handle
{
    stc_iojsonresponder_item_t* pstcRoot;
} stc_iojsonresponder_handle_t;

void IoJsonResponder_Init(stc_iojsonresponder_handle_t* pstcHandle);
void IoJsonResponder_AddVariables(stc_iojsonresponder_handle_t* pstcHandle, stc_iojsonresponder_item_t astcJsonItems[],uint8_t u8Count);
void IoJsonResponder_GetJsonString(stc_iojsonresponder_handle_t* pstcHandle, char_t* pcStringBuffer, uint32_t u32MaxLen);

#endif /* ioJsonResponder_h */
