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
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysStringLen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ VT_BSTR ; 
 scalar_t__ VT_NULL ; 
 int /*<<< orphan*/  V_BSTR (int /*<<< orphan*/ *) ; 
 scalar_t__ V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_variant (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  return_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_null (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT Global_Len(vbdisp_t *This, VARIANT *arg, unsigned args_cnt, VARIANT *res)
{
    DWORD len;
    HRESULT hres;

    TRACE("%s\n", debugstr_variant(arg));

    if(V_VT(arg) == VT_NULL)
        return return_null(res);

    if(V_VT(arg) != VT_BSTR) {
        BSTR str;

        hres = to_string(arg, &str);
        if(FAILED(hres))
            return hres;

        len = SysStringLen(str);
        SysFreeString(str);
    }else {
        len = SysStringLen(V_BSTR(arg));
    }

    return return_int(res, len);
}