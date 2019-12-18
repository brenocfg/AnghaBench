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

__attribute__((used)) static bool isurihex(int c)
{   /* Same as isxdigit() but does not depend on locale and unsignedness */
    return ((unsigned char)(c - '0') < 10)
        || ((unsigned char)(c - 'A') < 6)
        || ((unsigned char)(c - 'a') < 6);
}