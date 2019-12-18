#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  OPJ_UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  opj_uint_adds (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opj_uint_min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opj_uint_subs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void opj_dwt_segment_grow(OPJ_UINT32 filter_width,
                                 OPJ_UINT32 max_size,
                                 OPJ_UINT32* start,
                                 OPJ_UINT32* end)
{
    *start = opj_uint_subs(*start, filter_width);
    *end = opj_uint_adds(*end, filter_width);
    *end = opj_uint_min(*end, max_size);
}