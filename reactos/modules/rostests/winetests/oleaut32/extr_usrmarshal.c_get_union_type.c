#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int VARTYPE ;
typedef  int /*<<< orphan*/  UINT_PTR ;
struct TYPE_4__ {int fFeatures; int cbElements; } ;
typedef  int /*<<< orphan*/  SF_TYPE ;
typedef  TYPE_1__ SAFEARRAY ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int FADF_HAVEIID ; 
 int FADF_VARIANT ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SF_BSTR ; 
 int /*<<< orphan*/  SF_DISPATCH ; 
 int /*<<< orphan*/  SF_ERROR ; 
 int /*<<< orphan*/  SF_HAVEIID ; 
 int /*<<< orphan*/  SF_I1 ; 
 int /*<<< orphan*/  SF_I2 ; 
 int /*<<< orphan*/  SF_I4 ; 
 int /*<<< orphan*/  SF_I8 ; 
 int /*<<< orphan*/  SF_RECORD ; 
 int /*<<< orphan*/  SF_UNKNOWN ; 
 int /*<<< orphan*/  SF_VARIANT ; 
#define  VT_BOOL 149 
#define  VT_BSTR 148 
#define  VT_CY 147 
#define  VT_DATE 146 
#define  VT_DISPATCH 145 
#define  VT_I1 144 
#define  VT_I2 143 
#define  VT_I4 142 
#define  VT_I8 141 
#define  VT_INT 140 
#define  VT_INT_PTR 139 
#define  VT_R4 138 
#define  VT_R8 137 
#define  VT_RECORD 136 
#define  VT_UI1 135 
#define  VT_UI2 134 
#define  VT_UI4 133 
#define  VT_UI8 132 
#define  VT_UINT 131 
#define  VT_UINT_PTR 130 
#define  VT_UNKNOWN 129 
#define  VT_VARIANT 128 
 int /*<<< orphan*/  pSafeArrayGetVartype (TYPE_1__*,int*) ; 

__attribute__((used)) static inline SF_TYPE get_union_type(SAFEARRAY *psa)
{
    VARTYPE vt;
    HRESULT hr;

    hr = pSafeArrayGetVartype(psa, &vt);
    if (FAILED(hr))
    {
        if(psa->fFeatures & FADF_VARIANT) return SF_VARIANT;

        switch(psa->cbElements)
        {
        case 1: vt = VT_I1; break;
        case 2: vt = VT_I2; break;
        case 4: vt = VT_I4; break;
        case 8: vt = VT_I8; break;
        default: return 0;
        }
    }

    if (psa->fFeatures & FADF_HAVEIID)
        return SF_HAVEIID;

    switch (vt)
    {
    case VT_I1:
    case VT_UI1:      return SF_I1;
    case VT_BOOL:
    case VT_I2:
    case VT_UI2:      return SF_I2;
    case VT_INT:
    case VT_UINT:
    case VT_I4:
    case VT_UI4:
    case VT_R4:       return SF_I4;
    case VT_DATE:
    case VT_CY:
    case VT_R8:
    case VT_I8:
    case VT_UI8:      return SF_I8;
    case VT_INT_PTR:
    case VT_UINT_PTR: return (sizeof(UINT_PTR) == 4 ? SF_I4 : SF_I8);
    case VT_BSTR:     return SF_BSTR;
    case VT_DISPATCH: return SF_DISPATCH;
    case VT_VARIANT:  return SF_VARIANT;
    case VT_UNKNOWN:  return SF_UNKNOWN;
    /* Note: Return a non-zero size to indicate vt is valid. The actual size
     * of a UDT is taken from the result of IRecordInfo_GetSize().
     */
    case VT_RECORD:   return SF_RECORD;
    default:          return SF_ERROR;
    }
}