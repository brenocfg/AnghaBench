#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int end_count; int start_count; int id_delta; int id_range_offset; } ;
typedef  TYPE_1__ cmap_format_4_seg ;
struct TYPE_6__ {int /*<<< orphan*/ * end_count; int /*<<< orphan*/  seg_countx2; } ;
typedef  TYPE_2__ cmap_format_4 ;
typedef  size_t USHORT ;

/* Variables and functions */
 int GET_BE_WORD (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_seg4(cmap_format_4 *cmap, USHORT seg_num, cmap_format_4_seg *seg)
{
    USHORT segs = GET_BE_WORD(cmap->seg_countx2) / 2;
    seg->end_count = GET_BE_WORD(cmap->end_count[seg_num]);
    seg->start_count = GET_BE_WORD(cmap->end_count[segs + 1 + seg_num]);
    seg->id_delta = GET_BE_WORD(cmap->end_count[2 * segs + 1 + seg_num]);
    seg->id_range_offset = GET_BE_WORD(cmap->end_count[3 * segs + 1 + seg_num]);
}