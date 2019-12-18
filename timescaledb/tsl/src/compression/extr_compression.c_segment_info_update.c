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
struct TYPE_3__ {int is_null; int /*<<< orphan*/  typlen; int /*<<< orphan*/  typ_by_val; scalar_t__ val; } ;
typedef  TYPE_1__ SegmentInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ datumCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
segment_info_update(SegmentInfo *segment_info, Datum val, bool is_null)
{
	segment_info->is_null = is_null;
	if (is_null)
		segment_info->val = 0;
	else
		segment_info->val = datumCopy(val, segment_info->typ_by_val, segment_info->typlen);
}