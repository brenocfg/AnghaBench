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
struct TYPE_3__ {int minAdaptLevel; } ;
typedef  TYPE_1__ FIO_prefs_t ;

/* Variables and functions */
 int ZSTD_minCLevel () ; 
 int /*<<< orphan*/  assert (int) ; 

void FIO_setAdaptMin(FIO_prefs_t* const prefs, int minCLevel)
{
#ifndef ZSTD_NOCOMPRESS
    assert(minCLevel >= ZSTD_minCLevel());
#endif
    prefs->minAdaptLevel = minCLevel;
}