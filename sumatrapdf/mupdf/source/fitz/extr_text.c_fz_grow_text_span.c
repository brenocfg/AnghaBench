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
struct TYPE_3__ {int cap; int len; int /*<<< orphan*/  items; } ;
typedef  TYPE_1__ fz_text_span ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_realloc_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_text_item ; 

__attribute__((used)) static void
fz_grow_text_span(fz_context *ctx, fz_text_span *span, int n)
{
	int new_cap = span->cap;
	if (span->len + n < new_cap)
		return;
	while (span->len + n > new_cap)
		new_cap = new_cap + 36;
	span->items = fz_realloc_array(ctx, span->items, new_cap, fz_text_item);
	span->cap = new_cap;
}