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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {scalar_t__ status; scalar_t__ (* wfunc ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  wdata; int /*<<< orphan*/  sb; } ;
typedef  TYPE_1__ BCWriteCtx ;

/* Variables and functions */
 int /*<<< orphan*/  sbufL (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcwrite_footer(BCWriteCtx *ctx)
{
  if (ctx->status == 0) {
    uint8_t zero = 0;
    ctx->status = ctx->wfunc(sbufL(&ctx->sb), &zero, 1, ctx->wdata);
  }
}