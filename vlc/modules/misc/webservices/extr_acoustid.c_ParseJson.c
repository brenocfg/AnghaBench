#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_17__ {unsigned int length; TYPE_4__ const** values; } ;
struct TYPE_16__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_18__ {int /*<<< orphan*/  dbl; TYPE_2__ array; TYPE_1__ string; } ;
struct TYPE_19__ {scalar_t__ type; TYPE_3__ u; } ;
typedef  TYPE_4__ const json_value ;
struct TYPE_20__ {unsigned int count; TYPE_6__* p_results; } ;
typedef  TYPE_5__ acoustid_results_t ;
struct TYPE_21__ {int /*<<< orphan*/  psz_id; int /*<<< orphan*/  d_score; } ;
typedef  TYPE_6__ acoustid_result_t ;

/* Variables and functions */
 TYPE_6__* calloc (unsigned int,int) ; 
 scalar_t__ json_array ; 
 scalar_t__ json_double ; 
 int /*<<< orphan*/  json_dupstring (TYPE_4__ const*,char*) ; 
 TYPE_4__ const* json_getbyname (TYPE_4__ const*,char*) ; 
 scalar_t__ json_object ; 
 TYPE_4__ const* json_parse_document (int /*<<< orphan*/ *,void const*) ; 
 scalar_t__ json_string ; 
 int /*<<< orphan*/  json_value_free (TYPE_4__ const*) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  parse_recordings (int /*<<< orphan*/ *,TYPE_4__ const*,TYPE_6__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool ParseJson( vlc_object_t *p_obj, const void *p_buffer, acoustid_results_t *p_results )
{
    json_value *root = json_parse_document( p_obj, p_buffer );
    if( !root )
        return false;

    const json_value *node = json_getbyname( root, "status" );
    if ( !node || node->type != json_string )
    {
        msg_Warn( p_obj, "status node not found or invalid" );
        goto error;
    }
    if ( strcmp( node->u.string.ptr, "ok" ) != 0 )
    {
        msg_Warn( p_obj, "Bad request status" );
        goto error;
    }
    node = json_getbyname( root, "results" );
    if ( !node || node->type != json_array )
    {
        msg_Warn( p_obj, "Bad results array or no results" );
        goto error;
    }
    p_results->p_results = calloc( node->u.array.length, sizeof(acoustid_result_t) );
    if ( ! p_results->p_results ) goto error;
    p_results->count = node->u.array.length;
    for( unsigned int i=0; i<node->u.array.length; i++ )
    {
        const json_value *resultnode = node->u.array.values[i];
        if ( resultnode && resultnode->type == json_object )
        {
            acoustid_result_t *p_result = & p_results->p_results[i];
            const json_value *value = json_getbyname( resultnode, "score" );
            if ( value && value->type == json_double )
                p_result->d_score = value->u.dbl;
            p_result->psz_id = json_dupstring( resultnode, "id" );
            parse_recordings( p_obj, json_getbyname( resultnode, "recordings" ), p_result );
        }
    }
    json_value_free( root );
    return true;

error:
    if ( root ) json_value_free( root );
    return false;
}