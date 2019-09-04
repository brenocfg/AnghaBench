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
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ ArrayInstance ;

/* Variables and functions */
 int /*<<< orphan*/  ArrayConstr_info ; 
 int /*<<< orphan*/  ArrayConstr_value ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int PROPF_CONSTR ; 
 int /*<<< orphan*/  alloc_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__**) ; 
 int /*<<< orphan*/  create_builtin_constructor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 

HRESULT create_array_constr(script_ctx_t *ctx, jsdisp_t *object_prototype, jsdisp_t **ret)
{
    ArrayInstance *array;
    HRESULT hres;

    static const WCHAR ArrayW[] = {'A','r','r','a','y',0};

    hres = alloc_array(ctx, object_prototype, &array);
    if(FAILED(hres))
        return hres;

    hres = create_builtin_constructor(ctx, ArrayConstr_value, ArrayW, &ArrayConstr_info, PROPF_CONSTR|1, &array->dispex, ret);

    jsdisp_release(&array->dispex);
    return hres;
}