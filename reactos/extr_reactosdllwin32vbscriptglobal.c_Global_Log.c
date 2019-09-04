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
 int /*<<< orphan*/  VBSE_ILLEGAL_FUNC_CALL ; 
 int /*<<< orphan*/  log (double) ; 
 int /*<<< orphan*/  return_double (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_double (int /*<<< orphan*/ *,double*) ; 

__attribute__((used)) static HRESULT Global_Log(vbdisp_t *This, VARIANT *arg, unsigned args_cnt, VARIANT *res)
{
    HRESULT hres;
    double d;

    hres = to_double(arg, &d);
    if(FAILED(hres))
        return hres;

    if(d <= 0)
        return MAKE_VBSERROR(VBSE_ILLEGAL_FUNC_CALL);
    else
        return return_double(res, log(d));
}