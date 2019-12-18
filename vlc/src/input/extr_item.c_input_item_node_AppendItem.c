#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int i_preparse_depth; int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ input_item_t ;
struct TYPE_13__ {TYPE_1__* p_item; } ;
typedef  TYPE_3__ input_item_node_t ;
struct TYPE_11__ {int i_preparse_depth; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_item_node_AppendNode (TYPE_3__*,TYPE_3__*) ; 
 TYPE_3__* input_item_node_Create (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

input_item_node_t *input_item_node_AppendItem( input_item_node_t *p_node, input_item_t *p_item )
{
    int i_preparse_depth;
    input_item_node_t *p_new_child = input_item_node_Create( p_item );
    if( !p_new_child ) return NULL;

    vlc_mutex_lock( &p_node->p_item->lock );
    i_preparse_depth = p_node->p_item->i_preparse_depth;
    vlc_mutex_unlock( &p_node->p_item->lock );

    vlc_mutex_lock( &p_item->lock );
    p_item->i_preparse_depth = i_preparse_depth > 0 ?
                               i_preparse_depth -1 :
                               i_preparse_depth;
    vlc_mutex_unlock( &p_item->lock );

    input_item_node_AppendNode( p_node, p_new_child );
    return p_new_child;
}