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
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  DA ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_min (int,int /*<<< orphan*/ ) ; 
 float pdf_array_get_real (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pdf_array_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_dict_get_inheritable (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_dict_put_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_field_mark_dirty (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_parse_default_appearance (int /*<<< orphan*/ *,char const*,char const**,float*,float*) ; 
 int /*<<< orphan*/  pdf_print_default_appearance (int /*<<< orphan*/ *,char*,int,char const*,float,float*) ; 
 char* pdf_to_str_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

void pdf_field_set_text_color(fz_context *ctx, pdf_obj *field, pdf_obj *col)
{
	char buf[100];
	const char *font;
	float size, color[3], black;
	const char *da = pdf_to_str_buf(ctx, pdf_dict_get_inheritable(ctx, field, PDF_NAME(DA)));

	pdf_parse_default_appearance(ctx, da, &font, &size, color);

	switch (pdf_array_len(ctx, col))
	{
	default:
		color[0] = color[1] = color[2] = 0;
		break;
	case 1:
		color[0] = color[1] = color[2] = pdf_array_get_real(ctx, col, 0);
		break;
	case 3:
		color[0] = pdf_array_get_real(ctx, col, 0);
		color[1] = pdf_array_get_real(ctx, col, 1);
		color[2] = pdf_array_get_real(ctx, col, 2);
		break;
	case 4:
		black = pdf_array_get_real(ctx, col, 3);
		color[0] = 1 - fz_min(1, pdf_array_get_real(ctx, col, 0) + black);
		color[1] = 1 - fz_min(1, pdf_array_get_real(ctx, col, 1) + black);
		color[2] = 1 - fz_min(1, pdf_array_get_real(ctx, col, 2) + black);
		break;
	}

	pdf_print_default_appearance(ctx, buf, sizeof buf, font, size, color);
	pdf_dict_put_string(ctx, field, PDF_NAME(DA), buf, strlen(buf));
	pdf_field_mark_dirty(ctx, field);
}