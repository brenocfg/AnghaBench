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
struct TYPE_4__ {struct TYPE_4__* p_next; } ;
typedef  TYPE_1__ webvtt_dom_node_t ;

/* Variables and functions */

__attribute__((used)) static void webvtt_domnode_AppendLast( webvtt_dom_node_t **pp_append,
                                       webvtt_dom_node_t *p_node )
{
    while( *pp_append )
        pp_append = &((*pp_append)->p_next);
    *pp_append = p_node;
}