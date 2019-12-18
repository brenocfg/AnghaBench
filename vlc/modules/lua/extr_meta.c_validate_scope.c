#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ meta_fetcher_scope_t ;
struct TYPE_3__ {scalar_t__ e_scope; } ;
typedef  TYPE_1__ luabatch_context_t ;

/* Variables and functions */
 scalar_t__ FETCHER_SCOPE_ANY ; 

__attribute__((used)) static bool validate_scope( const luabatch_context_t *p_context, meta_fetcher_scope_t e_scope )
{
    if ( p_context->e_scope == FETCHER_SCOPE_ANY )
        return true;
    else
        return ( p_context->e_scope == e_scope );
}