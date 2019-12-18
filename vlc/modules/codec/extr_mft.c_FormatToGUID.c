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
typedef  scalar_t__ vlc_fourcc_t ;
struct TYPE_3__ {scalar_t__ fourcc; int /*<<< orphan*/  const* guid; } ;
typedef  TYPE_1__ pair_format_guid ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */

__attribute__((used)) static const GUID *FormatToGUID(const pair_format_guid table[], vlc_fourcc_t fourcc)
{
    for (int i = 0; table[i].fourcc; ++i)
        if (table[i].fourcc == fourcc)
            return table[i].guid;

    return NULL;
}