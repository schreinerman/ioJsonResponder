//
//  main.c
//  ioJsonResponder
//
//  Created by Manuel Schreiner on 07.02.16.
//  Copyright © 2016 io-expert.com. All rights reserved.
//

#include <stdio.h>
#include "ioJsonResponder.h"

uint8_t u8A = 8;
int8_t i8B = -4;
float32_t f32C = 3.14f;
const char_t* str = "Hello, World!\n";

stc_iojsonresponder_item_t astcJsonVars[] = {
    {"A",&u8A,enIoJsonResponderVarUInt8,1},
    {"B",&i8B,enIoJsonResponderVarInt8,1},
    {"C",&f32C,enIoJsonResponderVarFloat32,1},
    {"str",&str,enIoJsonResponderVarString,1},
};

char_t acJString[150];

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    IoJsonResponder_Init(NULL);
    IoJsonResponder_AddVariables(NULL,astcJsonVars,4);
    IoJsonResponder_GetJsonString(NULL,&acJString[0],sizeof(acJString));
    printf(acJString);
    return 0;
}
