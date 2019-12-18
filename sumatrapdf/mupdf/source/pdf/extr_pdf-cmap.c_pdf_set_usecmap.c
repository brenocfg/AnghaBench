#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ codespace_len; int /*<<< orphan*/ * codespace; int /*<<< orphan*/  usecmap; } ;
typedef  TYPE_1__ pdf_cmap ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  pdf_drop_cmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_keep_cmap (int /*<<< orphan*/ *,TYPE_1__*) ; 

void
pdf_set_usecmap(fz_context *ctx, pdf_cmap *cmap, pdf_cmap *usecmap)
{
	int i;

	pdf_drop_cmap(ctx, cmap->usecmap);
	cmap->usecmap = pdf_keep_cmap(ctx, usecmap);

	if (cmap->codespace_len == 0)
	{
		cmap->codespace_len = usecmap->codespace_len;
		for (i = 0; i < usecmap->codespace_len; i++)
			cmap->codespace[i] = usecmap->codespace[i];
	}
}