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
typedef  int /*<<< orphan*/  fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_4__ {int /*<<< orphan*/ * (* open_entry ) (int /*<<< orphan*/ *,TYPE_1__*,char const*) ;} ;
typedef  TYPE_1__ fz_archive ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *,TYPE_1__*,char const*) ; 

fz_stream *
fz_open_archive_entry(fz_context *ctx, fz_archive *arch, const char *name)
{
	if (!arch->open_entry)
		fz_throw(ctx, FZ_ERROR_GENERIC, "cannot open archive entry");
	return arch->open_entry(ctx, arch, name);
}