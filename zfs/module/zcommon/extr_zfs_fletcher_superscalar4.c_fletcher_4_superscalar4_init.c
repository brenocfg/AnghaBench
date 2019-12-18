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
typedef  int /*<<< orphan*/  zfs_fletcher_superscalar_t ;
struct TYPE_3__ {int /*<<< orphan*/  superscalar; } ;
typedef  TYPE_1__ fletcher_4_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
fletcher_4_superscalar4_init(fletcher_4_ctx_t *ctx)
{
	bzero(ctx->superscalar, 4 * sizeof (zfs_fletcher_superscalar_t));
}