#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  input_item_t ;
struct TYPE_4__ {int /*<<< orphan*/ * pp_children; scalar_t__ i_children; int /*<<< orphan*/ * p_item; } ;
typedef  TYPE_1__ input_item_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_item_Hold (int /*<<< orphan*/ *) ; 
 TYPE_1__* malloc (int) ; 

input_item_node_t *input_item_node_Create( input_item_t *p_input )
{
    input_item_node_t* p_node = malloc( sizeof( input_item_node_t ) );
    if( !p_node )
        return NULL;

    assert( p_input );

    p_node->p_item = p_input;
    input_item_Hold( p_input );

    p_node->i_children = 0;
    p_node->pp_children = NULL;

    return p_node;
}