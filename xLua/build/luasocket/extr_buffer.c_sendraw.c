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
typedef  int /*<<< orphan*/  p_timeout ;
typedef  TYPE_1__* p_io ;
typedef  TYPE_2__* p_buffer ;
struct TYPE_5__ {size_t sent; int /*<<< orphan*/  tm; TYPE_1__* io; } ;
struct TYPE_4__ {int (* send ) (int /*<<< orphan*/ ,char const*,size_t,size_t*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int IO_DONE ; 
 size_t STEPSIZE ; 
 int stub1 (int /*<<< orphan*/ ,char const*,size_t,size_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sendraw(p_buffer buf, const char *data, size_t count, size_t *sent) {
    p_io io = buf->io;
    p_timeout tm = buf->tm;
    size_t total = 0;
    int err = IO_DONE;
    while (total < count && err == IO_DONE) {
        size_t done = 0;
        size_t step = (count-total <= STEPSIZE)? count-total: STEPSIZE;
        err = io->send(io->ctx, data+total, step, &done, tm);
        total += done;
    }
    *sent = total;
    buf->sent += total;
    return err;
}