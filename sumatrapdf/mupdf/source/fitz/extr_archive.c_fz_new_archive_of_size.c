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
struct TYPE_4__ {int /*<<< orphan*/  file; } ;
typedef  TYPE_1__ fz_archive ;

/* Variables and functions */
 TYPE_1__* Memento_label (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fz_calloc (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  fz_keep_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

fz_archive *
fz_new_archive_of_size(fz_context *ctx, fz_stream *file, int size)
{
	fz_archive *arch;
	arch = Memento_label(fz_calloc(ctx, 1, size), "fz_archive");
	arch->file = fz_keep_stream(ctx, file);
	return arch;
}