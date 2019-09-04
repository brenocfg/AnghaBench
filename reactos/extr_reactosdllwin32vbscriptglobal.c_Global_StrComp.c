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
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  debugstr_variant (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  return_short (int /*<<< orphan*/ *,short) ; 
 int strcmpW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strcmpiW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_int (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  to_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT Global_StrComp(vbdisp_t *This, VARIANT *args, unsigned args_cnt, VARIANT *res)
{
    BSTR left, right;
    int mode, ret;
    HRESULT hres;
    short val;

    TRACE("(%s %s ...)\n", debugstr_variant(args), debugstr_variant(args+1));

    assert(args_cnt == 2 || args_cnt == 3);

    if (args_cnt == 3) {
        hres = to_int(args+2, &mode);
        if(FAILED(hres))
            return hres;

        if (mode != 0 && mode != 1) {
            FIXME("unknown compare mode = %d\n", mode);
            return E_FAIL;
        }
    }
    else
        mode = 0;

    hres = to_string(args, &left);
    if(FAILED(hres))
        return hres;

    hres = to_string(args+1, &right);
    if(FAILED(hres))
    {
        SysFreeString(left);
        return hres;
    }

    ret = mode ? strcmpiW(left, right) : strcmpW(left, right);
    val = ret < 0 ? -1 : (ret > 0 ? 1 : 0);

    SysFreeString(left);
    SysFreeString(right);
    return return_short(res, val);
}