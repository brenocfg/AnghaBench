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
 int /*<<< orphan*/  DISP_E_BADVARTYPE ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  debugstr_variant (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  return_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  to_int (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static HRESULT Global_CLng(vbdisp_t *This, VARIANT *arg, unsigned args_cnt, VARIANT *res)
{
    int i;
    HRESULT hres;

    TRACE("%s\n", debugstr_variant(arg));

    assert(args_cnt == 1);

    hres = to_int(arg, &i);
    if(FAILED(hres))
        return hres;
    if(!res)
        return DISP_E_BADVARTYPE;

    return return_int(res, i);
}