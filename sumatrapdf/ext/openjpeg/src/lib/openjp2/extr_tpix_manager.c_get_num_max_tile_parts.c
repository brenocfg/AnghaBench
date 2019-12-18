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
struct TYPE_5__ {int tw; int th; TYPE_1__* tile; } ;
typedef  TYPE_2__ opj_codestream_info_t ;
struct TYPE_4__ {int /*<<< orphan*/  num_tps; } ;

/* Variables and functions */
 int MAX (int /*<<< orphan*/ ,int) ; 

int get_num_max_tile_parts(opj_codestream_info_t cstr_info)
{
    int num_max_tp = 0, i;

    for (i = 0; i < cstr_info.tw * cstr_info.th; i++) {
        num_max_tp = MAX(cstr_info.tile[i].num_tps, num_max_tp);
    }

    return num_max_tp;
}