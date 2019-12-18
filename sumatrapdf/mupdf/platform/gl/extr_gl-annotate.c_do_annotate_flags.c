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
 int PDF_ANNOT_IS_HIDDEN ; 
 int PDF_ANNOT_IS_INVISIBLE ; 
 int PDF_ANNOT_IS_LOCKED ; 
 int PDF_ANNOT_IS_LOCKED_CONTENTS ; 
 int PDF_ANNOT_IS_NO_ROTATE ; 
 int PDF_ANNOT_IS_NO_VIEW ; 
 int PDF_ANNOT_IS_NO_ZOOM ; 
 int PDF_ANNOT_IS_PRINT ; 
 int PDF_ANNOT_IS_READ_ONLY ; 
 int PDF_ANNOT_IS_TOGGLE_NO_VIEW ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  fz_strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  fz_strlcpy (char*,char*,int) ; 
 int pdf_annot_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selected_annot ; 
 int /*<<< orphan*/  ui_label (char*,char*) ; 

__attribute__((used)) static void do_annotate_flags(void)
{
	char buf[4096];
	int f = pdf_annot_flags(ctx, selected_annot);
	fz_strlcpy(buf, "Flags:", sizeof buf);
	if (f & PDF_ANNOT_IS_INVISIBLE) fz_strlcat(buf, " inv", sizeof buf);
	if (f & PDF_ANNOT_IS_HIDDEN) fz_strlcat(buf, " hidden", sizeof buf);
	if (f & PDF_ANNOT_IS_PRINT) fz_strlcat(buf, " print", sizeof buf);
	if (f & PDF_ANNOT_IS_NO_ZOOM) fz_strlcat(buf, " nz", sizeof buf);
	if (f & PDF_ANNOT_IS_NO_ROTATE) fz_strlcat(buf, " nr", sizeof buf);
	if (f & PDF_ANNOT_IS_NO_VIEW) fz_strlcat(buf, " nv", sizeof buf);
	if (f & PDF_ANNOT_IS_READ_ONLY) fz_strlcat(buf, " ro", sizeof buf);
	if (f & PDF_ANNOT_IS_LOCKED) fz_strlcat(buf, " lock", sizeof buf);
	if (f & PDF_ANNOT_IS_TOGGLE_NO_VIEW) fz_strlcat(buf, " tnv", sizeof buf);
	if (f & PDF_ANNOT_IS_LOCKED_CONTENTS) fz_strlcat(buf, " lc", sizeof buf);
	if (!f) fz_strlcat(buf, " none", sizeof buf);
	ui_label("%s", buf);
}