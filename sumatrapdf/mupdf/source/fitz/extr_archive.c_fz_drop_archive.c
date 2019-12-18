#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_5__ {int /*<<< orphan*/  file; int /*<<< orphan*/  (* drop_archive ) (int /*<<< orphan*/ *,TYPE_1__*) ;} ;
typedef  TYPE_1__ fz_archive ;

/* Variables and functions */
 int /*<<< orphan*/  fz_drop_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_1__*) ; 

void
fz_drop_archive(fz_context *ctx, fz_archive *arch)
{
	if (!arch)
		return;

	if (arch->drop_archive)
		arch->drop_archive(ctx, arch);
	fz_drop_stream(ctx, arch->file);
	fz_free(ctx, arch);
}