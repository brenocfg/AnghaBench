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
 int /*<<< orphan*/  SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  debugstr_variant (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  return_bool (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_double (int /*<<< orphan*/ *,double*) ; 

__attribute__((used)) static HRESULT Global_IsNumeric(vbdisp_t *This, VARIANT *arg, unsigned args_cnt, VARIANT *res)
{
    HRESULT hres;
    double d;

    TRACE("(%s)\n", debugstr_variant(arg));

    assert(args_cnt == 1);

    hres = to_double(arg, &d);

    return return_bool(res, SUCCEEDED(hres));
}