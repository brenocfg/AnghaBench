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
struct TYPE_5__ {struct TYPE_5__* psz_mcast_ip; struct TYPE_5__* psz_password; struct TYPE_5__* psz_user; struct TYPE_5__* psz_name; struct TYPE_5__* psz_location; struct TYPE_5__* psz_server; struct TYPE_5__* psz_uri; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 

void Close_SGIMB( vlc_object_t *p_this )
{
    stream_t *p_demux = (stream_t*)p_this;
    demux_sys_t *p_sys = p_demux->p_sys;
    free( p_sys->psz_uri );
    free( p_sys->psz_server );
    free( p_sys->psz_location );
    free( p_sys->psz_name );
    free( p_sys->psz_user );
    free( p_sys->psz_password );
    free( p_sys->psz_mcast_ip );
    free( p_demux->p_sys );
    return;
}