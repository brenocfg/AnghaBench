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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ isspace (char const) ; 
 int /*<<< orphan*/  memcmp (char const*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static BOOL gl_extension_supported(const char *extensions, const char *extension_string)
{
    size_t ext_str_len = strlen(extension_string);

    while (*extensions)
    {
        const char *start;
        size_t len;

        while (isspace(*extensions))
            ++extensions;
        start = extensions;
        while (!isspace(*extensions) && *extensions)
            ++extensions;

        len = extensions - start;
        if (!len)
            continue;

        if (len == ext_str_len && !memcmp(start, extension_string, ext_str_len))
        {
            return TRUE;
        }
    }
    return FALSE;
}