#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  i_object_type; } ;
typedef  TYPE_2__ mmi_t ;
struct TYPE_7__ {TYPE_1__* p_sessions; int /*<<< orphan*/  obj; } ;
typedef  TYPE_3__ cam_t ;
struct TYPE_5__ {scalar_t__ p_sys; int /*<<< orphan*/  pf_close; int /*<<< orphan*/  pf_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  EN50221_MMI_NONE ; 
 int /*<<< orphan*/  MMIClose ; 
 int /*<<< orphan*/  MMIHandle ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static void MMIOpen( cam_t *p_cam, unsigned i_session_id )
{
    mmi_t *p_mmi;

    msg_Dbg( p_cam->obj, "opening MMI session (%u)", i_session_id );

    p_cam->p_sessions[i_session_id - 1].pf_handle = MMIHandle;
    p_cam->p_sessions[i_session_id - 1].pf_close = MMIClose;
    p_cam->p_sessions[i_session_id - 1].p_sys = xmalloc(sizeof(mmi_t));
    p_mmi = (mmi_t *)p_cam->p_sessions[i_session_id - 1].p_sys;
    p_mmi->i_object_type = EN50221_MMI_NONE;
}