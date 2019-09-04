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
 size_t ARRAY_SIZE (char const**) ; 
#define  VT_ARRAY 176 
#define  VT_BLOB 175 
#define  VT_BLOB_OBJECT 174 
#define  VT_BOOL 173 
#define  VT_BSTR 172 
#define  VT_BYREF 171 
#define  VT_CARRAY 170 
#define  VT_CF 169 
#define  VT_CLSID 168 
#define  VT_CY 167 
#define  VT_DATE 166 
#define  VT_DECIMAL 165 
#define  VT_DISPATCH 164 
#define  VT_EMPTY 163 
#define  VT_ERROR 162 
#define  VT_FILETIME 161 
#define  VT_HRESULT 160 
#define  VT_I1 159 
#define  VT_I2 158 
#define  VT_I4 157 
#define  VT_I8 156 
#define  VT_ILLEGAL 155 
#define  VT_INT 154 
#define  VT_INT_PTR 153 
#define  VT_LPSTR 152 
#define  VT_LPWSTR 151 
#define  VT_NULL 150 
#define  VT_PTR 149 
#define  VT_R4 148 
#define  VT_R8 147 
#define  VT_RECORD 146 
#define  VT_RESERVED 145 
#define  VT_SAFEARRAY 144 
#define  VT_STORAGE 143 
#define  VT_STORED_OBJECT 142 
#define  VT_STREAM 141 
#define  VT_STREAMED_OBJECT 140 
#define  VT_UI1 139 
#define  VT_UI2 138 
#define  VT_UI4 137 
#define  VT_UI8 136 
#define  VT_UINT 135 
#define  VT_UINT_PTR 134 
#define  VT_UNKNOWN 133 
#define  VT_USERDEFINED 132 
#define  VT_VARIANT 131 
#define  VT_VECTOR 130 
#define  VT_VERSIONED_STREAM 129 
#define  VT_VOID 128 
 int /*<<< orphan*/  sprintf (char const*,char*,int) ; 
 char const** vtstr_buffer ; 
 size_t vtstr_current ; 

__attribute__((used)) static const char *vtstr(int x)
{
    switch(x) {
#define CASE(vt) case VT_##vt: return #vt
    CASE(EMPTY);
    CASE(NULL);
    CASE(I2);
    CASE(I4);
    CASE(R4);
    CASE(R8);
    CASE(CY);
    CASE(DATE);
    CASE(BSTR);
    CASE(DISPATCH);
    CASE(ERROR);
    CASE(BOOL);
    CASE(VARIANT);
    CASE(UNKNOWN);
    CASE(DECIMAL);
    CASE(I1);
    CASE(UI1);
    CASE(UI2);
    CASE(UI4);
    CASE(I8);
    CASE(UI8);
    CASE(INT);
    CASE(UINT);
    CASE(VOID);
    CASE(HRESULT);
    CASE(PTR);
    CASE(SAFEARRAY);
    CASE(CARRAY);
    CASE(USERDEFINED);
    CASE(LPSTR);
    CASE(LPWSTR);
    CASE(RECORD);
    CASE(INT_PTR);
    CASE(UINT_PTR);
    CASE(FILETIME);
    CASE(BLOB);
    CASE(STREAM);
    CASE(STORAGE);
    CASE(STREAMED_OBJECT);
    CASE(STORED_OBJECT);
    CASE(BLOB_OBJECT);
    CASE(CF);
    CASE(CLSID);
    CASE(VERSIONED_STREAM);
    CASE(VECTOR);
    CASE(ARRAY);
    CASE(BYREF);
    CASE(RESERVED);
    CASE(ILLEGAL);
#undef CASE

    case 0xfff:
        return "VT_BSTR_BLOB/VT_ILLEGALMASKED/VT_TYPEMASK";

    default:
        vtstr_current %= ARRAY_SIZE(vtstr_buffer);
        sprintf(vtstr_buffer[vtstr_current], "unknown variant type %d", x);
        return vtstr_buffer[vtstr_current++];
    }
}