#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int len; int cap; int* object; } ;
typedef  TYPE_1__ page_objects ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 TYPE_1__* fz_realloc (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 TYPE_1__* page_objects_create (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
page_objects_insert(fz_context *ctx, page_objects **ppo, int i)
{
	page_objects *po;

	/* Make a page_objects if we don't have one */
	if (*ppo == NULL)
		*ppo = page_objects_create(ctx);

	po = *ppo;
	/* page_objects insertion: extend the page_objects by 1, and put us on the end */
	if (po->len == po->cap)
	{
		po = fz_realloc(ctx, po, sizeof(page_objects) + (po->cap*2 - 1)*sizeof(int));
		po->cap *= 2;
		*ppo = po;
	}
	po->object[po->len++] = i;
}