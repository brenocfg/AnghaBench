#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {size_t i_tracks; void* psz_date; void* psz_artist; void* psz_group_id; void* psz_id; void* psz_title; int /*<<< orphan*/ * p_tracks; } ;
typedef  TYPE_3__ musicbrainz_release_t ;
struct TYPE_12__ {scalar_t__ length; TYPE_4__ const** values; } ;
struct TYPE_13__ {TYPE_1__ array; } ;
struct TYPE_15__ {scalar_t__ type; TYPE_2__ u; } ;
typedef  TYPE_4__ const json_value ;

/* Variables and functions */
 int /*<<< orphan*/ * calloc (scalar_t__,int) ; 
 scalar_t__ json_array ; 
 void* json_dupstring (TYPE_4__ const*,char*) ; 
 TYPE_4__ const* json_getbyname (TYPE_4__ const*,char*) ; 
 void* musicbrainz_fill_artists (TYPE_4__ const*) ; 
 scalar_t__ musicbrainz_fill_track (TYPE_4__ const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool musicbrainz_fill_release(const json_value *releasenode, musicbrainz_release_t *r)
{
    const json_value *media = json_getbyname(releasenode, "media");
    if(!media || media->type != json_array ||
       media->u.array.length == 0)
        return false;
    /* we always use first media */
    media = media->u.array.values[0];

    const json_value *tracks = json_getbyname(media, "tracks");
    if(!tracks || tracks->type != json_array ||
       tracks->u.array.length == 0)
        return false;

    r->p_tracks = calloc(tracks->u.array.length, sizeof(*r->p_tracks));
    if(!r->p_tracks)
        return false;

    for(size_t i=0; i<tracks->u.array.length; i++)
    {
        if(musicbrainz_fill_track(tracks->u.array.values[i], &r->p_tracks[r->i_tracks]))
            r->i_tracks++;
    }

    r->psz_title = json_dupstring(releasenode, "title");
    r->psz_id = json_dupstring(releasenode, "id");

    const json_value *rgnode = json_getbyname(releasenode, "release-group");
    if(rgnode)
    {
        r->psz_date = json_dupstring(rgnode, "first-release-date");
        r->psz_group_id = json_dupstring(rgnode, "id");

        const json_value *node = json_getbyname(rgnode, "artist-credit");
        if(node)
            r->psz_artist = musicbrainz_fill_artists(node);
    }
    else
    {
        const json_value *node = json_getbyname(releasenode, "artist-credit");
        if(node)
            r->psz_artist = musicbrainz_fill_artists(node);

        node = json_getbyname(releasenode, "release-events");
        if(node && node->type == json_array && node->u.array.length)
            r->psz_date = json_dupstring(node->u.array.values[0], "date");
    }


    return true;
}