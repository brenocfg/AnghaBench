#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  file; scalar_t__ length; } ;
typedef  TYPE_1__ prog_state ;
typedef  scalar_t__ int64_t ;
struct TYPE_5__ {int /*<<< orphan*/  rp; int /*<<< orphan*/  wp; scalar_t__ pos; scalar_t__ state; } ;
typedef  TYPE_2__ fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int SEEK_CUR ; 
 int SEEK_END ; 
 int SEEK_SET ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fseek (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void seek_prog(fz_context *ctx, fz_stream *stm, int64_t offset, int whence)
{
	prog_state *ps = (prog_state *)stm->state;

	if (whence == SEEK_END)
	{
		whence = SEEK_SET;
		offset += ps->length;
	}
	else if (whence == SEEK_CUR)
	{
		whence = SEEK_SET;
		offset += stm->pos;
	}

	if (fseek(ps->file, offset, whence) != 0)
		fz_throw(ctx, FZ_ERROR_GENERIC, "cannot seek: %s", strerror(errno));
	stm->pos = offset;
	stm->wp = stm->rp;
}