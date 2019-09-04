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

/* Variables and functions */
 char* format_units (long double,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  metric_units ; 

char *format_metric(long double n) {
    return format_units(n, &metric_units, 2);
}