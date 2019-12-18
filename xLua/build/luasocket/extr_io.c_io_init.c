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
typedef  int /*<<< orphan*/  p_send ;
typedef  int /*<<< orphan*/  p_recv ;
typedef  TYPE_1__* p_io ;
typedef  int /*<<< orphan*/  p_error ;
struct TYPE_3__ {void* ctx; int /*<<< orphan*/  error; int /*<<< orphan*/  recv; int /*<<< orphan*/  send; } ;

/* Variables and functions */

void io_init(p_io io, p_send send, p_recv recv, p_error error, void *ctx) {
    io->send = send;
    io->recv = recv;
    io->error = error;
    io->ctx = ctx;
}