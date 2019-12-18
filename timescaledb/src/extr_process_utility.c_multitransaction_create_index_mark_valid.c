#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ max_chunks; } ;
struct TYPE_5__ {TYPE_1__ extended_options; } ;
typedef  TYPE_2__ CreateIndexInfo ;

/* Variables and functions */

__attribute__((used)) static bool
multitransaction_create_index_mark_valid(CreateIndexInfo info)
{
#ifdef DEBUG
	return info.extended_options.max_chunks < 0;
#else
	return true;
#endif
}