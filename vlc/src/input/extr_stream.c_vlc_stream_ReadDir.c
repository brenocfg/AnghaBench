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
struct TYPE_4__ {int (* pf_readdir ) (TYPE_1__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ stream_t ;
typedef  int /*<<< orphan*/  input_item_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ *) ; 

int vlc_stream_ReadDir( stream_t *s, input_item_node_t *p_node )
{
    assert(s->pf_readdir != NULL);
    return s->pf_readdir( s, p_node );
}