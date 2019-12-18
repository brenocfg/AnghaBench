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
typedef  int /*<<< orphan*/  type_t ;

/* Variables and functions */
#define  VT_BOOL 154 
#define  VT_BSTR 153 
#define  VT_CY 152 
#define  VT_DATE 151 
#define  VT_DECIMAL 150 
#define  VT_DISPATCH 149 
#define  VT_ERROR 148 
#define  VT_HRESULT 147 
#define  VT_I1 146 
#define  VT_I2 145 
#define  VT_I4 144 
#define  VT_I8 143 
#define  VT_INT 142 
#define  VT_LPSTR 141 
#define  VT_LPWSTR 140 
#define  VT_PTR 139 
#define  VT_R4 138 
#define  VT_R8 137 
#define  VT_UI1 136 
#define  VT_UI2 135 
#define  VT_UI4 134 
#define  VT_UI8 133 
#define  VT_UINT 132 
#define  VT_UNKNOWN 131 
#define  VT_USERDEFINED 130 
#define  VT_VARIANT 129 
#define  VT_VOID 128 
 int /*<<< orphan*/  error (char*,int) ; 
 int get_type_vt (int /*<<< orphan*/ *) ; 
 int pointer_size ; 

__attribute__((used)) static int get_element_size(type_t *type)
{
    int vt = get_type_vt(type);

    switch (vt)
    {
    case VT_I1:
    case VT_UI1:
        return 1;

    case VT_INT:
    case VT_UINT:
        return /* typelib_kind == SYS_WIN16 ? 2 : */ 4;

    case VT_UI2:
    case VT_I2:
    case VT_BOOL:
        return 2;

    case VT_I4:
    case VT_UI4:
    case VT_R4:
    case VT_ERROR:
    case VT_HRESULT:
        return 4;

    case VT_R8:
    case VT_I8:
    case VT_UI8:
    case VT_CY:
    case VT_DATE:
        return 8;

    case VT_DECIMAL:
        return 16;

    case VT_PTR:
    case VT_UNKNOWN:
    case VT_DISPATCH:
    case VT_BSTR:
    case VT_LPSTR:
    case VT_LPWSTR:
        return pointer_size;

    case VT_VOID:
        return 0;

    case VT_VARIANT:
        return pointer_size == 8 ? 24 : 16;

    case VT_USERDEFINED:
        return 0;

    default:
        error("get_element_size: unrecognized vt %d\n", vt);
        break;
    }

    return 0;
}