#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_8__ {scalar_t__ pos; scalar_t__ wp; scalar_t__ rp; int /*<<< orphan*/  seek; } ;
typedef  TYPE_1__ fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_9__ {scalar_t__ len; scalar_t__ data; } ;
typedef  TYPE_2__ fz_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  drop_buffer ; 
 int /*<<< orphan*/  fz_keep_buffer (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_1__* fz_new_stream (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next_buffer ; 
 int /*<<< orphan*/  seek_buffer ; 

fz_stream *
fz_open_buffer(fz_context *ctx, fz_buffer *buf)
{
	fz_stream *stm;

	fz_keep_buffer(ctx, buf);
	stm = fz_new_stream(ctx, buf, next_buffer, drop_buffer);
	stm->seek = seek_buffer;

	stm->rp = buf->data;
	stm->wp = buf->data + buf->len;

	stm->pos = (int64_t)buf->len;

	return stm;
}