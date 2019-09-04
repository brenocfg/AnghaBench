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
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int /*<<< orphan*/  dispex_prop_t ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_prop_name_prot (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  invoke_prop_func (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_hash (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  to_disp (int /*<<< orphan*/ *) ; 

HRESULT jsdisp_call_name(jsdisp_t *disp, const WCHAR *name, WORD flags, unsigned argc, jsval_t *argv, jsval_t *r)
{
    dispex_prop_t *prop;
    HRESULT hres;

    hres = find_prop_name_prot(disp, string_hash(name), name, &prop);
    if(FAILED(hres))
        return hres;

    return invoke_prop_func(disp, to_disp(disp), prop, flags, argc, argv, r, NULL);
}