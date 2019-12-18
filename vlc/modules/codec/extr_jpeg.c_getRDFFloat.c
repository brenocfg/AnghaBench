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
 char* strcasestr (char const*,char const*) ; 
 char* strchr (char*,char) ; 
 size_t strlen (char const*) ; 
 scalar_t__ unlikely (int) ; 
 float us_strtof (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool getRDFFloat(const char *psz_rdf, float *out, const char *psz_var)
{
    char *p_start = strcasestr(psz_rdf, psz_var);
    if (p_start == NULL)
        return false;

    size_t varlen = strlen(psz_var);
    p_start += varlen;
    char *p_end = NULL;
    /* XML style */
    if (p_start[0] == '>')
    {
        p_start += 1;
        p_end = strchr(p_start, '<');
    }
    else if (p_start[0] == '=' && p_start[1] == '"')
    {
        p_start += 2;
        p_end = strchr(p_start, '"');
    }
    if (unlikely(p_end == NULL || p_end == p_start + 1))
        return false;

    *out = us_strtof(p_start, NULL);
    return true;
}