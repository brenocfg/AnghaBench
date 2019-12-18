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
typedef  int /*<<< orphan*/  vlc_media_tree_t ;
struct TYPE_7__ {int /*<<< orphan*/  node; void* userdata; struct vlc_media_tree_callbacks const* cbs; } ;
typedef  TYPE_1__ vlc_media_tree_listener_id ;
struct vlc_media_tree_callbacks {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  listeners; } ;
typedef  TYPE_2__ media_tree_private_t ;

/* Variables and functions */
 TYPE_1__* malloc (int) ; 
 TYPE_2__* mt_priv (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_media_tree_Lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_media_tree_NotifyCurrentState (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_media_tree_Unlock (int /*<<< orphan*/ *) ; 

vlc_media_tree_listener_id *
vlc_media_tree_AddListener(vlc_media_tree_t *tree,
                           const struct vlc_media_tree_callbacks *cbs,
                           void *userdata, bool notify_current_state)
{
    vlc_media_tree_listener_id *listener = malloc(sizeof(*listener));
    if (unlikely(!listener))
        return NULL;
    listener->cbs = cbs;
    listener->userdata = userdata;

    media_tree_private_t *priv = mt_priv(tree);
    vlc_media_tree_Lock(tree);

    vlc_list_append(&listener->node, &priv->listeners);

    if (notify_current_state)
        vlc_media_tree_NotifyCurrentState(tree, listener);

    vlc_media_tree_Unlock(tree);
    return listener;
}