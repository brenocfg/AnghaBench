#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_fourcc_t ;
typedef  int /*<<< orphan*/  video_format_t ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  cond; int /*<<< orphan*/ * chroma_list; int /*<<< orphan*/  fmtsrc; int /*<<< orphan*/  fmtdst; } ;
struct TYPE_5__ {TYPE_1__ prerender; } ;
typedef  TYPE_2__ spu_private_t ;

/* Variables and functions */
 size_t SPU_CHROMALIST_COUNT ; 
 int /*<<< orphan*/  video_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_format_Copy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  video_format_IsSimilar (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spu_PrerenderWake(spu_private_t *sys,
                              const video_format_t *fmt_dst,
                              const video_format_t *fmt_src,
                              const vlc_fourcc_t *chroma_list)
{
    vlc_mutex_lock(&sys->prerender.lock);
    if(!video_format_IsSimilar(fmt_dst, &sys->prerender.fmtdst))
    {
        video_format_Clean(&sys->prerender.fmtdst);
        video_format_Copy(&sys->prerender.fmtdst, fmt_dst);
    }
    if(!video_format_IsSimilar(fmt_src, &sys->prerender.fmtsrc))
    {
        video_format_Clean(&sys->prerender.fmtsrc);
        video_format_Copy(&sys->prerender.fmtsrc, fmt_src);
    }

    for(size_t i=0; i<SPU_CHROMALIST_COUNT; i++)
    {
        sys->prerender.chroma_list[i] = chroma_list[i];
        if(!chroma_list[i])
            break;
    }

    vlc_cond_signal(&sys->prerender.cond);
    vlc_mutex_unlock(&sys->prerender.lock);
}