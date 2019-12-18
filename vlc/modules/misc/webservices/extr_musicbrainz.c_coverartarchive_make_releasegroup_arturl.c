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
 char const* COVERARTARCHIVE_DEFAULT_SERVER ; 
 int asprintf (char**,char*,char const*,char const*) ; 

char * coverartarchive_make_releasegroup_arturl(const char *psz_server, const char *psz_group_id)
{
    char *psz_art;
    if(-1 < asprintf(&psz_art, "https://%s/release-group/%s/front",
                     psz_server ? psz_server : COVERARTARCHIVE_DEFAULT_SERVER,
                     psz_group_id))
        return psz_art;
    return NULL;
}