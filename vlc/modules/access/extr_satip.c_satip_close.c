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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_5__ {int /*<<< orphan*/  control; int /*<<< orphan*/  content_base; int /*<<< orphan*/  tcp_sock; int /*<<< orphan*/  rtcp_sock; int /*<<< orphan*/  udp_sock; int /*<<< orphan*/  fifo; int /*<<< orphan*/  thread; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  block_FifoRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_Close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  satip_teardown (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void satip_close(vlc_object_t *obj)
{
    stream_t *access = (stream_t *)obj;
    access_sys_t *sys = access->p_sys;

    vlc_cancel(sys->thread);
    vlc_join(sys->thread, NULL);

    satip_teardown(access);

    block_FifoRelease(sys->fifo);
    net_Close(sys->udp_sock);
    net_Close(sys->rtcp_sock);
    net_Close(sys->tcp_sock);
    free(sys->content_base);
    free(sys->control);
}