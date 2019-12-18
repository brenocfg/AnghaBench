#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  const fmt_out; TYPE_2__* last; } ;
typedef  TYPE_3__ filter_chain_t ;
typedef  int /*<<< orphan*/  es_format_t ;
struct TYPE_5__ {int /*<<< orphan*/  const fmt_out; } ;
struct TYPE_6__ {TYPE_1__ filter; } ;

/* Variables and functions */

const es_format_t *filter_chain_GetFmtOut( const filter_chain_t *p_chain )
{
    if( p_chain->last != NULL )
        return &p_chain->last->filter.fmt_out;

    /* Unless filter_chain_Reset has been called we are doomed */
    return &p_chain->fmt_out;
}