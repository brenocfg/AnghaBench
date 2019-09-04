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
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,unsigned int const) ; 
 int /*<<< orphan*/  create_regexp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int const,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  debugstr_jsstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_op_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int get_op_uint (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  jsval_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stack_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT interp_regexp(script_ctx_t *ctx)
{
    jsstr_t *source = get_op_str(ctx, 0);
    const unsigned flags = get_op_uint(ctx, 1);
    jsdisp_t *regexp;
    HRESULT hres;

    TRACE("%s %x\n", debugstr_jsstr(source), flags);

    hres = create_regexp(ctx, source, flags, &regexp);
    if(FAILED(hres))
        return hres;

    return stack_push(ctx, jsval_obj(regexp));
}