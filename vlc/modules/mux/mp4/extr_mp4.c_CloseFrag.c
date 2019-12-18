#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_22__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_19__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_24__ {int /*<<< orphan*/  psz_mux; scalar_t__ p_sys; } ;
typedef  TYPE_1__ sout_mux_t ;
struct TYPE_26__ {unsigned int i_nb_streams; int /*<<< orphan*/  muxh; TYPE_3__** pp_streams; } ;
typedef  TYPE_2__ sout_mux_sys_t ;
struct TYPE_27__ {TYPE_22__* p_held_entry; int /*<<< orphan*/  read; } ;
typedef  TYPE_3__ mp4_stream_t ;
struct TYPE_28__ {scalar_t__ b; } ;
typedef  TYPE_4__ bo_t ;
struct TYPE_25__ {TYPE_19__* p_block; } ;
struct TYPE_23__ {int i_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENQUEUE_ENTRY (int /*<<< orphan*/ ,TYPE_22__*) ; 
 TYPE_4__* GetMfraBox (TYPE_1__*) ; 
 int /*<<< orphan*/  LengthLocalFixup (TYPE_1__*,TYPE_3__*,TYPE_19__*) ; 
 scalar_t__ MP4_MFRO_BOXSIZE ; 
 int /*<<< orphan*/  TAB_CLEAN (unsigned int,TYPE_3__**) ; 
 int /*<<< orphan*/  WriteFragments (TYPE_1__*,int) ; 
 int /*<<< orphan*/  bo_add_32be (TYPE_4__*,scalar_t__) ; 
 scalar_t__ bo_size (TYPE_4__*) ; 
 int /*<<< orphan*/  box_fix (TYPE_4__*,scalar_t__) ; 
 TYPE_4__* box_full_new (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  box_gather (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  box_send (TYPE_1__*,TYPE_4__*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  mp4_stream_Delete (TYPE_3__*) ; 
 int /*<<< orphan*/  mp4mux_Delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void CloseFrag(vlc_object_t *p_this)
{
    sout_mux_t *p_mux = (sout_mux_t *) p_this;
    sout_mux_sys_t *p_sys = (sout_mux_sys_t*) p_mux->p_sys;

    /* Flush remaining entries */
    for (unsigned int i = 0; i < p_sys->i_nb_streams; i++)
    {
        mp4_stream_t *p_stream = p_sys->pp_streams[i];
        if (p_stream->p_held_entry)
        {
            if (p_stream->p_held_entry->p_block->i_length < 1)
                LengthLocalFixup(p_mux, p_stream, p_stream->p_held_entry->p_block);
            ENQUEUE_ENTRY(p_stream->read, p_stream->p_held_entry);
            p_stream->p_held_entry = NULL;
        }
    }

    /* and force creating a fragment from it */
    WriteFragments(p_mux, true);

    /* Write indexes, but only for non streamed content
       as they refer to moof by absolute position */
    if (!strcmp(p_mux->psz_mux, "mp4frag"))
    {
        bo_t *mfra = GetMfraBox(p_mux);
        if (mfra)
        {
            bo_t *mfro = box_full_new("mfro", 0, 0x0);
            if (mfro)
            {
                if (mfra->b)
                {
                    box_fix(mfra, bo_size(mfra));
                    bo_add_32be(mfro, bo_size(mfra) + MP4_MFRO_BOXSIZE);
                }
                box_gather(mfra, mfro);
            }
            box_send(p_mux, mfra);
        }
    }

    for (unsigned int i = 0; i < p_sys->i_nb_streams; i++)
        mp4_stream_Delete(p_sys->pp_streams[i]);
    TAB_CLEAN(p_sys->i_nb_streams, p_sys->pp_streams);
    mp4mux_Delete(p_sys->muxh);
    free(p_sys);
}