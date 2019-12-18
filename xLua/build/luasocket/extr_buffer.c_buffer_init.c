#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  p_timeout ;
typedef  int /*<<< orphan*/  p_io ;
typedef  TYPE_1__* p_buffer ;
struct TYPE_3__ {int /*<<< orphan*/  birthday; scalar_t__ sent; scalar_t__ received; int /*<<< orphan*/  tm; int /*<<< orphan*/  io; scalar_t__ last; scalar_t__ first; } ;

/* Variables and functions */
 int /*<<< orphan*/  timeout_gettime () ; 

void buffer_init(p_buffer buf, p_io io, p_timeout tm) {
    buf->first = buf->last = 0;
    buf->io = io;
    buf->tm = tm;
    buf->received = buf->sent = 0;
    buf->birthday = timeout_gettime();
}