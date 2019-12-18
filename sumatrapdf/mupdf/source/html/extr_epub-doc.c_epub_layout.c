#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  fz_document ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_3__ {float layout_w; float layout_h; float layout_em; scalar_t__ css_sum; TYPE_2__* accel; } ;
typedef  TYPE_1__ epub_document ;
struct TYPE_4__ {float layout_w; float layout_h; float layout_em; int use_doc_css; scalar_t__ css_sum; } ;

/* Variables and functions */
 int fz_use_document_css (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  invalidate_accelerator (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ user_css_sum (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
epub_layout(fz_context *ctx, fz_document *doc_, float w, float h, float em)
{
	epub_document *doc = (epub_document*)doc_;
	uint32_t css_sum = user_css_sum(ctx);
	int use_doc_css = fz_use_document_css(ctx);

	if (doc->layout_w == w && doc->layout_h == h && doc->layout_em == em && doc->css_sum == css_sum)
		return;
	doc->layout_w = w;
	doc->layout_h = h;
	doc->layout_em = em;

	if (doc->accel == NULL)
		return;

	/* When we load the saved accelerator, doc->accel
	 * can be populated with different values than doc.
	 * This is really useful as doc starts out with the
	 * values being 0. If we've got the right values
	 * already, then don't bin the data! */
	if (doc->accel->layout_w == w &&
		doc->accel->layout_h == h &&
		doc->accel->layout_em == em &&
		doc->accel->use_doc_css == use_doc_css &&
		doc->accel->css_sum == css_sum)
		return;

	doc->accel->layout_w = w;
	doc->accel->layout_h = h;
	doc->accel->layout_em = em;
	doc->accel->use_doc_css = use_doc_css;
	doc->accel->css_sum = css_sum;
	invalidate_accelerator(ctx, doc->accel);
}