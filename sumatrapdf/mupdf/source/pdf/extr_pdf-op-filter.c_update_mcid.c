#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  utf8; scalar_t__ edited; } ;
struct TYPE_6__ {int /*<<< orphan*/  utf8; scalar_t__ edited; } ;
struct TYPE_8__ {TYPE_2__ actualtext; int /*<<< orphan*/  mcid_obj; TYPE_1__ alt; } ;
typedef  TYPE_3__ tag_record ;
struct TYPE_9__ {TYPE_3__* current_tags; } ;
typedef  TYPE_4__ pdf_filter_processor ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  Alt ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dict_put_text_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
update_mcid(fz_context *ctx, pdf_filter_processor *p)
{
	tag_record *tag = p->current_tags;

	if (tag == NULL)
		return;
	if (tag->alt.edited)
		pdf_dict_put_text_string(ctx, tag->mcid_obj, PDF_NAME(Alt), tag->alt.utf8);
	if (tag->actualtext.edited)
		pdf_dict_put_text_string(ctx, tag->mcid_obj, PDF_NAME(Alt), tag->actualtext.utf8);
}