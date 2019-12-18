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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_10__ {int /*<<< orphan*/ * cbs; } ;
typedef  TYPE_3__ es_out_t ;
struct TYPE_9__ {int /*<<< orphan*/ * channels; int /*<<< orphan*/ * p_video_es; } ;
struct TYPE_8__ {int i_audio_pid; int i_spu_pid; } ;
struct TYPE_11__ {int b_discontinuity; int b_disable_output; int b_entered_recycling; int b_restart_decoders_on_reuse; int b_lowdelay; TYPE_3__ es_out; int /*<<< orphan*/  lock; TYPE_2__ overlay; TYPE_1__ selected; void* priv; int /*<<< orphan*/ * p_obj; TYPE_3__* p_dst_out; int /*<<< orphan*/  es; } ;
typedef  TYPE_4__ bluray_esout_priv_t ;

/* Variables and functions */
 size_t MAX_OVERLAY ; 
 int /*<<< orphan*/  VOUT_SPU_CHANNEL_INVALID ; 
 int /*<<< orphan*/  bluray_esOutCallbacks ; 
 TYPE_4__* malloc (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static es_out_t *esOutNew(vlc_object_t *p_obj, es_out_t *p_dst_out, void *priv)
{
    bluray_esout_priv_t *esout_priv = malloc(sizeof(*esout_priv));
    if (unlikely(esout_priv == NULL))
        return NULL;

    vlc_array_init(&esout_priv->es);
    esout_priv->p_dst_out = p_dst_out;
    esout_priv->p_obj = p_obj;
    esout_priv->priv = priv;
    esout_priv->es_out.cbs = &bluray_esOutCallbacks;
    esout_priv->b_discontinuity = false;
    esout_priv->b_disable_output = false;
    esout_priv->b_entered_recycling = false;
    esout_priv->b_restart_decoders_on_reuse = true;
    esout_priv->b_lowdelay = false;
    esout_priv->selected.i_audio_pid = -1;
    esout_priv->selected.i_spu_pid = -1;
    esout_priv->overlay.p_video_es = NULL;
    for(size_t i=0; i<MAX_OVERLAY; i++)
        esout_priv->overlay.channels[i] = VOUT_SPU_CHANNEL_INVALID;
    vlc_mutex_init(&esout_priv->lock);
    return &esout_priv->es_out;
}