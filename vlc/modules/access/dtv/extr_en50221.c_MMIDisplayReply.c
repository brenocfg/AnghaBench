#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  obj; } ;
typedef  TYPE_1__ cam_t ;

/* Variables and functions */
 int /*<<< orphan*/  AOT_DISPLAY_REPLY ; 
 int /*<<< orphan*/  APDUSend (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  DRI_MMI_MODE_ACK ; 
 int /*<<< orphan*/  MM_HIGH_LEVEL ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void MMIDisplayReply( cam_t *p_cam, int i_session_id )
{
    uint8_t p_response[2];

    p_response[0] = DRI_MMI_MODE_ACK;
    p_response[1] = MM_HIGH_LEVEL;

    APDUSend( p_cam, i_session_id, AOT_DISPLAY_REPLY, p_response, 2 );

    msg_Dbg( p_cam->obj, "sending DisplayReply on session (%d)", i_session_id );
}