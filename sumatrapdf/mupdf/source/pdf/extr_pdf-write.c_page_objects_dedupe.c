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
struct TYPE_3__ {int len; scalar_t__* object; } ;
typedef  TYPE_1__ page_objects ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */

__attribute__((used)) static void
page_objects_dedupe(fz_context *ctx, page_objects *po)
{
	int i, j;
	int n = po->len-1;

	for (i = 0; i < n; i++)
	{
		if (po->object[i] == po->object[i+1])
			break;
	}
	j = i; /* j points to the last valid one */
	i++; /* i points to the first one we haven't looked at */
	for (; i < n; i++)
	{
		if (po->object[j] != po->object[i])
			po->object[++j] = po->object[i];
	}
	po->len = j+1;
}