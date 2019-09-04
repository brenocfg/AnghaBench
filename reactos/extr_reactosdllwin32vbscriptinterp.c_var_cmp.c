#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* script; } ;
typedef  TYPE_2__ exec_ctx_t ;
typedef  int /*<<< orphan*/  VARIANT ;
struct TYPE_4__ {int /*<<< orphan*/  lcid; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VarCmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_variant (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT var_cmp(exec_ctx_t *ctx, VARIANT *l, VARIANT *r)
{
    TRACE("%s %s\n", debugstr_variant(l), debugstr_variant(r));

    /* FIXME: Fix comparing string to number */

    return VarCmp(l, r, ctx->script->lcid, 0);
 }