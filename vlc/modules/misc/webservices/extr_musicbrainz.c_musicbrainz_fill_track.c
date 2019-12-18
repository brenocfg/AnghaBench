#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  i_index; void* psz_artist; void* psz_title; } ;
typedef  TYPE_3__ musicbrainz_track_t ;
struct TYPE_10__ {TYPE_4__ const** values; scalar_t__ length; } ;
struct TYPE_11__ {int /*<<< orphan*/  integer; TYPE_1__ array; } ;
struct TYPE_13__ {scalar_t__ type; TYPE_2__ u; } ;
typedef  TYPE_4__ json_value ;

/* Variables and functions */
 scalar_t__ json_array ; 
 void* json_dupstring (TYPE_4__ const*,char*) ; 
 TYPE_4__* json_getbyname (TYPE_4__ const*,char*) ; 
 scalar_t__ json_integer ; 

__attribute__((used)) static bool musicbrainz_fill_track(const json_value *tracknode, musicbrainz_track_t *t)
{
    t->psz_title = json_dupstring(tracknode, "title");

    const json_value *node = json_getbyname(tracknode, "artist-credit");
    if (node && node->type == json_array && node->u.array.length)
        t->psz_artist = json_dupstring(node->u.array.values[0], "name");

    node = json_getbyname(tracknode, "position");
    if (node && node->type == json_integer)
        t->i_index = node->u.integer;

    return true;
}