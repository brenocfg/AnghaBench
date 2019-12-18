#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* p_sectors; } ;
typedef  TYPE_3__ vcddev_toc_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_11__ {TYPE_5__* p_sys; } ;
typedef  TYPE_4__ stream_t ;
struct TYPE_12__ {int i_current_title; unsigned int i_current_seekpoint; TYPE_2__* titles; scalar_t__ i_sector; scalar_t__ offset; TYPE_3__* p_toc; } ;
typedef  TYPE_5__ access_sys_t ;
struct TYPE_9__ {unsigned int count; scalar_t__* seekpoints; } ;
struct TYPE_8__ {scalar_t__ i_lba; } ;

/* Variables and functions */
 scalar_t__ VCD_DATA_SIZE ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_4__*,char*) ; 

__attribute__((used)) static int Seek( stream_t *p_access, uint64_t i_pos )
{
    access_sys_t *p_sys = p_access->p_sys;
    const vcddev_toc_t *p_toc = p_sys->p_toc;
    int i_title = p_sys->i_current_title;
    unsigned i_seekpoint;

    /* Next sector to read */
    p_sys->offset = i_pos;
    p_sys->i_sector = i_pos / VCD_DATA_SIZE + p_toc->p_sectors[i_title + 1].i_lba;

    /* Update current seekpoint */
    for( i_seekpoint = 0; i_seekpoint < p_sys->titles[i_title].count; i_seekpoint++ )
    {
        if( i_seekpoint + 1 >= p_sys->titles[i_title].count ) break;
        if( 0 < p_sys->titles[i_title].seekpoints[i_seekpoint + 1] &&
            i_pos < p_sys->titles[i_title].seekpoints[i_seekpoint + 1] ) break;
    }

    if( i_seekpoint != p_sys->i_current_seekpoint )
    {
        msg_Dbg( p_access, "seekpoint change" );
        p_sys->i_current_seekpoint = i_seekpoint;
    }

    return VLC_SUCCESS;
}