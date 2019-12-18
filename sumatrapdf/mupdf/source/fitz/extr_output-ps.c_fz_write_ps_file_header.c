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
typedef  int /*<<< orphan*/  fz_output ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_write_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

void
fz_write_ps_file_header(fz_context *ctx, fz_output *out)
{
	fz_write_printf(ctx, out,
		"%%!PS-Adobe-3.0\n"
		//"%%%%BoundingBox: 0 0 612 792\n"
		//"%%%%HiResBoundingBox: 0 0 612 792\n"
		"%%%%Creator: MuPDF\n"
		"%%%%LanguageLevel: 2\n"
		"%%%%CreationDate: D:20160318101706Z00'00'\n"
		"%%%%DocumentData: Binary\n"
		"%%%%Pages: (atend)\n"
		"%%%%EndComments\n"
		"\n"
		"%%%%BeginProlog\n"
		"%%%%EndProlog\n"
		"\n"
		"%%%%BeginSetup\n"
		"%%%%EndSetup\n"
		"\n"
		);
}