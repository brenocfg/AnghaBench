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
 char* pdf_annot_author (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pdf_annot_has_author (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selected_annot ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  ui_label (char*,char const*) ; 

__attribute__((used)) static void do_annotate_author(void)
{
	if (pdf_annot_has_author(ctx, selected_annot))
	{
		const char *author = pdf_annot_author(ctx, selected_annot);
		if (strlen(author) > 0)
			ui_label("Author: %s", author);
	}
}