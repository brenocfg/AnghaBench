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
struct TYPE_3__ {int /*<<< orphan*/  scalar; } ;
typedef  TYPE_1__ fletcher_4_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZIO_SET_CHECKSUM (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fletcher_4_scalar_init(fletcher_4_ctx_t *ctx)
{
	ZIO_SET_CHECKSUM(&ctx->scalar, 0, 0, 0, 0);
}