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
 int EINVAL ; 

int unbase64char(char c) {
        unsigned offset;

        if (c >= 'A' && c <= 'Z')
                return c - 'A';

        offset = 'Z' - 'A' + 1;

        if (c >= 'a' && c <= 'z')
                return c - 'a' + offset;

        offset += 'z' - 'a' + 1;

        if (c >= '0' && c <= '9')
                return c - '0' + offset;

        offset += '9' - '0' + 1;

        if (c == '+')
                return offset;

        offset++;

        if (c == '/')
                return offset;

        return -EINVAL;
}