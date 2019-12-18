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
struct TYPE_4__ {int /*<<< orphan*/  drop; } ;
typedef  TYPE_1__ fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fz_free ; 
 TYPE_1__* fz_open_file_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

fz_stream *fz_open_file_ptr_no_close(fz_context *ctx, FILE *file)
{
	fz_stream *stm = fz_open_file_ptr(ctx, file);
	/* We don't own the file ptr. Ensure we don't close it */
	stm->drop = fz_free;
	return stm;
}