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
 char* strdup (char const*) ; 
 int strlen (char*) ; 
 char* strrchr (char*,char) ; 
 char tolower (char) ; 

__attribute__((used)) static char *rdh_name_from_filename(const char *psz_filename)
{
    /* remove leading white spaces */
    while (*psz_filename != '\0' && *psz_filename == ' ')
        psz_filename++;

    char *psz_name = strdup(psz_filename);
    if (!psz_name)
        return NULL;

    /* remove extension */
    char *psz_ptr = strrchr(psz_name, '.');
    if (psz_ptr && psz_ptr != psz_name)
        *psz_ptr = '\0';

    /* remove trailing white spaces */
    int i = strlen(psz_name) - 1;
    while (psz_name[i] == ' ' && i >= 0)
        psz_name[i--] = '\0';

    /* convert to lower case */
    psz_ptr = psz_name;
    while (*psz_ptr != '\0')
    {
        *psz_ptr = tolower(*psz_ptr);
        psz_ptr++;
    }

    return psz_name;
}