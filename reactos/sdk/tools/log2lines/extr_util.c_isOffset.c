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
 int /*<<< orphan*/  getFmt (char const*) ; 
 int sscanf (char const*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ strchr (char const*,char) ; 

int
isOffset(const char *a)
{
    int i = 0;
    if (strchr(a, '.'))
        return 0;
    return sscanf(a, getFmt(a), &i);
}