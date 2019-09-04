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
typedef  int VARTYPE ;
typedef  int /*<<< orphan*/  VARIANT_BOOL ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  SHORT ;
typedef  int /*<<< orphan*/  SCODE ;
typedef  int /*<<< orphan*/  LONGLONG ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  FLOAT ;
typedef  int /*<<< orphan*/  DOUBLE ;
typedef  int /*<<< orphan*/  DECIMAL ;
typedef  int /*<<< orphan*/  DATE ;
typedef  int /*<<< orphan*/  CY ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int VT_ARRAY ; 
#define  VT_BOOL 152 
#define  VT_BSTR 151 
 int VT_BYREF ; 
#define  VT_CY 150 
#define  VT_DATE 149 
#define  VT_DECIMAL 148 
#define  VT_DISPATCH 147 
#define  VT_EMPTY 146 
#define  VT_ERROR 145 
#define  VT_HRESULT 144 
#define  VT_I1 143 
#define  VT_I2 142 
#define  VT_I4 141 
#define  VT_I8 140 
#define  VT_INT 139 
#define  VT_NULL 138 
#define  VT_R4 137 
#define  VT_R8 136 
#define  VT_RECORD 135 
#define  VT_UI1 134 
#define  VT_UI2 133 
#define  VT_UI4 132 
#define  VT_UI8 131 
#define  VT_UINT 130 
#define  VT_UNKNOWN 129 
#define  VT_VARIANT 128 

unsigned int get_type_size(ULONG *pFlags, VARTYPE vt)
{
    if (vt & VT_ARRAY) return 4;

    switch (vt & ~VT_BYREF) {
    case VT_EMPTY:
    case VT_NULL:
        return 0;
    case VT_I1:
    case VT_UI1:
        return sizeof(CHAR);
    case VT_I2:
    case VT_UI2:
        return sizeof(SHORT);
    case VT_I4:
    case VT_UI4:
    case VT_HRESULT:
        return sizeof(LONG);
    case VT_INT:
    case VT_UINT:
        return sizeof(INT);
    case VT_I8:
    case VT_UI8:
        return sizeof(LONGLONG);
    case VT_R4:
        return sizeof(FLOAT);
    case VT_R8:
        return sizeof(DOUBLE);
    case VT_BOOL:
        return sizeof(VARIANT_BOOL);
    case VT_ERROR:
        return sizeof(SCODE);
    case VT_DATE:
        return sizeof(DATE);
    case VT_CY:
        return sizeof(CY);
    case VT_DECIMAL:
        return sizeof(DECIMAL);
    case VT_BSTR:
        return sizeof(ULONG);
    case VT_VARIANT:
        return sizeof(VARIANT);
    case VT_UNKNOWN:
    case VT_DISPATCH:
    case VT_RECORD:
        return 0;
    default:
        FIXME("unhandled VT %d\n", vt);
        return 0;
    }
}