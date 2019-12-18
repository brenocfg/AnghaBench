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
typedef  TYPE_1__ services_discovery_t ;
struct TYPE_5__ {int /*<<< orphan*/  pi_fd; int /*<<< orphan*/  i_fd; } ;
typedef  TYPE_2__ services_discovery_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  SHUT_WR ; 
 int /*<<< orphan*/  TAB_APPEND (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int net_ListenUDP1 (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  shutdown (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int InitSocket( services_discovery_t *p_sd, const char *psz_address,
                       int i_port )
{
    int i_fd = net_ListenUDP1 ((vlc_object_t *)p_sd, psz_address, i_port);
    if (i_fd == -1)
        return VLC_EGENERIC;

    shutdown( i_fd, SHUT_WR );
    services_discovery_sys_t *p_sys = p_sd->p_sys;
    TAB_APPEND(p_sys->i_fd, p_sys->pi_fd, i_fd);
    return VLC_SUCCESS;
}