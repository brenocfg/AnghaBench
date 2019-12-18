#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  lock; TYPE_2__* interfaces; } ;
typedef  TYPE_1__ libvlc_priv_t ;
typedef  int /*<<< orphan*/  libvlc_int_t ;
struct TYPE_8__ {int /*<<< orphan*/  p_cfg; int /*<<< orphan*/  p_module; struct TYPE_8__* p_next; } ;
typedef  TYPE_2__ intf_thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  AddIntfCallback ; 
 int /*<<< orphan*/  config_ChainDestroy (int /*<<< orphan*/ ) ; 
 TYPE_1__* libvlc_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_unneed (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_DelCallback (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_2__*) ; 

void intf_DestroyAll(libvlc_int_t *libvlc)
{
    libvlc_priv_t *priv = libvlc_priv(libvlc);

    vlc_mutex_lock(&priv->lock);
    intf_thread_t *intf, **pp = &priv->interfaces;

    while ((intf = *pp) != NULL)
    {
        *pp = intf->p_next;
        vlc_mutex_unlock(&priv->lock);

        module_unneed(intf, intf->p_module);
        config_ChainDestroy(intf->p_cfg);
        var_DelCallback(intf, "intf-add", AddIntfCallback, NULL);
        vlc_object_delete(intf);

        vlc_mutex_lock(&priv->lock);
    }
    vlc_mutex_unlock(&priv->lock);
}