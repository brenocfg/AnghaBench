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
typedef  int /*<<< orphan*/  fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pdf_get_indirect_document (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pdf_is_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pdf_open_stream_number (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdf_to_num (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

fz_stream *pdf_open_stream(fz_context *ctx, pdf_obj *ref)
{
	if (pdf_is_stream(ctx, ref))
		return pdf_open_stream_number(ctx, pdf_get_indirect_document(ctx, ref), pdf_to_num(ctx, ref));
	fz_throw(ctx, FZ_ERROR_GENERIC, "object is not a stream");
}