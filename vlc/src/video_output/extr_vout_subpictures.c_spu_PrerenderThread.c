#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct spu_prerender_ctx_s {scalar_t__* chroma_list; int /*<<< orphan*/  fmtdst; int /*<<< orphan*/  fmtsrc; TYPE_6__** pp_processed; int /*<<< orphan*/ * cleanuplock; } ;
struct TYPE_8__ {TYPE_3__* p; } ;
typedef  TYPE_2__ spu_t ;
struct TYPE_10__ {size_t size; TYPE_6__** data; } ;
struct TYPE_7__ {int /*<<< orphan*/  output_cond; TYPE_6__* p_processed; int /*<<< orphan*/  lock; int /*<<< orphan*/  fmtsrc; int /*<<< orphan*/  fmtdst; int /*<<< orphan*/ * chroma_list; TYPE_4__ vector; int /*<<< orphan*/  cond; } ;
struct TYPE_9__ {TYPE_1__ prerender; } ;
typedef  TYPE_3__ spu_private_t ;
struct TYPE_11__ {scalar_t__ i_start; } ;

/* Variables and functions */
 size_t SPU_CHROMALIST_COUNT ; 
 int /*<<< orphan*/  memcpy (scalar_t__**,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  spu_PrerenderText (TYPE_2__*,TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  spu_prerender_cleanup_routine ; 
 int /*<<< orphan*/  video_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_format_Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_format_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_cleanup_pop () ; 
 int /*<<< orphan*/  vlc_cleanup_push (int /*<<< orphan*/ ,struct spu_prerender_ctx_s*) ; 
 int /*<<< orphan*/  vlc_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 
 int /*<<< orphan*/  vlc_vector_remove (TYPE_4__*,size_t) ; 

__attribute__((used)) static void * spu_PrerenderThread(void *priv)
{
    spu_t *spu = priv;
    spu_private_t *sys = spu->p;

    struct spu_prerender_ctx_s ctx;
    ctx.cleanuplock = &sys->prerender.lock;
    ctx.chroma_list[SPU_CHROMALIST_COUNT] = 0;
    video_format_Init(&ctx.fmtsrc, 0);
    video_format_Init(&ctx.fmtdst, 0);
    ctx.pp_processed = &sys->prerender.p_processed;

    vlc_mutex_lock(&sys->prerender.lock);
    for( ;; )
    {
        vlc_cleanup_push(spu_prerender_cleanup_routine, &ctx);
        while(!sys->prerender.vector.size || !sys->prerender.chroma_list[0])
            vlc_cond_wait(&sys->prerender.cond, &sys->prerender.lock);

        size_t i_idx = 0;
        sys->prerender.p_processed = sys->prerender.vector.data[0];
        for(size_t i=1; i<sys->prerender.vector.size; i++)
        {
             if(sys->prerender.p_processed->i_start > sys->prerender.vector.data[i]->i_start)
             {
                 sys->prerender.p_processed = sys->prerender.vector.data[i];
                 i_idx = i;
             }
        }
        vlc_vector_remove(&sys->prerender.vector, i_idx);
        memcpy(&ctx.chroma_list, sys->prerender.chroma_list, SPU_CHROMALIST_COUNT);
        video_format_Clean(&ctx.fmtdst);
        video_format_Clean(&ctx.fmtsrc);
        video_format_Copy(&ctx.fmtdst, &sys->prerender.fmtdst);
        video_format_Copy(&ctx.fmtsrc, &sys->prerender.fmtsrc);

        vlc_mutex_unlock(&sys->prerender.lock);
        vlc_cleanup_pop();

        int canc = vlc_savecancel();
        spu_PrerenderText(spu, sys->prerender.p_processed,
                          &ctx.fmtsrc, &ctx.fmtdst, ctx.chroma_list);
        vlc_restorecancel(canc);

        vlc_mutex_lock(&sys->prerender.lock);
        sys->prerender.p_processed = NULL;
        vlc_cond_signal(&sys->prerender.output_cond);
    }

    return NULL;
}