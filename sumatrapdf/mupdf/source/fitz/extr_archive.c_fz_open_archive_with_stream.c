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
typedef  int /*<<< orphan*/  fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_archive ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 scalar_t__ fz_is_tar_archive (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ fz_is_zip_archive (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fz_open_tar_archive_with_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fz_open_zip_archive_with_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

fz_archive *
fz_open_archive_with_stream(fz_context *ctx, fz_stream *file)
{
	fz_archive *arch = NULL;

	if (fz_is_zip_archive(ctx, file))
		arch = fz_open_zip_archive_with_stream(ctx, file);
	else if (fz_is_tar_archive(ctx, file))
		arch = fz_open_tar_archive_with_stream(ctx, file);
	else
		fz_throw(ctx, FZ_ERROR_GENERIC, "cannot recognize archive");

	return arch;
}