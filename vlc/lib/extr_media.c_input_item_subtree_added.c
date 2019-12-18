#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  libvlc_media_t ;
typedef  int /*<<< orphan*/  input_item_t ;
typedef  int /*<<< orphan*/  input_item_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_media_add_subtree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void input_item_subtree_added(input_item_t *item,
                                     input_item_node_t *node,
                                     void *user_data)
{
    VLC_UNUSED(item);
    libvlc_media_t * p_md = user_data;
    libvlc_media_add_subtree(p_md, node);
}