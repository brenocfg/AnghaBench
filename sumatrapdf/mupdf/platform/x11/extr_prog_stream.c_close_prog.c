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
struct TYPE_2__ {int /*<<< orphan*/  file; } ;
typedef  TYPE_1__ prog_state ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void close_prog(fz_context *ctx, void *state)
{
	prog_state *ps = (prog_state *)state;
	int n = fclose(ps->file);
	if (n < 0)
		fz_warn(ctx, "cannot fclose: %s", strerror(errno));
	fz_free(ctx, state);
}