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
struct TYPE_3__ {int /*<<< orphan*/  storable; } ;
typedef  TYPE_1__ pdf_pattern ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_drop_storable (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
pdf_drop_pattern(fz_context *ctx, pdf_pattern *pat)
{
	fz_drop_storable(ctx, &pat->storable);
}