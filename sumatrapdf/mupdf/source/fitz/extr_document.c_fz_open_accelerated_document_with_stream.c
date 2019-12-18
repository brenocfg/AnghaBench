#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_stream ;
struct TYPE_4__ {int /*<<< orphan*/ * (* open_with_stream ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* open_accel_with_stream ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ fz_document_handler ;
typedef  int /*<<< orphan*/  fz_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  fz_drop_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* fz_recognize_document (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__ pdf_document_handler ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

fz_document *
fz_open_accelerated_document_with_stream(fz_context *ctx, const char *magic, fz_stream *stream, fz_stream *accel)
{
	const fz_document_handler *handler;

	if (magic == NULL || stream == NULL)
		fz_throw(ctx, FZ_ERROR_GENERIC, "no document to open");

	handler = fz_recognize_document(ctx, magic);
	if (!handler)
#if FZ_ENABLE_PDF
		handler = &pdf_document_handler;
#else
		fz_throw(ctx, FZ_ERROR_GENERIC, "cannot find document handler for file type: %s", magic);
#endif
	if (handler->open_accel_with_stream)
		if (accel || handler->open_with_stream == NULL)
			return handler->open_accel_with_stream(ctx, stream, accel);
	if (accel)
	{
		/* We've had an accelerator passed to a format that doesn't
		 * handle it. This should never happen, as how did the
		 * accelerator get created? */
		fz_drop_stream(ctx, accel);
	}
	return handler->open_with_stream(ctx, stream);
}