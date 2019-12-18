#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vout_thread_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
struct spu_channel {int dummy; } ;
struct TYPE_14__ {TYPE_3__* p; } ;
typedef  TYPE_2__ spu_t ;
struct TYPE_13__ {int /*<<< orphan*/  thread; scalar_t__* chroma_list; int /*<<< orphan*/ * p_processed; int /*<<< orphan*/  fmtsrc; int /*<<< orphan*/  fmtdst; int /*<<< orphan*/  vector; int /*<<< orphan*/  output_cond; int /*<<< orphan*/  cond; int /*<<< orphan*/  lock; } ;
struct TYPE_15__ {int last_sort_date; TYPE_1__ prerender; int /*<<< orphan*/ * vout; void* scale_yuvp; void* scale; int /*<<< orphan*/  text; void* filter_chain; void* source_chain; int /*<<< orphan*/  textlock; int /*<<< orphan*/  filter_chain_lock; int /*<<< orphan*/ * filter_chain_update; int /*<<< orphan*/ * source_chain_update; void* secondary_alignment; void* secondary_margin; void* margin; int /*<<< orphan*/  lock; int /*<<< orphan*/  channels; } ;
typedef  TYPE_3__ spu_private_t ;

/* Variables and functions */
 size_t SPU_CHROMALIST_COUNT ; 
 void* SpuRenderCreateAndLoadScale (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SpuRenderCreateAndLoadText (TYPE_2__*) ; 
 int /*<<< orphan*/  VLC_CODEC_RGBA ; 
 int /*<<< orphan*/  VLC_CODEC_YUVA ; 
 int /*<<< orphan*/  VLC_CODEC_YUVP ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_2__*) ; 
 int /*<<< orphan*/  VLC_THREAD_PRIORITY_VIDEO ; 
 int /*<<< orphan*/  VLC_VOUT_ORDER_PRIMARY ; 
 size_t VOUT_SPU_CHANNEL_OSD_COUNT ; 
 void* filter_chain_NewSPU (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  spu_Cleanup (TYPE_2__*) ; 
 int /*<<< orphan*/  spu_PrerenderThread ; 
 int /*<<< orphan*/  spu_channel_Init (struct spu_channel*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* var_InheritInteger (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  video_format_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_cond_init (int /*<<< orphan*/ *) ; 
 TYPE_2__* vlc_custom_create (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_vector_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_vector_push (int /*<<< orphan*/ *,struct spu_channel) ; 
 int /*<<< orphan*/  vlc_vector_reserve (int /*<<< orphan*/ *,size_t) ; 

spu_t *spu_Create(vlc_object_t *object, vout_thread_t *vout)
{
    spu_t *spu = vlc_custom_create(object,
                                   sizeof(spu_t) + sizeof(spu_private_t),
                                   "subpicture");
    if (!spu)
        return NULL;

    /* Initialize spu fields */
    spu_private_t *sys = spu->p = (spu_private_t*)&spu[1];

    vlc_vector_init(&sys->channels);
    if (!vlc_vector_reserve(&sys->channels, VOUT_SPU_CHANNEL_OSD_COUNT))
    {
        vlc_object_delete(spu);
        return NULL;
    }
    for (size_t i = 0; i < VOUT_SPU_CHANNEL_OSD_COUNT; ++i)
    {
        struct spu_channel channel;
        spu_channel_Init(&channel, i, VLC_VOUT_ORDER_PRIMARY, NULL);
        vlc_vector_push(&sys->channels, channel);
    }

    /* Initialize private fields */
    vlc_mutex_init(&sys->lock);

    sys->margin = var_InheritInteger(spu, "sub-margin");
    sys->secondary_margin = var_InheritInteger(spu, "secondary-sub-margin");

    sys->secondary_alignment = var_InheritInteger(spu,
                                                  "secondary-sub-alignment");

    sys->source_chain_update = NULL;
    sys->filter_chain_update = NULL;
    vlc_mutex_init(&sys->filter_chain_lock);
    sys->source_chain = filter_chain_NewSPU(spu, "sub source");
    sys->filter_chain = filter_chain_NewSPU(spu, "sub filter");

    /* Load text and scale module */
    sys->text = SpuRenderCreateAndLoadText(spu);
    vlc_mutex_init(&sys->textlock);

    /* XXX spu->p_scale is used for all conversion/scaling except yuvp to
     * yuva/rgba */
    sys->scale = SpuRenderCreateAndLoadScale(VLC_OBJECT(spu),
                                             VLC_CODEC_YUVA, VLC_CODEC_RGBA, true);

    /* This one is used for YUVP to YUVA/RGBA without scaling
     * FIXME rename it */
    sys->scale_yuvp = SpuRenderCreateAndLoadScale(VLC_OBJECT(spu),
                                                  VLC_CODEC_YUVP, VLC_CODEC_YUVA, false);


    if (!sys->source_chain || !sys->filter_chain || !sys->text || !sys->scale
     || !sys->scale_yuvp)
    {
        sys->vout = NULL;
        spu_Cleanup(spu);
        vlc_object_delete(spu);
        return NULL;
    }
    /* */
    sys->last_sort_date = -1;
    sys->vout = vout;

    vlc_mutex_init(&sys->prerender.lock);
    vlc_cond_init(&sys->prerender.cond);
    vlc_cond_init(&sys->prerender.output_cond);
    vlc_vector_init(&sys->prerender.vector);
    video_format_Init(&sys->prerender.fmtdst, 0);
    video_format_Init(&sys->prerender.fmtsrc, 0);
    sys->prerender.p_processed = NULL;
    sys->prerender.chroma_list[0] = 0;
    sys->prerender.chroma_list[SPU_CHROMALIST_COUNT] = 0;
    if(vlc_clone(&sys->prerender.thread, spu_PrerenderThread, spu, VLC_THREAD_PRIORITY_VIDEO))
    {
        spu_Cleanup(spu);
        vlc_object_delete(spu);
        spu = NULL;
    }

    return spu;
}