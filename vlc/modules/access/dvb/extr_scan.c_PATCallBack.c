#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_8__ {TYPE_3__* p_pat; } ;
struct TYPE_9__ {int /*<<< orphan*/  i_nit_pid; TYPE_1__ local; int /*<<< orphan*/ * p_obj; } ;
typedef  TYPE_2__ scan_session_t ;
struct TYPE_10__ {TYPE_4__* p_first_program; scalar_t__ b_current_next; int /*<<< orphan*/  i_version; int /*<<< orphan*/  i_ts_id; } ;
typedef  TYPE_3__ dvbpsi_pat_t ;
struct TYPE_11__ {scalar_t__ i_number; int /*<<< orphan*/  i_pid; struct TYPE_11__* p_next; } ;
typedef  TYPE_4__ dvbpsi_pat_program_t ;

/* Variables and functions */
 int /*<<< orphan*/  dvbpsi_pat_delete (TYPE_3__*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void PATCallBack( scan_session_t *p_session, dvbpsi_pat_t *p_pat )
{
    vlc_object_t *p_obj = p_session->p_obj;

    /* */
    if( p_session->local.p_pat && p_session->local.p_pat->b_current_next )
    {
        dvbpsi_pat_delete( p_session->local.p_pat );
        p_session->local.p_pat = NULL;
    }
    if( p_session->local.p_pat )
    {
        dvbpsi_pat_delete( p_pat );
        return;
    }

    dvbpsi_pat_program_t *p_program;

    /* */
    p_session->local.p_pat = p_pat;

    /* */
    msg_Dbg( p_obj, "new PAT ts_id=%d version=%d current_next=%d",
             p_pat->i_ts_id, p_pat->i_version, p_pat->b_current_next );
    for( p_program = p_pat->p_first_program; p_program != NULL; p_program = p_program->p_next )
    {
        msg_Dbg( p_obj, "  * number=%d pid=%d", p_program->i_number, p_program->i_pid );
        if( p_program->i_number == 0 )
            p_session->i_nit_pid = p_program->i_pid;
    }
}