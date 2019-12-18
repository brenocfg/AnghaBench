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

/* Variables and functions */
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  doc ; 
 scalar_t__ fz_atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_debug_store (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_drop_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_drop_document (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_drop_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_drop_outline (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_drop_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_drop_separations (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_drop_stext_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fzpage ; 
 int /*<<< orphan*/  getenv (char*) ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  outline ; 
 int /*<<< orphan*/  page_text ; 
 int /*<<< orphan*/  save_accelerator () ; 
 int /*<<< orphan*/  save_history () ; 
 int /*<<< orphan*/  seps ; 
 int /*<<< orphan*/  ui_finish () ; 

__attribute__((used)) static void cleanup(void)
{
	save_history();
	save_accelerator();

	ui_finish();

#ifndef NDEBUG
	if (fz_atoi(getenv("FZ_DEBUG_STORE")))
		fz_debug_store(ctx);
#endif

	fz_drop_stext_page(ctx, page_text);
	fz_drop_separations(ctx, seps);
	fz_drop_link(ctx, links);
	fz_drop_page(ctx, fzpage);
	fz_drop_outline(ctx, outline);
	fz_drop_document(ctx, doc);
	fz_drop_context(ctx);
}