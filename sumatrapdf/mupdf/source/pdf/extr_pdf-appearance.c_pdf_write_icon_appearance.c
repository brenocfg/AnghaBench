#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_annot ;
struct TYPE_5__ {int x0; int x1; int y0; int y1; } ;
typedef  TYPE_1__ fz_rect ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  fz_append_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 TYPE_1__ fz_make_rect (float,float,int,int) ; 
 char* icon_comment ; 
 char* icon_graph ; 
 char* icon_help ; 
 char* icon_insert ; 
 char* icon_key ; 
 char* icon_mic ; 
 char* icon_new_paragraph ; 
 char* icon_note ; 
 char* icon_paperclip ; 
 char* icon_paragraph ; 
 char* icon_push_pin ; 
 char* icon_speaker ; 
 char* icon_star ; 
 char* icon_tag ; 
 char* pdf_annot_icon_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_is_dark_fill_color (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_write_fill_color_appearance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static void
pdf_write_icon_appearance(fz_context *ctx, pdf_annot *annot, fz_buffer *buf, fz_rect *rect, fz_rect *bbox)
{
	const char *name;
	float xc = (rect->x0 + rect->x1) / 2;
	float yc = (rect->y0 + rect->y1) / 2;

	if (!pdf_write_fill_color_appearance(ctx, annot, buf))
		fz_append_string(ctx, buf, "1 g\n");

	fz_append_string(ctx, buf, "1 w\n0.5 0.5 15 15 re\nb\n");
	fz_append_string(ctx, buf, "1 0 0 -1 4 12 cm\n");

	if (pdf_is_dark_fill_color(ctx, annot))
		fz_append_string(ctx, buf, "1 g\n");
	else
		fz_append_string(ctx, buf, "0 g\n");

	name = pdf_annot_icon_name(ctx, annot);

	/* Text names */
	if (!strcmp(name, "Comment"))
		fz_append_string(ctx, buf, icon_comment);
	else if (!strcmp(name, "Key"))
		fz_append_string(ctx, buf, icon_key);
	else if (!strcmp(name, "Note"))
		fz_append_string(ctx, buf, icon_note);
	else if (!strcmp(name, "Help"))
		fz_append_string(ctx, buf, icon_help);
	else if (!strcmp(name, "NewParagraph"))
		fz_append_string(ctx, buf, icon_new_paragraph);
	else if (!strcmp(name, "Paragraph"))
		fz_append_string(ctx, buf, icon_paragraph);
	else if (!strcmp(name, "Insert"))
		fz_append_string(ctx, buf, icon_insert);

	/* FileAttachment names */
	else if (!strcmp(name, "Graph"))
		fz_append_string(ctx, buf, icon_graph);
	else if (!strcmp(name, "PushPin"))
		fz_append_string(ctx, buf, icon_push_pin);
	else if (!strcmp(name, "Paperclip"))
		fz_append_string(ctx, buf, icon_paperclip);
	else if (!strcmp(name, "Tag"))
		fz_append_string(ctx, buf, icon_tag);

	/* Sound names */
	else if (!strcmp(name, "Speaker"))
		fz_append_string(ctx, buf, icon_speaker);
	else if (!strcmp(name, "Mic"))
		fz_append_string(ctx, buf, icon_mic);

	/* Unknown */
	else
		fz_append_string(ctx, buf, icon_star);

	*rect = fz_make_rect(xc - 9, yc - 9, xc + 9, yc + 9);
	*bbox = fz_make_rect(0, 0, 16, 16);
}