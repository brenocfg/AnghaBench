#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int offset; } ;
typedef  TYPE_2__ zip_entry ;
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/ * file; } ;
struct TYPE_8__ {TYPE_1__ super; } ;
typedef  TYPE_3__ fz_zip_archive ;
typedef  int /*<<< orphan*/  fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int ZIP_ENCRYPTED_FLAG ; 
 scalar_t__ ZIP_LOCAL_FILE_SIG ; 
 int fz_read_uint16_le (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ fz_read_uint32_le (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int read_zip_entry_header(fz_context *ctx, fz_zip_archive *zip, zip_entry *ent)
{
	fz_stream *file = zip->super.file;
	uint32_t sig;
	int general, method, namelength, extralength;

	fz_seek(ctx, file, ent->offset, 0);

	sig = fz_read_uint32_le(ctx, file);
	if (sig != ZIP_LOCAL_FILE_SIG)
		fz_throw(ctx, FZ_ERROR_GENERIC, "wrong zip local file signature (0x%x)", sig);

	(void) fz_read_uint16_le(ctx, file); /* version */
	general = fz_read_uint16_le(ctx, file); /* general */
	if (general & ZIP_ENCRYPTED_FLAG)
		fz_throw(ctx, FZ_ERROR_GENERIC, "zip content is encrypted");

	method = fz_read_uint16_le(ctx, file);
	(void) fz_read_uint16_le(ctx, file); /* file time */
	(void) fz_read_uint16_le(ctx, file); /* file date */
	(void) fz_read_uint32_le(ctx, file); /* crc-32 */
	(void) fz_read_uint32_le(ctx, file); /* csize */
	(void) fz_read_uint32_le(ctx, file); /* usize */
	namelength = fz_read_uint16_le(ctx, file);
	extralength = fz_read_uint16_le(ctx, file);

	fz_seek(ctx, file, namelength + extralength, 1);

	return method;
}