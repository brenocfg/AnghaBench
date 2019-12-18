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
typedef  int /*<<< orphan*/  uInt ;
struct TYPE_5__ {int /*<<< orphan*/  count; int /*<<< orphan*/  output; int /*<<< orphan*/  central; } ;
typedef  TYPE_1__ fz_zip_writer ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_6__ {char const* data; scalar_t__ len; } ;
typedef  TYPE_2__ fz_buffer ;

/* Variables and functions */
 int ZIP_CENTRAL_DIRECTORY_SIG ; 
 int ZIP_LOCAL_FILE_SIG ; 
 int crc32 (int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_append_int16_le (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fz_append_int32_le (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fz_append_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int fz_tell_output (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_write_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 int /*<<< orphan*/  fz_write_int16_le (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fz_write_int32_le (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strlen (char const*) ; 

void
fz_write_zip_entry(fz_context *ctx, fz_zip_writer *zip, const char *name, fz_buffer *buf, int compress)
{
	int offset = fz_tell_output(ctx, zip->output);
	int sum;

	sum = crc32(0, NULL, 0);
	sum = crc32(sum, buf->data, (uInt)buf->len);

	fz_append_int32_le(ctx, zip->central, ZIP_CENTRAL_DIRECTORY_SIG);
	fz_append_int16_le(ctx, zip->central, 0); /* version made by: MS-DOS */
	fz_append_int16_le(ctx, zip->central, 20); /* version to extract: 2.0 */
	fz_append_int16_le(ctx, zip->central, 0); /* general purpose bit flag */
	fz_append_int16_le(ctx, zip->central, 0); /* compression method: store */
	fz_append_int16_le(ctx, zip->central, 0); /* TODO: last mod file time */
	fz_append_int16_le(ctx, zip->central, 0); /* TODO: last mod file date */
	fz_append_int32_le(ctx, zip->central, sum); /* crc-32 */
	fz_append_int32_le(ctx, zip->central, (int)buf->len); /* csize */
	fz_append_int32_le(ctx, zip->central, (int)buf->len); /* usize */
	fz_append_int16_le(ctx, zip->central, (int)strlen(name)); /* file name length */
	fz_append_int16_le(ctx, zip->central, 0); /* extra field length */
	fz_append_int16_le(ctx, zip->central, 0); /* file comment length */
	fz_append_int16_le(ctx, zip->central, 0); /* disk number start */
	fz_append_int16_le(ctx, zip->central, 0); /* internal file attributes */
	fz_append_int32_le(ctx, zip->central, 0); /* external file attributes */
	fz_append_int32_le(ctx, zip->central, offset); /* relative offset of local header */
	fz_append_string(ctx, zip->central, name);

	fz_write_int32_le(ctx, zip->output, ZIP_LOCAL_FILE_SIG);
	fz_write_int16_le(ctx, zip->output, 20); /* version to extract: 2.0 */
	fz_write_int16_le(ctx, zip->output, 0); /* general purpose bit flag */
	fz_write_int16_le(ctx, zip->output, 0); /* compression method: store */
	fz_write_int16_le(ctx, zip->output, 0); /* TODO: last mod file time */
	fz_write_int16_le(ctx, zip->output, 0); /* TODO: last mod file date */
	fz_write_int32_le(ctx, zip->output, sum); /* crc-32 */
	fz_write_int32_le(ctx, zip->output, (int)buf->len); /* csize */
	fz_write_int32_le(ctx, zip->output, (int)buf->len); /* usize */
	fz_write_int16_le(ctx, zip->output, (int)strlen(name)); /* file name length */
	fz_write_int16_le(ctx, zip->output, 0); /* extra field length */
	fz_write_data(ctx, zip->output, name, strlen(name));
	fz_write_data(ctx, zip->output, buf->data, buf->len);

	++zip->count;
}