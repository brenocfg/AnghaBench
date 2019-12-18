#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* first; } ;
typedef  TYPE_2__ filter_chain_t ;
struct TYPE_5__ {int /*<<< orphan*/  filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  filter_chain_DeleteFilter (TYPE_2__*,int /*<<< orphan*/ *) ; 

void filter_chain_Clear( filter_chain_t *p_chain )
{
    while( p_chain->first != NULL )
        filter_chain_DeleteFilter( p_chain, &p_chain->first->filter );
}