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
 int strcmp (char const*,char const*) ; 

int clusterManagerSlotCompare(const void *slot1, const void *slot2) {
    const char **i1 = (const char **)slot1;
    const char **i2 = (const char **)slot2;
    return strcmp(*i1, *i2);
}