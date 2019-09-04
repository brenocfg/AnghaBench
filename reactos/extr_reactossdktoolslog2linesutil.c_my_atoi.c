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
 int /*<<< orphan*/  sscanf (char const*,int /*<<< orphan*/ ,int*) ; 

long
my_atoi(const char *a)
{
    int i = 0;
    sscanf(a, getFmt(a), &i);
    return i;
}