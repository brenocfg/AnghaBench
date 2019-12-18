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
typedef  int /*<<< orphan*/  system_ids_t ;
struct TYPE_6__ {TYPE_1__* p_sessions; int /*<<< orphan*/  obj; } ;
typedef  TYPE_2__ cam_t ;
struct TYPE_5__ {int /*<<< orphan*/  p_sys; int /*<<< orphan*/  pf_close; int /*<<< orphan*/  pf_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  AOT_CA_INFO_ENQ ; 
 int /*<<< orphan*/  APDUSend (TYPE_2__*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConditionalAccessClose ; 
 int /*<<< orphan*/  ConditionalAccessHandle ; 
 int /*<<< orphan*/  calloc (int,int) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 

__attribute__((used)) static void ConditionalAccessOpen( cam_t * p_cam, unsigned i_session_id )
{
    msg_Dbg( p_cam->obj, "opening ConditionalAccess session (%u)",
             i_session_id );
    p_cam->p_sessions[i_session_id - 1].pf_handle = ConditionalAccessHandle;
    p_cam->p_sessions[i_session_id - 1].pf_close = ConditionalAccessClose;
    p_cam->p_sessions[i_session_id - 1].p_sys = calloc( 1, sizeof(system_ids_t) );

    APDUSend( p_cam, i_session_id, AOT_CA_INFO_ENQ, NULL, 0 );
}