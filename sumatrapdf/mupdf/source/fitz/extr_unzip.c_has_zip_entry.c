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
typedef  int /*<<< orphan*/  zip_entry ;
typedef  int /*<<< orphan*/  fz_zip_archive ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_archive ;

/* Variables and functions */
 int /*<<< orphan*/ * lookup_zip_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int has_zip_entry(fz_context *ctx, fz_archive *arch, const char *name)
{
	fz_zip_archive *zip = (fz_zip_archive *) arch;
	zip_entry *ent = lookup_zip_entry(ctx, zip, name);
	return ent != NULL;
}