#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_17__ {char* psz_coverart_url; scalar_t__ psz_group_id; } ;
typedef  TYPE_3__ musicbrainz_release_t ;
struct TYPE_18__ {size_t i_release; TYPE_3__* p_releases; } ;
typedef  TYPE_4__ musicbrainz_recording_t ;
struct TYPE_19__ {int /*<<< orphan*/  root; } ;
typedef  TYPE_5__ musicbrainz_lookup_t ;
struct TYPE_15__ {int length; TYPE_6__** values; } ;
struct TYPE_16__ {TYPE_1__ array; } ;
struct TYPE_20__ {scalar_t__ type; TYPE_2__ u; } ;
typedef  TYPE_6__ json_value ;

/* Variables and functions */
 int /*<<< orphan*/  COVERARTARCHIVE_DEFAULT_SERVER ; 
 void* calloc (int,int) ; 
 char* coverartarchive_make_releasegroup_arturl (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 scalar_t__ json_array ; 
 TYPE_6__* json_getbyname (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ json_object ; 
 int /*<<< orphan*/  musicbrainz_fill_release (TYPE_6__*,TYPE_3__*) ; 
 scalar_t__ musicbrainz_has_cover_in_releasegroup (TYPE_6__**,unsigned int,scalar_t__) ; 
 TYPE_5__* musicbrainz_lookup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  musicbrainz_lookup_release (TYPE_5__*) ; 

__attribute__((used)) static musicbrainz_recording_t *musicbrainz_lookup_recording_by_apiurl(vlc_object_t *obj,
                                                                       const char *psz_url)
{
    musicbrainz_recording_t *r = calloc(1, sizeof(*r));
    if(!r)
        return NULL;

    musicbrainz_lookup_t *lookup = musicbrainz_lookup(obj, psz_url);
    if(!lookup)
    {
        free(r);
        return NULL;
    }

    const json_value *releases = json_getbyname(lookup->root, "releases");
    if (releases && releases->type == json_array &&
        releases->u.array.length)
    {
        r->p_releases = calloc(releases->u.array.length, sizeof(*r->p_releases));
        if(r->p_releases)
        {
            for(unsigned i=0; i<releases->u.array.length; i++)
            {
                json_value *node = releases->u.array.values[i];
                musicbrainz_release_t *p_mbrel = &r->p_releases[r->i_release];
                if (!node || node->type != json_object ||
                    !musicbrainz_fill_release(node, p_mbrel))
                    continue;

                /* Try to find cover from other releases from the same group */
                if(p_mbrel->psz_group_id && !p_mbrel->psz_coverart_url &&
                   musicbrainz_has_cover_in_releasegroup(releases->u.array.values,
                                                         releases->u.array.length,
                                                         p_mbrel->psz_group_id))
                {
                    char *psz_art = coverartarchive_make_releasegroup_arturl(
                                        COVERARTARCHIVE_DEFAULT_SERVER,
                                        p_mbrel->psz_group_id );
                    if(psz_art)
                        p_mbrel->psz_coverart_url = psz_art;
                }

                r->i_release++;
            }
        }
    }

    musicbrainz_lookup_release(lookup);

    return r;
}