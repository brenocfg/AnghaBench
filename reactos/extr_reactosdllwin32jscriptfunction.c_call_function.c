#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
struct TYPE_5__ {scalar_t__ value_proc; } ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ FunctionInstance ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DISPATCH_METHOD ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  invoke_source (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  invoke_value_proc (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT call_function(script_ctx_t *ctx, FunctionInstance *function, IDispatch *this_obj,
        unsigned argc, jsval_t *argv, BOOL caller_execs_source, jsval_t *r)
{
    if(function->value_proc)
        return invoke_value_proc(ctx, function, this_obj, DISPATCH_METHOD, argc, argv, r);

    return invoke_source(ctx, function, this_obj, argc, argv, FALSE, caller_execs_source, r);
}