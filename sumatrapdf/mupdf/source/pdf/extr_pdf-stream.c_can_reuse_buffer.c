#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  obj; int /*<<< orphan*/  stm_buf; } ;
typedef  TYPE_1__ pdf_xref_entry ;
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_7__ {scalar_t__ type; } ;
typedef  TYPE_2__ fz_compression_params ;

/* Variables and functions */
 int /*<<< orphan*/  DP ; 
 int /*<<< orphan*/  DecodeParms ; 
 int /*<<< orphan*/  F ; 
 scalar_t__ FZ_IMAGE_RAW ; 
 int /*<<< orphan*/  Filter ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_compression_params (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * pdf_array_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pdf_array_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_geta (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pdf_is_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_is_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_is_null (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
can_reuse_buffer(fz_context *ctx, pdf_xref_entry *entry, fz_compression_params *params)
{
	pdf_obj *f;
	pdf_obj *p;

	if (!entry || !entry->obj || !entry->stm_buf)
		return 0;

	if (params)
		params->type = FZ_IMAGE_RAW;

	f = pdf_dict_geta(ctx, entry->obj, PDF_NAME(Filter), PDF_NAME(F));
	/* If there are no filters, it's uncompressed, and we can use it */
	if (!f)
		return 1;

	p = pdf_dict_geta(ctx, entry->obj, PDF_NAME(DecodeParms), PDF_NAME(DP));
	if (pdf_is_array(ctx, f))
	{
		int len = pdf_array_len(ctx, f);

		/* Empty array of filters. Its uncompressed. We can cope. */
		if (len == 0)
			return 1;
		/* 1 filter is the most we can hope to cope with - if more,*/
		if (len != 1)
			return 0;
		p = pdf_array_get(ctx, p, 0);
	}
	if (pdf_is_null(ctx, f))
		return 1; /* Null filter is uncompressed */
	if (!pdf_is_name(ctx, f))
		return 0;

	/* There are filters, so unless we have the option of shortstopping,
	 * we can't use the existing buffer. */
	if (!params)
		return 0;

	build_compression_params(ctx, f, p, params);

	return (params->type == FZ_IMAGE_RAW) ? 0 : 1;
}