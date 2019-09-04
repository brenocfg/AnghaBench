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

__attribute__((used)) static char *
remove_mark(char *Line)
{
    if (Line[1] == ' ' && Line[2] == '<')
        if (Line[0] == '*' || Line[0] == '?')
            return Line + 2;
    return Line;
}