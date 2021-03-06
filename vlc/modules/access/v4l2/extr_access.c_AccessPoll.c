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
struct pollfd {int /*<<< orphan*/  events; int /*<<< orphan*/  fd; } ;
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_5__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_2__ access_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  POLLIN ; 
 int vlc_poll_i11e (struct pollfd*,int,int) ; 

__attribute__((used)) static int AccessPoll (stream_t *access)
{
    access_sys_t *sys = access->p_sys;
    struct pollfd ufd;

    ufd.fd = sys->fd;
    ufd.events = POLLIN;

    return vlc_poll_i11e (&ufd, 1, -1);
}