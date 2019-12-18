#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* p; } ;
typedef  TYPE_2__ vout_thread_t ;
struct TYPE_8__ {int /*<<< orphan*/  configuration; int /*<<< orphan*/  src_fmt; int /*<<< orphan*/  chain_static; int /*<<< orphan*/  chain_interactive; } ;
struct TYPE_10__ {int /*<<< orphan*/  original; int /*<<< orphan*/ * clock; int /*<<< orphan*/  (* mouse_event ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;scalar_t__ spu; int /*<<< orphan*/  mouse_opaque; int /*<<< orphan*/ * display_pool; int /*<<< orphan*/ * decoder_fifo; TYPE_1__ filter; int /*<<< orphan*/  display_lock; int /*<<< orphan*/ * display; int /*<<< orphan*/ * spu_blend; } ;
typedef  TYPE_3__ vout_thread_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  INT64_MAX ; 
 int /*<<< orphan*/  ThreadDelAllFilterCallbacks (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filter_DeleteBlend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  filter_chain_Delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  picture_fifo_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spu_Detach (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_CloseWrapper (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_FlushUnlocked (TYPE_2__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vout_ReleaseDisplay(vout_thread_t *vout)
{
    vout_thread_sys_t *sys = vout->p;

    assert(sys->display != NULL);

    if (sys->spu_blend != NULL)
        filter_DeleteBlend(sys->spu_blend);

    /* Destroy the rendering display */
    if (sys->display_pool != NULL)
        vout_FlushUnlocked(vout, true, INT64_MAX);

    vlc_mutex_lock(&sys->display_lock);
    vout_CloseWrapper(vout, sys->display);
    sys->display = NULL;
    vlc_mutex_unlock(&sys->display_lock);

    /* Destroy the video filters */
    ThreadDelAllFilterCallbacks(vout);
    filter_chain_Delete(sys->filter.chain_interactive);
    filter_chain_Delete(sys->filter.chain_static);
    video_format_Clean(&sys->filter.src_fmt);
    free(sys->filter.configuration);

    if (sys->decoder_fifo != NULL)
    {
        picture_fifo_Delete(sys->decoder_fifo);
        sys->decoder_fifo = NULL;
    }
    assert(sys->display_pool == NULL);

    if (sys->mouse_event)
        sys->mouse_event(NULL, sys->mouse_opaque);

    if (sys->spu)
        spu_Detach(sys->spu);
    sys->mouse_event = NULL;
    sys->clock = NULL;
    video_format_Clean(&sys->original);
}