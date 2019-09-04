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
struct TYPE_4__ {int /*<<< orphan*/  val; int /*<<< orphan*/  ei; } ;
struct TYPE_5__ {TYPE_1__ ei; } ;
typedef  TYPE_2__ script_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_undefined () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void clear_ei(script_ctx_t *ctx)
{
    memset(&ctx->ei.ei, 0, sizeof(ctx->ei.ei));
    jsval_release(ctx->ei.val);
    ctx->ei.val = jsval_undefined();
}