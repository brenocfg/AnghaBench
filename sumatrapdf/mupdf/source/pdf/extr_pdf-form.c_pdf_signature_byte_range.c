#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_obj ;
struct TYPE_5__ {int file_size; } ;
typedef  TYPE_1__ pdf_document ;
struct TYPE_6__ {int offset; int length; } ;
typedef  TYPE_2__ fz_range ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  ByteRange ; 
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  PDF_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int pdf_array_get_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pdf_array_len (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_dict_getl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int pdf_signature_byte_range(fz_context *ctx, pdf_document *doc, pdf_obj *signature, fz_range *byte_range)
{
	pdf_obj *br = pdf_dict_getl(ctx, signature, PDF_NAME(V), PDF_NAME(ByteRange), NULL);
	int i, n = pdf_array_len(ctx, br)/2;

	if (byte_range)
	{
		for (i = 0; i < n; i++)
		{
			int offset = pdf_array_get_int(ctx, br, 2*i);
			int length = pdf_array_get_int(ctx, br, 2*i+1);

			if (offset < 0 || offset > doc->file_size)
				fz_throw(ctx, FZ_ERROR_GENERIC, "offset of signature byte range outside of file");
			else if (length < 0)
				fz_throw(ctx, FZ_ERROR_GENERIC, "length of signature byte range negative");
			else if (offset + length > doc->file_size)
				fz_throw(ctx, FZ_ERROR_GENERIC, "signature byte range extends past end of file");

			byte_range[i].offset = offset;
			byte_range[i].length = length;
		}
	}

	return n;
}