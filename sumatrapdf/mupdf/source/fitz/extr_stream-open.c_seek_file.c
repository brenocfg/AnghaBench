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
typedef  scalar_t__ int64_t ;
struct TYPE_4__ {int /*<<< orphan*/  wp; int /*<<< orphan*/  rp; int /*<<< orphan*/  pos; TYPE_2__* state; } ;
typedef  TYPE_1__ fz_stream ;
struct TYPE_5__ {int /*<<< orphan*/  buffer; int /*<<< orphan*/  file; } ;
typedef  TYPE_2__ fz_file_stream ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 scalar_t__ _fseeki64 (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  _ftelli64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fseeko (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  ftello (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void seek_file(fz_context *ctx, fz_stream *stm, int64_t offset, int whence)
{
	fz_file_stream *state = stm->state;
#ifdef _WIN32
	int64_t n = _fseeki64(state->file, offset, whence);
#else
	int64_t n = fseeko(state->file, offset, whence);
#endif
	if (n < 0)
		fz_throw(ctx, FZ_ERROR_GENERIC, "cannot seek: %s", strerror(errno));
#ifdef _WIN32
	stm->pos = _ftelli64(state->file);
#else
	stm->pos = ftello(state->file);
#endif
	stm->rp = state->buffer;
	stm->wp = state->buffer;
}