#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int codespace_len; TYPE_3__* codespace; } ;
typedef  TYPE_1__ pdf_cmap ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_5__ {int n; unsigned int low; unsigned int high; } ;

/* Variables and functions */
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*) ; 
 int nelem (TYPE_3__*) ; 

void
pdf_add_codespace(fz_context *ctx, pdf_cmap *cmap, unsigned int low, unsigned int high, int n)
{
	if (cmap->codespace_len + 1 == nelem(cmap->codespace))
	{
		fz_warn(ctx, "assert: too many code space ranges");
		return;
	}

	cmap->codespace[cmap->codespace_len].n = n;
	cmap->codespace[cmap->codespace_len].low = low;
	cmap->codespace[cmap->codespace_len].high = high;
	cmap->codespace_len ++;
}