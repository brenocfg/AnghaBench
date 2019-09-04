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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  metric_units ; 
 int scan_units (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int scan_metric(char *s, uint64_t *n) {
    return scan_units(s, n, &metric_units);
}