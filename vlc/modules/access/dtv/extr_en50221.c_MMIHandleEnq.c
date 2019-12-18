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
typedef  int uint8_t ;
struct TYPE_9__ {int b_blind; char* psz_text; } ;
struct TYPE_10__ {TYPE_2__ enq; } ;
struct TYPE_11__ {TYPE_3__ u; int /*<<< orphan*/  i_object_type; } ;
typedef  TYPE_4__ mmi_t ;
struct TYPE_12__ {int* pb_slot_mmi_expected; int* pb_slot_mmi_undisplayed; int /*<<< orphan*/  obj; TYPE_1__* p_sessions; } ;
typedef  TYPE_5__ cam_t ;
struct TYPE_8__ {int i_slot; scalar_t__ p_sys; } ;

/* Variables and functions */
 int* APDUGetLength (int*,int*) ; 
 int /*<<< orphan*/  EN50221_MMI_ENQ ; 
 int /*<<< orphan*/  MMIFree (TYPE_4__*) ; 
 int /*<<< orphan*/  VLC_UNUSED (int) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 char* xmalloc (int) ; 

__attribute__((used)) static void MMIHandleEnq( cam_t *p_cam, int i_session_id,
                          uint8_t *p_apdu, int i_size )
{
    VLC_UNUSED( i_size );

    mmi_t *p_mmi = (mmi_t *)p_cam->p_sessions[i_session_id - 1].p_sys;
    int i_slot = p_cam->p_sessions[i_session_id - 1].i_slot;
    int l;
    uint8_t *d = APDUGetLength( p_apdu, &l );

    MMIFree( p_mmi );
    p_mmi->i_object_type = EN50221_MMI_ENQ;
    p_mmi->u.enq.b_blind = (*d & 0x1) ? true : false;
    d += 2; /* skip answer_text_length because it is not mandatory */
    l -= 2;
    p_mmi->u.enq.psz_text = xmalloc( l + 1 );
    strncpy( p_mmi->u.enq.psz_text, (char *)d, l );
    p_mmi->u.enq.psz_text[l] = '\0';

    msg_Dbg( p_cam->obj, "MMI enq: %s%s", p_mmi->u.enq.psz_text,
             p_mmi->u.enq.b_blind ? " (blind)" : "" );
    p_cam->pb_slot_mmi_expected[i_slot] = false;
    p_cam->pb_slot_mmi_undisplayed[i_slot] = true;
}