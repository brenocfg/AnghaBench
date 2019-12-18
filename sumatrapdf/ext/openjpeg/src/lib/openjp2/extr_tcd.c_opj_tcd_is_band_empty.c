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
struct TYPE_3__ {scalar_t__ x1; scalar_t__ x0; scalar_t__ y1; scalar_t__ y0; } ;
typedef  TYPE_1__ opj_tcd_band_t ;
typedef  int OPJ_BOOL ;

/* Variables and functions */

OPJ_BOOL opj_tcd_is_band_empty(opj_tcd_band_t* band)
{
    return (band->x1 - band->x0 == 0) || (band->y1 - band->y0 == 0);
}