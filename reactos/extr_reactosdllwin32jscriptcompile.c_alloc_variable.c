#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* func; } ;
typedef  TYPE_2__ compiler_ctx_t ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_7__ {int /*<<< orphan*/  var_cnt; } ;
typedef  int /*<<< orphan*/  BSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  alloc_local (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compiler_alloc_bstr (TYPE_2__*,int /*<<< orphan*/  const*) ; 
 scalar_t__ find_local (TYPE_2__*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static BOOL alloc_variable(compiler_ctx_t *ctx, const WCHAR *name)
{
    BSTR ident;

    if(find_local(ctx, name))
        return TRUE;

    ident = compiler_alloc_bstr(ctx, name);
    if(!ident)
        return FALSE;

    return alloc_local(ctx, ident, ctx->func->var_cnt++);
}