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
 int /*<<< orphan*/  sprintf (char*,char*,char const) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void format_test_result(char *target, const char *src)
{
    int i;
    for (i = 0; i < strlen(src); i++)
        sprintf(target + 2*i, "%02x", src[i] & 0xFF);
    target[2*i] = 0;
}