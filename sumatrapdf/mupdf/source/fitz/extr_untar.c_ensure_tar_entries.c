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
typedef  int int64_t ;
struct TYPE_6__ {int /*<<< orphan*/ * file; } ;
struct TYPE_7__ {int count; TYPE_3__* entries; TYPE_1__ super; } ;
typedef  TYPE_2__ fz_tar_archive ;
typedef  int /*<<< orphan*/  fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_8__ {int offset; int size; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int INT_MAX ; 
 int SEEK_SET ; 
 size_t fz_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*,int) ; 
 char fz_read_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* fz_realloc_array (int /*<<< orphan*/ *,TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  fz_strdup (int /*<<< orphan*/ *,char*) ; 
 int fz_tell (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int nelem (char*) ; 
 int otoi (char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  tar_entry ; 

__attribute__((used)) static void ensure_tar_entries(fz_context *ctx, fz_tar_archive *tar)
{
	fz_stream *file = tar->super.file;
	char name[100];
	char octsize[12];
	char typeflag;
	int64_t offset, blocks, size;
	size_t n;

	tar->count = 0;

	fz_seek(ctx, file, 0, SEEK_SET);

	while (1)
	{
		offset = fz_tell(ctx, file);
		n = fz_read(ctx, file, (unsigned char *) name, nelem(name));
		if (n < nelem(name))
			fz_throw(ctx, FZ_ERROR_GENERIC, "premature end of data in tar entry name");
		name[nelem(name) - 1] = '\0';

		if (strlen(name) == 0)
			break;

		fz_seek(ctx, file, 24, 1);
		n = fz_read(ctx, file, (unsigned char *) octsize, nelem(octsize));
		if (n < nelem(octsize))
			fz_throw(ctx, FZ_ERROR_GENERIC, "premature end of data in tar entry size");
		octsize[nelem(octsize) - 1] = '\0';
		size = otoi(octsize);
		if (size > INT_MAX)
			fz_throw(ctx, FZ_ERROR_GENERIC, "tar archive entry too large");

		fz_seek(ctx, file, 20, 1);
		typeflag = fz_read_byte(ctx, file);

		fz_seek(ctx, file, 355, 1);
		blocks = (size + 511) / 512;
		fz_seek(ctx, file, blocks * 512, 1);

		if (typeflag != '0' && typeflag != '\0')
			continue;

		tar->entries = fz_realloc_array(ctx, tar->entries, tar->count + 1, tar_entry);

		tar->entries[tar->count].name = fz_strdup(ctx, name);
		tar->entries[tar->count].offset = offset;
		tar->entries[tar->count].size = size;

		tar->count++;
	}
}