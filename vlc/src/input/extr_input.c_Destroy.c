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
typedef  int /*<<< orphan*/  input_thread_t ;
struct TYPE_4__ {size_t i_control; int /*<<< orphan*/  lock_control; int /*<<< orphan*/  wait_control; TYPE_2__* control; int /*<<< orphan*/ * stats; int /*<<< orphan*/  p_item; int /*<<< orphan*/ * p_resource; int /*<<< orphan*/ * p_es_out_display; int /*<<< orphan*/ * p_renderer; } ;
typedef  TYPE_1__ input_thread_private_t ;
struct TYPE_5__ {int /*<<< orphan*/  param; int /*<<< orphan*/  i_type; } ;
typedef  TYPE_2__ input_control_t ;

/* Variables and functions */
 int /*<<< orphan*/  ControlRelease (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VLC_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  es_out_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* input_item_GetName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_item_Release (int /*<<< orphan*/ ) ; 
 TYPE_1__* input_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_resource_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_stats_Destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  vlc_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_object_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_renderer_item_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Destroy(input_thread_t *input)
{
    input_thread_private_t *priv = input_priv(input);

#ifndef NDEBUG
    char *name = input_item_GetName(priv->p_item);
    msg_Dbg(input, "destroying input for '%s'", name);
    free(name);
#endif

    if (priv->p_renderer != NULL)
        vlc_renderer_item_release(priv->p_renderer);
    if (priv->p_es_out_display != NULL)
        es_out_Delete(priv->p_es_out_display);

    if (priv->p_resource != NULL)
        input_resource_Release(priv->p_resource);

    input_item_Release(priv->p_item);

    if (priv->stats != NULL)
        input_stats_Destroy(priv->stats);

    for (size_t i = 0; i < priv->i_control; i++)
    {
        input_control_t *ctrl = &priv->control[i];

        ControlRelease(ctrl->i_type, &ctrl->param);
    }

    vlc_cond_destroy(&priv->wait_control);
    vlc_mutex_destroy(&priv->lock_control);
    vlc_object_delete(VLC_OBJECT(input));
}