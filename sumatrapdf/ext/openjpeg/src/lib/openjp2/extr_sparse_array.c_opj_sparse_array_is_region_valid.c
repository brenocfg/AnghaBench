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
struct TYPE_3__ {scalar_t__ width; scalar_t__ height; } ;
typedef  TYPE_1__ opj_sparse_array_int32_t ;
typedef  scalar_t__ OPJ_UINT32 ;
typedef  int OPJ_BOOL ;

/* Variables and functions */

OPJ_BOOL opj_sparse_array_is_region_valid(const opj_sparse_array_int32_t* sa,
        OPJ_UINT32 x0,
        OPJ_UINT32 y0,
        OPJ_UINT32 x1,
        OPJ_UINT32 y1)
{
    return !(x0 >= sa->width || x1 <= x0 || x1 > sa->width ||
             y0 >= sa->height || y1 <= y0 || y1 > sa->height);
}