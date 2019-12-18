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
 char const* MUSICBRAINZ_DEFAULT_SERVER ; 
 int asprintf (char**,char*,char const*,char const*,char*,char const*) ; 

__attribute__((used)) static char *musicbrainz_build_discid_json_url(const char *psz_server,
                                               const char *psz_disc_id,
                                               const char *psz_tail)
{
    char *psz_url;
    if(asprintf(&psz_url,
                "https://%s/ws/2/discid/%s?"
                "fmt=json"
                "&inc=artist-credits+recordings+release-groups"
                "&cdstubs=no"
                "%s%s",
                psz_server ? psz_server : MUSICBRAINZ_DEFAULT_SERVER,
                psz_disc_id,
                psz_tail ? "&" : "",
                psz_tail ? psz_tail : "" ) > -1 )
    {
        return psz_url;
    }
    return NULL;
}