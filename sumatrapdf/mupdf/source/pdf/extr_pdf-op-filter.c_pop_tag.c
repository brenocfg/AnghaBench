#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* utf8; } ;
struct TYPE_6__ {TYPE_3__* utf8; } ;
struct TYPE_8__ {int /*<<< orphan*/  mcid_obj; TYPE_2__ actualtext; TYPE_1__ alt; int /*<<< orphan*/  cooked; int /*<<< orphan*/  raw; scalar_t__ bdc; struct TYPE_8__* tag; struct TYPE_8__* prev; } ;
typedef  TYPE_3__ tag_record ;
typedef  int /*<<< orphan*/  pdf_filter_processor ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  pdf_drop_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pop_tag(fz_context *ctx, pdf_filter_processor *p, tag_record **tags)
{
	tag_record *tag = *tags;

	if (tag == NULL)
		return;
	*tags = tag->prev;
	fz_free(ctx, tag->tag);
	if (tag->bdc)
	{
		pdf_drop_obj(ctx, tag->raw);
		pdf_drop_obj(ctx, tag->cooked);
	}
	fz_free(ctx, tag->alt.utf8);
	fz_free(ctx, tag->actualtext.utf8);
	pdf_drop_obj(ctx, tag->mcid_obj);
	fz_free(ctx, tag);
}