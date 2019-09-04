#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int DWORD ;

/* Variables and functions */
#define  SymTagAnnotation 158 
#define  SymTagArrayType 157 
#define  SymTagBaseClass 156 
#define  SymTagBaseType 155 
#define  SymTagBlock 154 
#define  SymTagCompiland 153 
#define  SymTagCompilandDetails 152 
#define  SymTagCompilandEnv 151 
#define  SymTagCustom 150 
#define  SymTagCustomType 149 
#define  SymTagData 148 
#define  SymTagDimension 147 
#define  SymTagEnum 146 
#define  SymTagExe 145 
#define  SymTagFriend 144 
#define  SymTagFuncDebugEnd 143 
#define  SymTagFuncDebugStart 142 
#define  SymTagFunction 141 
#define  SymTagFunctionArgType 140 
#define  SymTagFunctionType 139 
#define  SymTagLabel 138 
#define  SymTagManagedType 137 
#define  SymTagNull 136 
#define  SymTagPointerType 135 
#define  SymTagPublicSymbol 134 
#define  SymTagThunk 133 
#define  SymTagTypedef 132 
#define  SymTagUDT 131 
#define  SymTagUsingNamespace 130 
#define  SymTagVTable 129 
#define  SymTagVTableShape 128 

__attribute__((used)) static const char* symt_get_tag_str(DWORD tag)
{
    switch (tag)
    {
    case SymTagNull:                    return "SymTagNull";
    case SymTagExe:                     return "SymTagExe";
    case SymTagCompiland:               return "SymTagCompiland";
    case SymTagCompilandDetails:        return "SymTagCompilandDetails";
    case SymTagCompilandEnv:            return "SymTagCompilandEnv";
    case SymTagFunction:                return "SymTagFunction";
    case SymTagBlock:                   return "SymTagBlock";
    case SymTagData:                    return "SymTagData";
    case SymTagAnnotation:              return "SymTagAnnotation";
    case SymTagLabel:                   return "SymTagLabel";
    case SymTagPublicSymbol:            return "SymTagPublicSymbol";
    case SymTagUDT:                     return "SymTagUDT";
    case SymTagEnum:                    return "SymTagEnum";
    case SymTagFunctionType:            return "SymTagFunctionType";
    case SymTagPointerType:             return "SymTagPointerType";
    case SymTagArrayType:               return "SymTagArrayType";
    case SymTagBaseType:                return "SymTagBaseType";
    case SymTagTypedef:                 return "SymTagTypedef,";
    case SymTagBaseClass:               return "SymTagBaseClass";
    case SymTagFriend:                  return "SymTagFriend";
    case SymTagFunctionArgType:         return "SymTagFunctionArgType,";
    case SymTagFuncDebugStart:          return "SymTagFuncDebugStart,";
    case SymTagFuncDebugEnd:            return "SymTagFuncDebugEnd";
    case SymTagUsingNamespace:          return "SymTagUsingNamespace,";
    case SymTagVTableShape:             return "SymTagVTableShape";
    case SymTagVTable:                  return "SymTagVTable";
    case SymTagCustom:                  return "SymTagCustom";
    case SymTagThunk:                   return "SymTagThunk";
    case SymTagCustomType:              return "SymTagCustomType";
    case SymTagManagedType:             return "SymTagManagedType";
    case SymTagDimension:               return "SymTagDimension";
    default:                            return "---";
    }
}