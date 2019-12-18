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
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  pdf_document ;
typedef  int /*<<< orphan*/  fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ fz_compression_params ;

/* Variables and functions */
 int /*<<< orphan*/  DP ; 
 int /*<<< orphan*/  DecodeParms ; 
 int /*<<< orphan*/  F ; 
 int /*<<< orphan*/  FZ_IMAGE_RAW ; 
 int /*<<< orphan*/  Filter ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * build_filter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * build_filter_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * fz_open_null_filter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_tell (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_array_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_geta (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pdf_is_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

fz_stream *
pdf_open_inline_stream(fz_context *ctx, pdf_document *doc, pdf_obj *stmobj, int length, fz_stream *file_stm, fz_compression_params *imparams)
{
	pdf_obj *filters = pdf_dict_geta(ctx, stmobj, PDF_NAME(Filter), PDF_NAME(F));
	pdf_obj *params = pdf_dict_geta(ctx, stmobj, PDF_NAME(DecodeParms), PDF_NAME(DP));

	if (pdf_is_name(ctx, filters))
		return build_filter(ctx, file_stm, doc, filters, params, 0, 0, imparams);
	else if (pdf_array_len(ctx, filters) > 0)
		return build_filter_chain(ctx, file_stm, doc, filters, params, 0, 0, imparams);

	if (imparams)
		imparams->type = FZ_IMAGE_RAW;
	return fz_open_null_filter(ctx, file_stm, length, fz_tell(ctx, file_stm));
}