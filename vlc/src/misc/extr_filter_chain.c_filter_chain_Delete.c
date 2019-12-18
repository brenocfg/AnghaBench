#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  fmt_out; int /*<<< orphan*/  fmt_in; } ;
typedef  TYPE_1__ filter_chain_t ;

/* Variables and functions */
 int /*<<< orphan*/  es_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  filter_chain_Clear (TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void filter_chain_Delete( filter_chain_t *p_chain )
{
    filter_chain_Clear( p_chain );

    es_format_Clean( &p_chain->fmt_in );
    es_format_Clean( &p_chain->fmt_out );

    free( p_chain );
}