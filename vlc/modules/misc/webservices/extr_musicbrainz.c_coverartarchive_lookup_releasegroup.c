#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  musicbrainz_lookup_t ;
struct TYPE_3__ {int /*<<< orphan*/  obj; int /*<<< orphan*/  psz_coverart_server; } ;
typedef  TYPE_1__ musicbrainz_config_t ;
typedef  char coverartarchive_t ;

/* Variables and functions */
 scalar_t__ asprintf (char**,char*,int /*<<< orphan*/ ,char const*) ; 
 char* calloc (int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * musicbrainz_lookup (int /*<<< orphan*/ ,char*) ; 

coverartarchive_t * coverartarchive_lookup_releasegroup(musicbrainz_config_t *cfg, const char *psz_id)
{
    coverartarchive_t *c = calloc(1, sizeof(*c));
    if(!c)
        return NULL;

    char *psz_url;
    if(0 < asprintf(&psz_url, "https://%s/releasegroup/%s", cfg->psz_coverart_server, psz_id ))
    {
        return NULL;
    }

     musicbrainz_lookup_t *p_lookup = musicbrainz_lookup(cfg->obj, psz_url);
     free(psz_url);

     if(!p_lookup)
     {
         free(c);
         return NULL;
     }

    return c;
}