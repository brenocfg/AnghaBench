#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  fz_bookmark ;

/* Variables and functions */
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  currentpage ; 
 int /*<<< orphan*/  doc ; 
 scalar_t__ future_count ; 
 scalar_t__ fz_is_document_reflowable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_layout_document (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fz_lookup_bookmark (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_make_bookmark (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ history_count ; 
 int layout_em ; 
 int /*<<< orphan*/  layout_h ; 
 int /*<<< orphan*/  layout_w ; 
 int /*<<< orphan*/  load_page () ; 
 int /*<<< orphan*/  render_page () ; 
 int /*<<< orphan*/  update_title () ; 

__attribute__((used)) static void relayout(void)
{
	if (layout_em < 6) layout_em = 6;
	if (layout_em > 36) layout_em = 36;
	if (fz_is_document_reflowable(ctx, doc))
	{
		fz_bookmark mark = fz_make_bookmark(ctx, doc, currentpage);
		fz_layout_document(ctx, doc, layout_w, layout_h, layout_em);
		currentpage = fz_lookup_bookmark(ctx, doc, mark);
		history_count = 0;
		future_count = 0;

		load_page();
		render_page();
		update_title();
	}
}