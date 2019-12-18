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
typedef  int /*<<< orphan*/  mmi_t ;
struct TYPE_5__ {int* pb_slot_mmi_expected; int* pb_slot_mmi_undisplayed; int /*<<< orphan*/  obj; TYPE_1__* p_sessions; } ;
typedef  TYPE_2__ cam_t ;
struct TYPE_4__ {int i_slot; scalar_t__ p_sys; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMIFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void MMIClose( cam_t *p_cam, int i_session_id )
{
    int i_slot = p_cam->p_sessions[i_session_id - 1].i_slot;
    mmi_t *p_mmi = (mmi_t *)p_cam->p_sessions[i_session_id - 1].p_sys;

    MMIFree( p_mmi );
    free( p_cam->p_sessions[i_session_id - 1].p_sys );

    msg_Dbg( p_cam->obj, "closing MMI session (%d)", i_session_id );
    p_cam->pb_slot_mmi_expected[i_slot] = false;
    p_cam->pb_slot_mmi_undisplayed[i_slot] = true;
}