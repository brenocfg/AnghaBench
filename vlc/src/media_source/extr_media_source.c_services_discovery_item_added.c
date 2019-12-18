#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  root; } ;
typedef  TYPE_2__ vlc_media_tree_t ;
struct TYPE_19__ {TYPE_2__* tree; } ;
typedef  TYPE_3__ vlc_media_source_t ;
struct TYPE_17__ {TYPE_3__* sys; } ;
struct TYPE_20__ {TYPE_1__ owner; } ;
typedef  TYPE_4__ services_discovery_t ;
struct TYPE_21__ {char* psz_name; } ;
typedef  TYPE_5__ input_item_t ;
typedef  int /*<<< orphan*/  input_item_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (char const*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_4__*,char*,char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_4__*,char*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/ * vlc_media_tree_Add (TYPE_2__*,int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  vlc_media_tree_Find (TYPE_2__*,TYPE_5__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_media_tree_Lock (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_media_tree_Unlock (TYPE_2__*) ; 

__attribute__((used)) static void
services_discovery_item_added(services_discovery_t *sd,
                              input_item_t *parent, input_item_t *media,
                              const char *cat)
{
    assert(!parent || !cat);
    VLC_UNUSED(cat);

    vlc_media_source_t *ms = sd->owner.sys;
    vlc_media_tree_t *tree = ms->tree;

    msg_Dbg(sd, "adding: %s", media->psz_name ? media->psz_name : "(null)");

    vlc_media_tree_Lock(tree);

    input_item_node_t *parent_node;
    if (parent)
        vlc_media_tree_Find(tree, parent, &parent_node, NULL);
    else
        parent_node = &tree->root;

    bool added = vlc_media_tree_Add(tree, parent_node, media) != NULL;
    if (unlikely(!added))
        msg_Err(sd, "could not allocate media tree node");

    vlc_media_tree_Unlock(tree);
}