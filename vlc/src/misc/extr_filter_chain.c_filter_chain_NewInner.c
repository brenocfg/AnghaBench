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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {int b_allow_fmt_out_change; char const* filter_cap; char const* conv_cap; int /*<<< orphan*/  fmt_out; int /*<<< orphan*/  fmt_in; int /*<<< orphan*/ * last; int /*<<< orphan*/ * first; int /*<<< orphan*/ * obj; } ;
typedef  TYPE_1__ filter_chain_t ;
typedef  enum es_format_category_e { ____Placeholder_es_format_category_e } es_format_category_e ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  es_format_Init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* malloc (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static filter_chain_t *filter_chain_NewInner( vlc_object_t *obj,
    const char *cap, const char *conv_cap, bool fmt_out_change,
    enum es_format_category_e cat )
{
    assert( obj != NULL );
    assert( cap != NULL );

    filter_chain_t *chain = malloc( sizeof (*chain) );
    if( unlikely(chain == NULL) )
        return NULL;

    chain->obj = obj;
    chain->first = NULL;
    chain->last = NULL;
    es_format_Init( &chain->fmt_in, cat, 0 );
    es_format_Init( &chain->fmt_out, cat, 0 );
    chain->b_allow_fmt_out_change = fmt_out_change;
    chain->filter_cap = cap;
    chain->conv_cap = conv_cap;
    return chain;
}