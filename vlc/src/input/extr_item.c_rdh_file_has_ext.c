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
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncasecmp (char const*,char const*,size_t) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static bool rdh_file_has_ext(const char *psz_filename,
                             const char *psz_ignored_exts)
{
    if (psz_ignored_exts == NULL)
        return false;

    const char *ext = strrchr(psz_filename, '.');
    if (ext == NULL)
        return false;

    size_t extlen = strlen(++ext);

    for (const char *type = psz_ignored_exts, *end; type[0]; type = end + 1)
    {
        end = strchr(type, ',');
        if (end == NULL)
            end = type + strlen(type);

        if (type + extlen == end && !strncasecmp(ext, type, extlen))
            return true;

        if (*end == '\0')
            break;
    }

    return false;
}