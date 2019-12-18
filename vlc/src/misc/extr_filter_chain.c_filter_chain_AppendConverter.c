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
struct TYPE_4__ {int /*<<< orphan*/  conv_cap; } ;
typedef  TYPE_1__ filter_chain_t ;
typedef  int /*<<< orphan*/  es_format_t ;

/* Variables and functions */
 int /*<<< orphan*/ * filter_chain_AppendInner (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

int filter_chain_AppendConverter( filter_chain_t *chain,
    const es_format_t *fmt_out )
{
    return filter_chain_AppendInner( chain, NULL, chain->conv_cap, NULL,
                                     fmt_out ) != NULL ? 0 : -1;
}