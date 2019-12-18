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
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ isurihex (char const) ; 
 scalar_t__ isurisafe (int) ; 
 scalar_t__ isurisubdelim (int) ; 
 int /*<<< orphan*/ * strchr (char const*,int) ; 

__attribute__((used)) static bool vlc_uri_component_validate(const char *str, const char *extras)
{
    assert(str != NULL);

    for (size_t i = 0; str[i] != '\0'; i++)
    {
        int c = str[i];

        if (isurisafe(c) || isurisubdelim(c))
            continue;
        if (strchr(extras, c) != NULL)
            continue;
        if (c == '%' && isurihex(str[i + 1]) && isurihex(str[i + 2]))
        {
            i += 2;
            continue;
        }
        return false;
    }
    return true;
}