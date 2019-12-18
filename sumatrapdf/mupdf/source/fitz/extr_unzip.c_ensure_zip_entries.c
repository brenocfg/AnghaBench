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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_5__ {int /*<<< orphan*/ * file; } ;
struct TYPE_6__ {TYPE_1__ super; } ;
typedef  TYPE_2__ fz_zip_archive ;
typedef  int /*<<< orphan*/  fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  SEEK_END ; 
 size_t fz_minz (size_t,int) ; 
 size_t fz_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  fz_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t fz_tell (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcmp (unsigned char*,char*,int) ; 
 int /*<<< orphan*/  read_zip_dir_imp (int /*<<< orphan*/ *,TYPE_2__*,size_t) ; 

__attribute__((used)) static void ensure_zip_entries(fz_context *ctx, fz_zip_archive *zip)
{
	fz_stream *file = zip->super.file;
	unsigned char buf[512];
	size_t size, back, maxback;
	size_t i, n;

	fz_seek(ctx, file, 0, SEEK_END);
	size = fz_tell(ctx, file);

	maxback = fz_minz(size, 0xFFFF + sizeof buf);
	back = fz_minz(maxback, sizeof buf);

	while (back <= maxback)
	{
		fz_seek(ctx, file, (int64_t)(size - back), 0);
		n = fz_read(ctx, file, buf, sizeof buf);
		if (n < 4)
			break;
		for (i = n - 4; i > 0; i--)
			if (!memcmp(buf + i, "PK\5\6", 4))
			{
				read_zip_dir_imp(ctx, zip, size - back + i);
				return;
			}
		back += sizeof buf - 4;
	}

	fz_throw(ctx, FZ_ERROR_GENERIC, "cannot find end of central directory");
}