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
 int /*<<< orphan*/  BS ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S ; 
 int /*<<< orphan*/  pdf_dict_getl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* pdf_to_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

char *pdf_field_border_style(fz_context *ctx, pdf_obj *field)
{
	const char *bs = pdf_to_name(ctx, pdf_dict_getl(ctx, field, PDF_NAME(BS), PDF_NAME(S), NULL));
	switch (*bs)
	{
	case 'S': return "Solid";
	case 'D': return "Dashed";
	case 'B': return "Beveled";
	case 'I': return "Inset";
	case 'U': return "Underline";
	}
	return "Solid";
}