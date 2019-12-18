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
typedef  int /*<<< orphan*/  tar_entry ;
typedef  int /*<<< orphan*/  fz_tar_archive ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_archive ;

/* Variables and functions */
 int /*<<< orphan*/ * lookup_tar_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int has_tar_entry(fz_context *ctx, fz_archive *arch, const char *name)
{
	fz_tar_archive *tar = (fz_tar_archive *) arch;
	tar_entry *ent = lookup_tar_entry(ctx, tar, name);
	return ent != NULL;
}