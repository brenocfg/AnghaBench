#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  s; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_6__ {int /*<<< orphan*/ * p_root; } ;
typedef  TYPE_2__ demux_sys_t ;
typedef  int /*<<< orphan*/  MP4_Box_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP4_BoxFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MP4_BoxGet (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * MP4_BoxGetRoot (int /*<<< orphan*/ ) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*) ; 

__attribute__((used)) static int LoadInitFrag( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;

    /* Load all boxes ( except raw data ) */
    MP4_Box_t *p_root = MP4_BoxGetRoot( p_demux->s );
    if( p_root == NULL || !MP4_BoxGet( p_root, "/moov" ) )
    {
        MP4_BoxFree( p_root );
        goto LoadInitFragError;
    }

    p_sys->p_root = p_root;

    return VLC_SUCCESS;

LoadInitFragError:
    msg_Warn( p_demux, "MP4 plugin discarded (not a valid initialization chunk)" );
    return VLC_EGENERIC;
}