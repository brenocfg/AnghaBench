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
typedef  scalar_t__ int64_t ;
struct TYPE_4__ {unsigned char* rp; unsigned char* wp; scalar_t__ pos; int /*<<< orphan*/  seek; } ;
typedef  TYPE_1__ fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 TYPE_1__* fz_new_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next_buffer ; 
 int /*<<< orphan*/  seek_buffer ; 

fz_stream *
fz_open_memory(fz_context *ctx, const unsigned char *data, size_t len)
{
	fz_stream *stm;

	stm = fz_new_stream(ctx, NULL, next_buffer, NULL);
	stm->seek = seek_buffer;

	stm->rp = (unsigned char *)data;
	stm->wp = (unsigned char *)data + len;

	stm->pos = (int64_t)len;

	return stm;
}