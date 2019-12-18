#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {int /*<<< orphan*/  root; } ;
typedef  TYPE_1__ musicbrainz_lookup_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  json_parse_document (int /*<<< orphan*/ *,void*) ; 
 void* json_retrieve_document (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_1__* musicbrainz_lookup_new () ; 

__attribute__((used)) static musicbrainz_lookup_t * musicbrainz_lookup(vlc_object_t *p_obj, const char *psz_url)
{
    msg_Dbg(p_obj, "Querying MB for %s", psz_url);
    void *p_buffer = json_retrieve_document(p_obj, psz_url);
    if(!p_buffer)
        return NULL;

    musicbrainz_lookup_t *p_lookup = musicbrainz_lookup_new();
    if(p_lookup)
    {
        p_lookup->root = json_parse_document(p_obj, p_buffer);
        if (!p_lookup->root)
            msg_Dbg(p_obj, "No results");
    }
    free(p_buffer);
    return p_lookup;
}