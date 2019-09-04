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
typedef  int /*<<< orphan*/  vbdisp_t ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
#define  VT_BOOL 131 
#define  VT_I2 130 
#define  VT_I4 129 
#define  VT_R8 128 
 double V_R8 (int /*<<< orphan*/ *) ; 
 int V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_variant (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  return_double (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round (double) ; 
 int /*<<< orphan*/  to_double (int /*<<< orphan*/ *,double*) ; 

__attribute__((used)) static HRESULT Global_Round(vbdisp_t *This, VARIANT *arg, unsigned args_cnt, VARIANT *res)
{
    double n;
    HRESULT hres;

    TRACE("%s\n", debugstr_variant(arg));

    if(!res)
        return S_OK;

    switch(V_VT(arg)) {
    case VT_I2:
    case VT_I4:
    case VT_BOOL:
        *res = *arg;
        return S_OK;
    case VT_R8:
        n = V_R8(arg);
        break;
    default:
        hres = to_double(arg, &n);
        if(FAILED(hres))
            return hres;
    }

    return return_double(res, round(n));
}