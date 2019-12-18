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
struct TYPE_5__ {TYPE_1__* p_sessions; int /*<<< orphan*/  obj; } ;
typedef  TYPE_2__ cam_t ;
struct TYPE_4__ {int /*<<< orphan*/  p_sys; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void ConditionalAccessClose( cam_t * p_cam, int i_session_id )
{
    msg_Dbg( p_cam->obj, "closing ConditionalAccess session (%d)",
             i_session_id );
    free( p_cam->p_sessions[i_session_id - 1].p_sys );
}