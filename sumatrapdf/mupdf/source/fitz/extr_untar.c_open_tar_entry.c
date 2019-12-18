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
struct TYPE_7__ {int /*<<< orphan*/  size; scalar_t__ offset; } ;
typedef  TYPE_2__ tar_entry ;
struct TYPE_6__ {int /*<<< orphan*/ * file; } ;
struct TYPE_8__ {TYPE_1__ super; } ;
typedef  TYPE_3__ fz_tar_archive ;
typedef  int /*<<< orphan*/  fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_archive ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/ * fz_open_null_filter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_tell (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* lookup_tar_entry (int /*<<< orphan*/ *,TYPE_3__*,char const*) ; 

__attribute__((used)) static fz_stream *open_tar_entry(fz_context *ctx, fz_archive *arch, const char *name)
{
	fz_tar_archive *tar = (fz_tar_archive *) arch;
	fz_stream *file = tar->super.file;
	tar_entry *ent;

	ent = lookup_tar_entry(ctx, tar, name);
	if (!ent)
		fz_throw(ctx, FZ_ERROR_GENERIC, "cannot find named tar archive entry");

	fz_seek(ctx, file, ent->offset + 512, 0);
	return fz_open_null_filter(ctx, file, ent->size, fz_tell(ctx, file));
}