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
struct TYPE_4__ {int /*<<< orphan*/  fmt_out; int /*<<< orphan*/  fmt_in; } ;
typedef  TYPE_1__ filter_chain_t ;
typedef  int /*<<< orphan*/  es_format_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  es_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  es_format_Copy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  filter_chain_Clear (TYPE_1__*) ; 

void filter_chain_Reset( filter_chain_t *p_chain, const es_format_t *p_fmt_in,
                         const es_format_t *p_fmt_out )
{
    filter_chain_Clear( p_chain );

    assert(p_fmt_in != NULL);
    es_format_Clean( &p_chain->fmt_in );
    es_format_Copy( &p_chain->fmt_in, p_fmt_in );

    assert(p_fmt_out != NULL);
    es_format_Clean( &p_chain->fmt_out );
    es_format_Copy( &p_chain->fmt_out, p_fmt_out );
}