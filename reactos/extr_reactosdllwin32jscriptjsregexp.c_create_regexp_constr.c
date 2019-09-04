#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  char WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  dispex; } ;
typedef  TYPE_1__ RegExpInstance ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int PROPF_CONSTR ; 
 int /*<<< orphan*/  RegExpConstr_info ; 
 int /*<<< orphan*/  RegExpConstr_value ; 
 int /*<<< orphan*/  alloc_regexp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__**) ; 
 int /*<<< orphan*/  create_builtin_constructor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 

HRESULT create_regexp_constr(script_ctx_t *ctx, jsdisp_t *object_prototype, jsdisp_t **ret)
{
    RegExpInstance *regexp;
    HRESULT hres;

    static const WCHAR RegExpW[] = {'R','e','g','E','x','p',0};

    hres = alloc_regexp(ctx, object_prototype, &regexp);
    if(FAILED(hres))
        return hres;

    hres = create_builtin_constructor(ctx, RegExpConstr_value, RegExpW, &RegExpConstr_info,
            PROPF_CONSTR|2, &regexp->dispex, ret);

    jsdisp_release(&regexp->dispex);
    return hres;
}