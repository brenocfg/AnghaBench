#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ pdf_font_desc ;
typedef  int /*<<< orphan*/  pdf_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* fz_find_item (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* fz_store_item (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hail_mary_store_key ; 
 int /*<<< orphan*/  hail_mary_store_type ; 
 int /*<<< orphan*/  pdf_drop_font_imp ; 
 TYPE_1__* pdf_load_simple_font (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

pdf_font_desc *
pdf_load_hail_mary_font(fz_context *ctx, pdf_document *doc)
{
	pdf_font_desc *fontdesc;
	pdf_font_desc *existing;

	if ((fontdesc = fz_find_item(ctx, pdf_drop_font_imp, &hail_mary_store_key, &hail_mary_store_type)) != NULL)
	{
		return fontdesc;
	}

	/* FIXME: Get someone with a clue about fonts to fix this */
	fontdesc = pdf_load_simple_font(ctx, doc, NULL);

	existing = fz_store_item(ctx, &hail_mary_store_key, fontdesc, fontdesc->size, &hail_mary_store_type);
	assert(existing == NULL);
	(void)existing; /* Silence warning in release builds */

	return fontdesc;
}