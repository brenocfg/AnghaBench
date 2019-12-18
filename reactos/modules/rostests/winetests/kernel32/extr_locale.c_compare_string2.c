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
 int CompareStringA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,char const*,int) ; 

__attribute__((used)) static int compare_string2(const void *e1, const void *e2)
{
    const char *s1 = *(const char *const *)e1;
    const char *s2 = *(const char *const *)e2;

    return CompareStringA(0, 0, s1, -1, s2, -1) - 2;
}