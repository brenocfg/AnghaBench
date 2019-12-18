#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ sout_mux_t ;
struct TYPE_12__ {int /*<<< orphan*/  i_pos; int /*<<< orphan*/  i_mdat_pos; int /*<<< orphan*/  muxh; } ;
typedef  TYPE_2__ sout_mux_sys_t ;
struct TYPE_13__ {scalar_t__ b; } ;
typedef  TYPE_3__ bo_t ;

/* Variables and functions */
 int /*<<< orphan*/  QUICKTIME ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  bo_add_64be (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ bo_size (TYPE_3__*) ; 
 TYPE_3__* box_new (char*) ; 
 int /*<<< orphan*/  box_send (TYPE_1__*,TYPE_3__*) ; 
 TYPE_3__* mp4mux_GetFtyp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp4mux_Is (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int WriteSlowStartHeader(sout_mux_t *p_mux)
{
    sout_mux_sys_t *p_sys = p_mux->p_sys;
    bo_t *box;

    if (!mp4mux_Is(p_sys->muxh, QUICKTIME))
    {
        /* Now add ftyp header */
        box = mp4mux_GetFtyp(p_sys->muxh);
        if(!box)
            return VLC_ENOMEM;

        p_sys->i_pos += bo_size(box);
        p_sys->i_mdat_pos = p_sys->i_pos;
        box_send(p_mux, box);
    }

    /* Now add mdat header */
    box = box_new("mdat");
    if(!box)
        return VLC_ENOMEM;

    bo_add_64be(box, 0); // enough to store an extended size

    if(box->b)
        p_sys->i_pos += bo_size(box);

    box_send(p_mux, box);

    return VLC_SUCCESS;
}