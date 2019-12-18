#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_18__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_17__ {unsigned int length; TYPE_5__** values; } ;
struct TYPE_19__ {TYPE_3__ string; TYPE_2__ array; } ;
struct TYPE_20__ {scalar_t__ type; TYPE_4__ u; } ;
typedef  TYPE_5__ json_value ;
struct TYPE_16__ {unsigned int count; TYPE_7__* p_recordings; } ;
struct TYPE_21__ {TYPE_1__ recordings; } ;
typedef  TYPE_6__ acoustid_result_t ;
struct TYPE_22__ {int /*<<< orphan*/  psz_artist; int /*<<< orphan*/  s_musicbrainz_id; int /*<<< orphan*/  psz_title; } ;
typedef  TYPE_7__ acoustid_mb_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  MB_ID_SIZE ; 
 size_t __MIN (size_t,int /*<<< orphan*/ ) ; 
 TYPE_7__* calloc (unsigned int,int) ; 
 scalar_t__ json_array ; 
 int /*<<< orphan*/  json_dupstring (TYPE_5__ const*,char*) ; 
 TYPE_5__* json_getbyname (TYPE_5__ const*,char*) ; 
 scalar_t__ json_object ; 
 scalar_t__ json_string ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_artists (TYPE_5__*,TYPE_7__*) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void parse_recordings( vlc_object_t *p_obj, const json_value *node, acoustid_result_t *p_result )
{
    if ( !node || node->type != json_array ) return;
    p_result->recordings.p_recordings = calloc( node->u.array.length, sizeof(acoustid_mb_result_t) );
    if ( ! p_result->recordings.p_recordings ) return;
    p_result->recordings.count = node->u.array.length;

    for( unsigned int i=0; i<node->u.array.length; i++ )
    {
        acoustid_mb_result_t *record = & p_result->recordings.p_recordings[ i ];
        const json_value *recordnode = node->u.array.values[ i ];
        if ( !recordnode || recordnode->type != json_object )
            break;
        record->psz_title = json_dupstring( recordnode, "title" );
        const json_value *value = json_getbyname( recordnode, "id" );
        if ( value && value->type == json_string )
        {
            size_t i_len = strlen( value->u.string.ptr );
            i_len = __MIN( i_len, MB_ID_SIZE );
            memcpy( record->s_musicbrainz_id, value->u.string.ptr, i_len );
        }
        parse_artists( json_getbyname( recordnode, "artists" ), record );
        msg_Dbg( p_obj, "recording %d title %s %36s %s", i, record->psz_title,
                 record->s_musicbrainz_id, record->psz_artist );
    }
}