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
typedef  int /*<<< orphan*/  musicbrainz_recording_t ;
struct TYPE_3__ {int /*<<< orphan*/  obj; int /*<<< orphan*/  psz_mb_server; } ;
typedef  TYPE_1__ musicbrainz_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* musicbrainz_build_discid_json_url (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/ * musicbrainz_lookup_recording_by_apiurl (int /*<<< orphan*/ ,char*) ; 

musicbrainz_recording_t *musicbrainz_lookup_recording_by_toc(musicbrainz_config_t *cfg,
                                                             const char *psz_toc)
{
    char *psz_url = musicbrainz_build_discid_json_url(cfg->psz_mb_server, "-", psz_toc);
    if(!psz_url)
        return NULL;

    musicbrainz_recording_t *r = musicbrainz_lookup_recording_by_apiurl(cfg->obj, psz_url);
    free(psz_url);
    return r;
}