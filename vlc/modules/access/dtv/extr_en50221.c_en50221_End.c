#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  fd; TYPE_1__* p_sessions; int /*<<< orphan*/ ** pp_selected_programs; } ;
typedef  TYPE_2__ cam_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* pf_close ) (TYPE_2__*,unsigned int) ;scalar_t__ i_resource_id; } ;

/* Variables and functions */
 unsigned int MAX_PROGRAMS ; 
 unsigned int MAX_SESSIONS ; 
 int /*<<< orphan*/  en50221_capmt_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  vlc_close (int /*<<< orphan*/ ) ; 

void en50221_End( cam_t * p_cam )
{
    for( unsigned i = 0; i < MAX_PROGRAMS; i++ )
    {
        if( p_cam->pp_selected_programs[i] != NULL )
        {
            en50221_capmt_Delete( p_cam->pp_selected_programs[i] );
        }
    }

    for( unsigned i = 1; i <= MAX_SESSIONS; i++ )
    {
        if( p_cam->p_sessions[i - 1].i_resource_id
              && p_cam->p_sessions[i - 1].pf_close != NULL )
        {
            p_cam->p_sessions[i - 1].pf_close( p_cam, i );
        }
    }

    vlc_close( p_cam->fd );
    free( p_cam );
}