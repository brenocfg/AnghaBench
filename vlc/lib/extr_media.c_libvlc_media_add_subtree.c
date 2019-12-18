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
struct TYPE_10__ {int /*<<< orphan*/  event_manager; } ;
typedef  TYPE_3__ libvlc_media_t ;
struct TYPE_8__ {TYPE_3__* item; } ;
struct TYPE_9__ {TYPE_1__ media_subitemtree_added; } ;
struct TYPE_11__ {TYPE_2__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_4__ libvlc_event_t ;
typedef  int /*<<< orphan*/  input_item_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  input_item_add_subnode (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_MediaSubItemTreeAdded ; 
 int /*<<< orphan*/  libvlc_event_send (int /*<<< orphan*/ *,TYPE_4__*) ; 

void libvlc_media_add_subtree(libvlc_media_t *p_md, input_item_node_t *node)
{
    /* FIXME FIXME FIXME
     * Recursive function calls seem much simpler for this. But playlists are
     * untrusted and can be arbitrarily deep (e.g. with XSPF). So recursion can
     * potentially lead to plain old stack overflow. */
    input_item_add_subnode( p_md, node );

    /* Construct the event */
    libvlc_event_t event;
    event.type = libvlc_MediaSubItemTreeAdded;
    event.u.media_subitemtree_added.item = p_md;

    /* Send the event */
    libvlc_event_send( &p_md->event_manager, &event );
}