#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* p; } ;
typedef  TYPE_2__ spu_t ;
struct TYPE_8__ {int /*<<< orphan*/  fmtsrc; int /*<<< orphan*/  fmtdst; int /*<<< orphan*/  vector; int /*<<< orphan*/  output_cond; int /*<<< orphan*/  cond; int /*<<< orphan*/  lock; } ;
struct TYPE_11__ {size_t size; int /*<<< orphan*/ * data; } ;
struct TYPE_10__ {TYPE_1__ prerender; int /*<<< orphan*/  lock; TYPE_4__ channels; int /*<<< orphan*/  filter_chain_update; int /*<<< orphan*/  source_chain_update; int /*<<< orphan*/  filter_chain_lock; int /*<<< orphan*/  filter_chain_current; int /*<<< orphan*/  filter_chain; TYPE_2__* vout; int /*<<< orphan*/  source_chain_current; int /*<<< orphan*/  source_chain; scalar_t__ scale; scalar_t__ scale_yuvp; int /*<<< orphan*/  textlock; scalar_t__ text; } ;
typedef  TYPE_3__ spu_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  FilterRelease (scalar_t__) ; 
 int /*<<< orphan*/  SubFilterDelProxyCallbacks ; 
 int /*<<< orphan*/  SubSourceClean ; 
 int /*<<< orphan*/  SubSourceDelProxyCallbacks ; 
 int /*<<< orphan*/  filter_chain_Delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filter_chain_ForEach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spu_channel_Clean (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_vector_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_vector_destroy (TYPE_4__*) ; 

__attribute__((used)) static void spu_Cleanup(spu_t *spu)
{
    spu_private_t *sys = spu->p;

    if (sys->text)
        FilterRelease(sys->text);
    vlc_mutex_destroy(&sys->textlock);

    if (sys->scale_yuvp)
        FilterRelease(sys->scale_yuvp);

    if (sys->scale)
        FilterRelease(sys->scale);

    filter_chain_ForEach(sys->source_chain, SubSourceClean, spu);
    if (sys->vout)
        filter_chain_ForEach(sys->source_chain,
                             SubSourceDelProxyCallbacks, sys->vout);
    filter_chain_Delete(sys->source_chain);
    free(sys->source_chain_current);
    if (sys->vout)
        filter_chain_ForEach(sys->filter_chain,
                             SubFilterDelProxyCallbacks, sys->vout);
    filter_chain_Delete(sys->filter_chain);
    free(sys->filter_chain_current);
    vlc_mutex_destroy(&sys->filter_chain_lock);
    free(sys->source_chain_update);
    free(sys->filter_chain_update);

    /* Destroy all remaining subpictures */
    for (size_t i = 0; i < sys->channels.size; ++i)
        spu_channel_Clean(sys, &sys->channels.data[i]);

    vlc_vector_destroy(&sys->channels);

    vlc_mutex_destroy(&sys->lock);

    vlc_mutex_destroy(&sys->prerender.lock);
    vlc_cond_destroy(&sys->prerender.cond);
    vlc_cond_destroy(&sys->prerender.output_cond);
    vlc_vector_clear(&sys->prerender.vector);
    video_format_Clean(&sys->prerender.fmtdst);
    video_format_Clean(&sys->prerender.fmtsrc);
}