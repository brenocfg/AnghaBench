#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int i_score; } ;
typedef  TYPE_1__ module_t ;

/* Variables and functions */

__attribute__((used)) static int vlc_module_cmp (const void *a, const void *b)
{
    const module_t *const *ma = a, *const *mb = b;
    /* Note that qsort() uses _ascending_ order,
     * so the smallest module is the one with the biggest score. */
    return (*mb)->i_score - (*ma)->i_score;
}