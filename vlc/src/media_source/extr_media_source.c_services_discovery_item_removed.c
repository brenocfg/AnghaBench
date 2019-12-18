#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_media_tree_t ;
struct TYPE_11__ {int /*<<< orphan*/ * tree; } ;
typedef  TYPE_2__ vlc_media_source_t ;
struct TYPE_10__ {TYPE_2__* sys; } ;
struct TYPE_12__ {TYPE_1__ owner; } ;
typedef  TYPE_3__ services_discovery_t ;
struct TYPE_13__ {char* psz_name; } ;
typedef  TYPE_4__ input_item_t ;

/* Variables and functions */
 int /*<<< orphan*/  msg_Dbg (TYPE_3__*,char*,char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_3__*,char*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_media_tree_Lock (int /*<<< orphan*/ *) ; 
 int vlc_media_tree_Remove (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  vlc_media_tree_Unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
services_discovery_item_removed(services_discovery_t *sd, input_item_t *media)
{
    vlc_media_source_t *ms = sd->owner.sys;
    vlc_media_tree_t *tree = ms->tree;

    msg_Dbg(sd, "removing: %s", media->psz_name ? media->psz_name : "(null)");

    vlc_media_tree_Lock(tree);
    bool removed = vlc_media_tree_Remove(tree, media);
    vlc_media_tree_Unlock(tree);

    if (unlikely(!removed))
    {
        msg_Err(sd, "removing item not added"); /* SD plugin bug */
        return;
    }
}