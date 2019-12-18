#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_5__ {int count; int closed; int /*<<< orphan*/  output; TYPE_1__* central; } ;
typedef  TYPE_2__ fz_zip_writer ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_4__ {char* data; int len; } ;

/* Variables and functions */
 int ZIP_END_OF_CENTRAL_DIRECTORY_SIG ; 
 int /*<<< orphan*/  fz_close_output (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ fz_tell_output (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_write_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fz_write_int16_le (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fz_write_int32_le (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void
fz_close_zip_writer(fz_context *ctx, fz_zip_writer *zip)
{
	int64_t offset = fz_tell_output(ctx, zip->output);

	fz_write_data(ctx, zip->output, zip->central->data, zip->central->len);

	fz_write_int32_le(ctx, zip->output, ZIP_END_OF_CENTRAL_DIRECTORY_SIG);
	fz_write_int16_le(ctx, zip->output, 0); /* number of this disk */
	fz_write_int16_le(ctx, zip->output, 0); /* number of disk where central directory starts */
	fz_write_int16_le(ctx, zip->output, zip->count); /* entries in central directory in this disk */
	fz_write_int16_le(ctx, zip->output, zip->count); /* entries in central directory in total */
	fz_write_int32_le(ctx, zip->output, (int)zip->central->len); /* size of the central directory */
	fz_write_int32_le(ctx, zip->output, (int)offset); /* offset of the central directory */
	fz_write_int16_le(ctx, zip->output, 5); /* zip file comment length */

	fz_write_data(ctx, zip->output, "MuPDF", 5);

	fz_close_output(ctx, zip->output);

	zip->closed = 1;
}