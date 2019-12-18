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
struct TYPE_4__ {int /*<<< orphan*/  as_stream; int /*<<< orphan*/  tell; int /*<<< orphan*/  seek; } ;
typedef  TYPE_1__ fz_output ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  _IONBF ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  file_as_stream ; 
 int /*<<< orphan*/ * file_drop ; 
 int /*<<< orphan*/  file_seek ; 
 int /*<<< orphan*/  file_tell ; 
 int /*<<< orphan*/  file_write ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/ * fz_fopen_utf8 (char const*,char*) ; 
 TYPE_1__* fz_new_output (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ fz_remove_utf8 (char const*) ; 
 int /*<<< orphan*/  fz_strcasecmp (char const*,char*) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  null_write ; 
 scalar_t__ remove (char const*) ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 

fz_output *
fz_new_output_with_path(fz_context *ctx, const char *filename, int append)
{
	FILE *file;
	fz_output *out;

	if (!strcmp(filename, "/dev/null") || !fz_strcasecmp(filename, "nul:"))
		return fz_new_output(ctx, 0, NULL, null_write, NULL, NULL);

#ifdef _WIN32
	/* Ensure we create a brand new file. We don't want to clobber our old file. */
	if (!append)
	{
		if (fz_remove_utf8(filename) < 0)
			if (errno != ENOENT)
				fz_throw(ctx, FZ_ERROR_GENERIC, "cannot remove file '%s': %s", filename, strerror(errno));
	}
	file = fz_fopen_utf8(filename, append ? "rb+" : "wb+");
#else
	/* Ensure we create a brand new file. We don't want to clobber our old file. */
	if (!append)
	{
		if (remove(filename) < 0)
			if (errno != ENOENT)
				fz_throw(ctx, FZ_ERROR_GENERIC, "cannot remove file '%s': %s", filename, strerror(errno));
	}
	file = fopen(filename, append ? "rb+" : "wb+");
#endif
	if (!file)
		fz_throw(ctx, FZ_ERROR_GENERIC, "cannot open file '%s': %s", filename, strerror(errno));

	setvbuf(file, NULL, _IONBF, 0); /* we do our own buffering */
	out = fz_new_output(ctx, 8192, file, file_write, NULL, file_drop);
	out->seek = file_seek;
	out->tell = file_tell;
	out->as_stream = file_as_stream;

	return out;
}