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
struct TYPE_5__ {int* offsets; TYPE_1__* wine_df; } ;
struct TYPE_4__ {int dwNumObjs; } ;
typedef  TYPE_2__ DataFormat ;

/* Variables and functions */

__attribute__((used)) static int offset_to_object(const DataFormat *df, int offset)
{
    int i;

    if (!df->offsets) return -1;

    for (i = 0; i < df->wine_df->dwNumObjs; i++)
        if (df->offsets[i] == offset) return i;

    return -1;
}