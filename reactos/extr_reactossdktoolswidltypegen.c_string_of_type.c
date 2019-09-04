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

/* Variables and functions */
#define  FC_ADD_1 207 
#define  FC_ALIGNM2 206 
#define  FC_ALIGNM4 205 
#define  FC_ALIGNM8 204 
#define  FC_AUTO_HANDLE 203 
#define  FC_BIND_CONTEXT 202 
#define  FC_BIND_GENERIC 201 
#define  FC_BIND_PRIMITIVE 200 
#define  FC_BOGUS_ARRAY 199 
#define  FC_BOGUS_STRUCT 198 
#define  FC_BYTE 197 
#define  FC_BYTE_COUNT_POINTER 196 
#define  FC_CALLBACK 195 
#define  FC_CALLBACK_HANDLE 194 
#define  FC_CARRAY 193 
#define  FC_CHAR 192 
#define  FC_CONSTANT_IID 191 
#define  FC_CPSTRUCT 190 
#define  FC_CSTRING 189 
#define  FC_CSTRUCT 188 
#define  FC_CVARRAY 187 
#define  FC_CVSTRUCT 186 
#define  FC_C_CSTRING 185 
#define  FC_C_WSTRING 184 
#define  FC_DEREFERENCE 183 
#define  FC_DIV_2 182 
#define  FC_DOUBLE 181 
#define  FC_EMBEDDED_COMPLEX 180 
#define  FC_ENCAPSULATED_UNION 179 
#define  FC_END 178 
#define  FC_ENUM16 177 
#define  FC_ENUM32 176 
#define  FC_ERROR_STATUS_T 175 
#define  FC_FIXED_OFFSET 174 
#define  FC_FIXED_REPEAT 173 
#define  FC_FLOAT 172 
#define  FC_FP 171 
#define  FC_HYPER 170 
#define  FC_IGNORE 169 
#define  FC_INT3264 168 
#define  FC_IP 167 
#define  FC_LGFARRAY 166 
#define  FC_LGVARRAY 165 
#define  FC_LONG 164 
#define  FC_MULT_2 163 
#define  FC_NON_ENCAPSULATED_UNION 162 
#define  FC_NO_REPEAT 161 
#define  FC_OP 160 
#define  FC_PAD 159 
#define  FC_POINTER 158 
#define  FC_PP 157 
#define  FC_PSTRUCT 156 
#define  FC_RANGE 155 
#define  FC_REPRESENT_AS 154 
#define  FC_RP 153 
#define  FC_SHORT 152 
#define  FC_SMALL 151 
#define  FC_SMFARRAY 150 
#define  FC_SMVARRAY 149 
#define  FC_STRING_SIZED 148 
#define  FC_STRUCT 147 
#define  FC_STRUCTPAD1 146 
#define  FC_STRUCTPAD2 145 
#define  FC_STRUCTPAD3 144 
#define  FC_STRUCTPAD4 143 
#define  FC_STRUCTPAD5 142 
#define  FC_STRUCTPAD6 141 
#define  FC_STRUCTPAD7 140 
#define  FC_SUB_1 139 
#define  FC_TRANSMIT_AS 138 
#define  FC_UINT3264 137 
#define  FC_ULONG 136 
#define  FC_UP 135 
#define  FC_USER_MARSHAL 134 
#define  FC_USHORT 133 
#define  FC_USMALL 132 
#define  FC_VARIABLE_OFFSET 131 
#define  FC_VARIABLE_REPEAT 130 
#define  FC_WCHAR 129 
#define  FC_WSTRING 128 
 int /*<<< orphan*/  error (char*,unsigned char) ; 

__attribute__((used)) static const char *string_of_type(unsigned char type)
{
    switch (type)
    {
    case FC_BYTE: return "FC_BYTE";
    case FC_CHAR: return "FC_CHAR";
    case FC_SMALL: return "FC_SMALL";
    case FC_USMALL: return "FC_USMALL";
    case FC_WCHAR: return "FC_WCHAR";
    case FC_SHORT: return "FC_SHORT";
    case FC_USHORT: return "FC_USHORT";
    case FC_LONG: return "FC_LONG";
    case FC_ULONG: return "FC_ULONG";
    case FC_FLOAT: return "FC_FLOAT";
    case FC_HYPER: return "FC_HYPER";
    case FC_DOUBLE: return "FC_DOUBLE";
    case FC_ENUM16: return "FC_ENUM16";
    case FC_ENUM32: return "FC_ENUM32";
    case FC_IGNORE: return "FC_IGNORE";
    case FC_ERROR_STATUS_T: return "FC_ERROR_STATUS_T";
    case FC_RP: return "FC_RP";
    case FC_UP: return "FC_UP";
    case FC_OP: return "FC_OP";
    case FC_FP: return "FC_FP";
    case FC_ENCAPSULATED_UNION: return "FC_ENCAPSULATED_UNION";
    case FC_NON_ENCAPSULATED_UNION: return "FC_NON_ENCAPSULATED_UNION";
    case FC_STRUCT: return "FC_STRUCT";
    case FC_PSTRUCT: return "FC_PSTRUCT";
    case FC_CSTRUCT: return "FC_CSTRUCT";
    case FC_CPSTRUCT: return "FC_CPSTRUCT";
    case FC_CVSTRUCT: return "FC_CVSTRUCT";
    case FC_BOGUS_STRUCT: return "FC_BOGUS_STRUCT";
    case FC_SMFARRAY: return "FC_SMFARRAY";
    case FC_LGFARRAY: return "FC_LGFARRAY";
    case FC_SMVARRAY: return "FC_SMVARRAY";
    case FC_LGVARRAY: return "FC_LGVARRAY";
    case FC_CARRAY: return "FC_CARRAY";
    case FC_CVARRAY: return "FC_CVARRAY";
    case FC_BOGUS_ARRAY: return "FC_BOGUS_ARRAY";
    case FC_ALIGNM2: return "FC_ALIGNM2";
    case FC_ALIGNM4: return "FC_ALIGNM4";
    case FC_ALIGNM8: return "FC_ALIGNM8";
    case FC_POINTER: return "FC_POINTER";
    case FC_C_CSTRING: return "FC_C_CSTRING";
    case FC_C_WSTRING: return "FC_C_WSTRING";
    case FC_CSTRING: return "FC_CSTRING";
    case FC_WSTRING: return "FC_WSTRING";
    case FC_BYTE_COUNT_POINTER: return "FC_BYTE_COUNT_POINTER";
    case FC_TRANSMIT_AS: return "FC_TRANSMIT_AS";
    case FC_REPRESENT_AS: return "FC_REPRESENT_AS";
    case FC_IP: return "FC_IP";
    case FC_BIND_CONTEXT: return "FC_BIND_CONTEXT";
    case FC_BIND_GENERIC: return "FC_BIND_GENERIC";
    case FC_BIND_PRIMITIVE: return "FC_BIND_PRIMITIVE";
    case FC_AUTO_HANDLE: return "FC_AUTO_HANDLE";
    case FC_CALLBACK_HANDLE: return "FC_CALLBACK_HANDLE";
    case FC_STRUCTPAD1: return "FC_STRUCTPAD1";
    case FC_STRUCTPAD2: return "FC_STRUCTPAD2";
    case FC_STRUCTPAD3: return "FC_STRUCTPAD3";
    case FC_STRUCTPAD4: return "FC_STRUCTPAD4";
    case FC_STRUCTPAD5: return "FC_STRUCTPAD5";
    case FC_STRUCTPAD6: return "FC_STRUCTPAD6";
    case FC_STRUCTPAD7: return "FC_STRUCTPAD7";
    case FC_STRING_SIZED: return "FC_STRING_SIZED";
    case FC_NO_REPEAT: return "FC_NO_REPEAT";
    case FC_FIXED_REPEAT: return "FC_FIXED_REPEAT";
    case FC_VARIABLE_REPEAT: return "FC_VARIABLE_REPEAT";
    case FC_FIXED_OFFSET: return "FC_FIXED_OFFSET";
    case FC_VARIABLE_OFFSET: return "FC_VARIABLE_OFFSET";
    case FC_PP: return "FC_PP";
    case FC_EMBEDDED_COMPLEX: return "FC_EMBEDDED_COMPLEX";
    case FC_DEREFERENCE: return "FC_DEREFERENCE";
    case FC_DIV_2: return "FC_DIV_2";
    case FC_MULT_2: return "FC_MULT_2";
    case FC_ADD_1: return "FC_ADD_1";
    case FC_SUB_1: return "FC_SUB_1";
    case FC_CALLBACK: return "FC_CALLBACK";
    case FC_CONSTANT_IID: return "FC_CONSTANT_IID";
    case FC_END: return "FC_END";
    case FC_PAD: return "FC_PAD";
    case FC_USER_MARSHAL: return "FC_USER_MARSHAL";
    case FC_RANGE: return "FC_RANGE";
    case FC_INT3264: return "FC_INT3264";
    case FC_UINT3264: return "FC_UINT3264";
    default:
        error("string_of_type: unknown type 0x%02x\n", type);
        return NULL;
    }
}