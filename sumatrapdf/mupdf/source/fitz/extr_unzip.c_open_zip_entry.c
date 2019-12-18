#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  usize; } ;
typedef  TYPE_2__ zip_entry ;
struct TYPE_8__ {int /*<<< orphan*/ * file; } ;
struct TYPE_10__ {TYPE_1__ super; } ;
typedef  TYPE_3__ fz_zip_archive ;
typedef  int /*<<< orphan*/  fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_archive ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/ * fz_open_flated (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * fz_open_null_filter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_tell (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__* lookup_zip_entry (int /*<<< orphan*/ *,TYPE_3__*,char const*) ; 
 int read_zip_entry_header (int /*<<< orphan*/ *,TYPE_3__*,TYPE_2__*) ; 

__attribute__((used)) static fz_stream *open_zip_entry(fz_context *ctx, fz_archive *arch, const char *name)
{
	fz_zip_archive *zip = (fz_zip_archive *) arch;
	fz_stream *file = zip->super.file;
	int method;
	zip_entry *ent;

	ent = lookup_zip_entry(ctx, zip, name);
	if (!ent)
		fz_throw(ctx, FZ_ERROR_GENERIC, "cannot find named zip archive entry");

	method = read_zip_entry_header(ctx, zip, ent);
	if (method == 0)
		return fz_open_null_filter(ctx, file, ent->usize, fz_tell(ctx, file));
	if (method == 8)
		return fz_open_flated(ctx, file, -15);
	fz_throw(ctx, FZ_ERROR_GENERIC, "unknown zip method: %d", method);
}