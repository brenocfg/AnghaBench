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
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKE_VBSERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VBSE_ILLEGAL_NULL_USE ; 
 scalar_t__ VT_NULL ; 
 scalar_t__ V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  debugstr_variant (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  return_short (int /*<<< orphan*/ *,short) ; 
 int /*<<< orphan*/  to_double (int /*<<< orphan*/ *,double*) ; 

__attribute__((used)) static HRESULT Global_Sgn(vbdisp_t *This, VARIANT *arg, unsigned args_cnt, VARIANT *res)
{
    double v;
    short val;
    HRESULT hres;

    TRACE("(%s)\n", debugstr_variant(arg));

    assert(args_cnt == 1);

    if(V_VT(arg) == VT_NULL)
        return MAKE_VBSERROR(VBSE_ILLEGAL_NULL_USE);

    hres = to_double(arg, &v);
    if (FAILED(hres))
        return hres;

    val = v == 0 ? 0 : (v > 0 ? 1 : -1);
    return return_short(res, val);
}