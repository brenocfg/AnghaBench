#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vout_thread_t ;
struct TYPE_6__ {int /*<<< orphan*/ * vout; int /*<<< orphan*/ * fmt; } ;
typedef  TYPE_1__ vout_device_configuration_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  vlc_decoder_device ;
struct TYPE_7__ {scalar_t__ i_vout; int /*<<< orphan*/  lock; int /*<<< orphan*/ * p_vout_free; int /*<<< orphan*/ ** pp_vout; int /*<<< orphan*/  lock_hold; int /*<<< orphan*/ * p_parent; int /*<<< orphan*/  p_vout_dummy; } ;
typedef  TYPE_2__ input_resource_t ;
typedef  enum vlc_vout_order { ____Placeholder_vlc_vout_order } vlc_vout_order ;

/* Variables and functions */
 int /*<<< orphan*/  TAB_APPEND (scalar_t__,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAB_FIND (scalar_t__,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * VLC_OBJECT (int /*<<< orphan*/ ) ; 
 int VLC_VOUT_ORDER_PRIMARY ; 
 int VLC_VOUT_ORDER_SECONDARY ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vout_Create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vout_GetDevice (TYPE_1__ const*) ; 

vout_thread_t *input_resource_GetVoutDecoderDevice(input_resource_t *p_resource,
                                      const vout_device_configuration_t *cfg,
                                      enum vlc_vout_order *order,
                                      vlc_decoder_device **pp_dec_dev)
{
    vout_device_configuration_t cfg_buf;
    vout_thread_t *vout;

    assert(cfg != NULL);
    assert(cfg->fmt != NULL);
    vlc_mutex_lock( &p_resource->lock );

    if (cfg->vout == NULL) {
        cfg_buf = *cfg;
        cfg_buf.vout = p_resource->p_vout_free;
        p_resource->p_vout_free = NULL;
        cfg = &cfg_buf;

        if (cfg_buf.vout == NULL) {
            /* Use the dummy vout as the parent of the future main vout. This
             * will allow the future vout to inherit all parameters
             * pre-configured on this dummy vout. */
            vlc_object_t *parent = p_resource->i_vout == 0 ?
                VLC_OBJECT(p_resource->p_vout_dummy) : p_resource->p_parent;
            cfg_buf.vout = vout = vout_Create(parent);
            if (vout == NULL)
                goto out;

            vlc_mutex_lock(&p_resource->lock_hold);
            *order = p_resource->i_vout == 0 ? VLC_VOUT_ORDER_PRIMARY
                                             : VLC_VOUT_ORDER_SECONDARY;
            TAB_APPEND(p_resource->i_vout, p_resource->pp_vout, vout);
            vlc_mutex_unlock(&p_resource->lock_hold);
        } else
        {
            /* The free vout is always the first one */
            *order = VLC_VOUT_ORDER_PRIMARY;
            msg_Dbg(p_resource->p_parent, "trying to reuse free vout");
        }
    }
    else
    {
        vlc_mutex_lock(&p_resource->lock_hold);
        assert(p_resource->i_vout > 0);
        *order = p_resource->pp_vout[0] == cfg->vout ? VLC_VOUT_ORDER_PRIMARY
                                                     : VLC_VOUT_ORDER_SECONDARY;
        vlc_mutex_unlock(&p_resource->lock_hold);
    }

#ifndef NDEBUG
    {
        int index;
        TAB_FIND(p_resource->i_vout, p_resource->pp_vout, cfg->vout, index );
        assert(index >= 0);
        assert(p_resource->p_vout_free == NULL || p_resource->p_vout_free == cfg->vout);
    }
#endif

    if (pp_dec_dev)
    {
        *pp_dec_dev = vout_GetDevice(cfg);
    }

    vout = cfg->vout;

out:
    vlc_mutex_unlock( &p_resource->lock );
    return vout;
}