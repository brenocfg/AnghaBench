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
 int /*<<< orphan*/  SetEnvironmentVariableA (char*,char*) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 

__attribute__((used)) static void create_environ(const char* layers[], size_t num)
{
    char buf[256] = { 0 };
    size_t n;
    for (n = 0; n < num; ++n)
    {
        if (n)
            strcat(buf, " ");
        strcat(buf, layers[n]);
    }
    SetEnvironmentVariableA("__COMPAT_LAYER", buf);
}