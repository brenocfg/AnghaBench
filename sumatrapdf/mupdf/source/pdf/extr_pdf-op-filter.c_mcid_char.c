#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* prev; } ;
typedef  TYPE_1__ tag_record ;
struct TYPE_7__ {TYPE_1__* current_tags; TYPE_1__* pending_tags; } ;
typedef  TYPE_2__ pdf_filter_processor ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  mcid_char_imp (int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__*,int,int) ; 

__attribute__((used)) static void
mcid_char(fz_context *ctx, pdf_filter_processor *p, int uni, int remove)
{
	tag_record *tr  = p->pending_tags;

	for (tr = p->pending_tags; tr != NULL; tr = tr->prev)
		mcid_char_imp(ctx, p, tr, uni, remove);
	for (tr = p->current_tags; tr != NULL; tr = tr->prev)
		mcid_char_imp(ctx, p, tr, uni, remove);
}