#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_6__ {scalar_t__ p_sys; } ;
typedef  TYPE_1__ sout_mux_t ;
struct TYPE_7__ {unsigned int i_nb_streams; TYPE_3__** pp_streams; } ;
typedef  TYPE_2__ sout_mux_sys_t ;
struct TYPE_8__ {int i_indexentries; TYPE_4__* p_indexentries; int /*<<< orphan*/  tinfo; } ;
typedef  TYPE_3__ mp4_stream_t ;
struct TYPE_9__ {int i_time; int i_moofoffset; int i_sample; int /*<<< orphan*/  i_trun; int /*<<< orphan*/  i_traf; } ;
typedef  TYPE_4__ mp4_fragindex_t ;
typedef  int /*<<< orphan*/  bo_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bo_add_32be (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bo_add_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * box_full_new (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  box_gather (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * box_new (char*) ; 
 int mp4mux_track_GetID (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bo_t *GetMfraBox(sout_mux_t *p_mux)
{
    sout_mux_sys_t *p_sys = (sout_mux_sys_t*) p_mux->p_sys;
    bo_t *mfra = NULL;
    for (unsigned int i = 0; i < p_sys->i_nb_streams; i++)
    {
        mp4_stream_t *p_stream = p_sys->pp_streams[i];
        if (p_stream->i_indexentries)
        {
            bo_t *tfra = box_full_new("tfra", 0, 0x0);
            if (!tfra) continue;
            bo_add_32be(tfra, mp4mux_track_GetID(p_stream->tinfo));
            bo_add_32be(tfra, 0x3); // reserved + lengths (1,1,4)=>(0,0,3)
            bo_add_32be(tfra, p_stream->i_indexentries);
            for(uint32_t i_index=0; i_index<p_stream->i_indexentries; i_index++)
            {
                const mp4_fragindex_t *p_indexentry = &p_stream->p_indexentries[i_index];
                bo_add_32be(tfra, p_indexentry->i_time);
                bo_add_32be(tfra, p_indexentry->i_moofoffset);
                assert(sizeof(p_indexentry->i_traf)==1); /* guard against sys changes */
                assert(sizeof(p_indexentry->i_trun)==1);
                assert(sizeof(p_indexentry->i_sample)==4);
                bo_add_8(tfra, p_indexentry->i_traf);
                bo_add_8(tfra, p_indexentry->i_trun);
                bo_add_32be(tfra, p_indexentry->i_sample);
            }

            if (!mfra && !(mfra = box_new("mfra")))
            {
                bo_free(tfra);
                return NULL;
            }

            box_gather(mfra,tfra);
        }
    }
    return mfra;
}