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
struct TYPE_4__ {TYPE_2__* p_first_program; } ;
typedef  TYPE_1__ dvbpsi_pat_t ;
struct TYPE_5__ {int i_pid; struct TYPE_5__* p_next; } ;
typedef  TYPE_2__ dvbpsi_pat_program_t ;
typedef  int /*<<< orphan*/  demux_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int PATCheck( demux_t *p_demux, dvbpsi_pat_t *p_pat )
{
    /* Some Dreambox streams have all PMT set to same pid */
    int i_prev_pid = -1;
    for( dvbpsi_pat_program_t * p_program = p_pat->p_first_program;
         p_program != NULL;
         p_program = p_program->p_next )
    {
        if( p_program->i_pid == i_prev_pid )
        {
            msg_Warn( p_demux, "PAT check failed: duplicate program pid %d", i_prev_pid );
            return VLC_EGENERIC;
        }
        i_prev_pid = p_program->i_pid;
    }
    return VLC_SUCCESS;
}