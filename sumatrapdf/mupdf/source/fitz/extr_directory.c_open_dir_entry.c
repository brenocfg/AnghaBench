#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_stream ;
struct TYPE_2__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ fz_directory ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_archive ;

/* Variables and functions */
 int /*<<< orphan*/ * fz_open_file (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fz_strlcat (char*,char const*,int) ; 
 int /*<<< orphan*/  fz_strlcpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static fz_stream *open_dir_entry(fz_context *ctx, fz_archive *arch, const char *name)
{
	fz_directory *dir = (fz_directory *) arch;
	char path[2048];
	fz_strlcpy(path, dir->path, sizeof path);
	fz_strlcat(path, "/", sizeof path);
	fz_strlcat(path, name, sizeof path);
	return fz_open_file(ctx, path);
}