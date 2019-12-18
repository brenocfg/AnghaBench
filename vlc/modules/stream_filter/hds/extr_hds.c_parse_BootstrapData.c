#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_5__ {scalar_t__ server_entry_count; scalar_t__ fragment_run_count; scalar_t__ segment_run_count; int /*<<< orphan*/ * quality_segment_modifier; void** server_entries; void* movie_id; int /*<<< orphan*/  live_current_time; void* timescale; } ;
typedef  TYPE_1__ hds_stream_t ;
typedef  int /*<<< orphan*/  abst_len ;

/* Variables and functions */
 scalar_t__ MAX_HDS_SERVERS ; 
 void* U32_AT (int*) ; 
 int /*<<< orphan*/  U64_AT (int*) ; 
 int* memchr (int*,char,int) ; 
 scalar_t__ memcmp (int*,char*,int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*) ; 
 int* parse_afrt (int /*<<< orphan*/ *,TYPE_1__*,int*,int*) ; 
 int* parse_asrt (int /*<<< orphan*/ *,TYPE_1__*,int*,int*) ; 
 scalar_t__ strlen (void*) ; 
 void* strndup (char*,int) ; 
 scalar_t__ strnlen (char*,int) ; 

__attribute__((used)) static void parse_BootstrapData( vlc_object_t* p_this,
                                 hds_stream_t * s,
                                 uint8_t* data,
                                 uint8_t* data_end )
{
    uint8_t* data_p = data;

    uint32_t abst_len = U32_AT( data_p );
    if( abst_len > data_end - data
        || data_end - data < 29 /* min size of data */ )
    {
        msg_Warn( p_this, "Not enough bootstrap data" );
        return;
    }
    data_p += sizeof(abst_len);

    if( 0 != memcmp( data_p, "abst", 4 ) )
    {
        msg_Warn( p_this, "Cant find abst in bootstrap" );
        return;
    }
    data_p += 4;

    /* version, flags*/
    data_p += 4;

    /* we ignore the version */
    data_p += 4;

    /* some flags we don't care about here because they are
     * in the manifest
     */
    data_p += 1;

    /* timescale */
    s->timescale = U32_AT( data_p );
    data_p += sizeof(s->timescale);

    s->live_current_time = U64_AT( data_p );
    data_p += sizeof(s->live_current_time);

    /* smtpe time code offset */
    data_p += 8;

    s->movie_id = strndup( (char*)data_p, data_end - data_p );
    data_p += ( strlen( s->movie_id ) + 1 );

    if( data_end - data_p < 4 ) {
        msg_Warn( p_this, "Not enough bootstrap after Movie Identifier" );
        return;
    }

    uint8_t server_entry_count = 0;
    server_entry_count = (uint8_t) *data_p;
    data_p++;

    s->server_entry_count = 0;
    while( server_entry_count-- > 0 )
    {
        if( s->server_entry_count < MAX_HDS_SERVERS )
        {
            s->server_entries[s->server_entry_count++] = strndup( (char*)data_p,
                                                                  data_end - data_p );
            data_p += strlen( s->server_entries[s->server_entry_count-1] ) + 1;
        }
        else
        {
            msg_Warn( p_this, "Too many servers" );
            data_p = memchr( data_p, '\0', data_end - data_p );
            if( ! data_p )
            {
                msg_Err( p_this, "Couldn't find server entry" );
                return;
            }
            data_p++;
        }

        if( data_p >= data_end )
        {
            msg_Warn( p_this, "Premature end of bootstrap info while reading servers" );
            return;
        }
    }

    if( data_end - data_p < 3 ) {
        msg_Warn( p_this, "Not enough bootstrap after Servers" );
        return;
    }

    s->quality_segment_modifier = NULL;

    uint8_t quality_entry_count = *data_p;
    data_p++;

    if( quality_entry_count > 1 )
    {
        msg_Err( p_this, "I don't know what to do with multiple quality levels in the bootstrap - shouldn't this be handled at the manifest level?" );
        return;
    }

    s->quality_segment_modifier = NULL;
    while( quality_entry_count-- > 0 )
    {
        if( s->quality_segment_modifier )
        {
            s->quality_segment_modifier = strndup( (char*)data_p, data_end - data_p );
        }
        data_p += strnlen( (char*)data_p, data_end - data_p ) + 1;
    }

    if( data_end - data_p < 2 ) {
        msg_Warn( p_this, "Not enough bootstrap after quality entries" );
        return;
    }

    /* ignoring "DrmData" */
    data_p = memchr( data_p, '\0', data_end - data_p );
    if( ! data_p )
    {
        msg_Err( p_this, "Couldn't find DRM Data" );
        return;
    }
    data_p++;

    if( data_end - data_p < 2 ) {
        msg_Warn( p_this, "Not enough bootstrap after drm data" );
        return;
    }

    /* ignoring "metadata" */
    data_p = memchr( data_p, '\0', data_end - data_p );
    if( ! data_p )
    {
        msg_Err( p_this, "Couldn't find metadata");
        return;
    }
    data_p++;

    if( data_end - data_p < 2 ) {
        msg_Warn( p_this, "Not enough bootstrap after drm data" );
        return;
    }

    uint8_t asrt_count = *data_p;
    data_p++;

    s->segment_run_count = 0;
    while( asrt_count-- > 0 &&
           data_end > data_p &&
           (data_p = parse_asrt( p_this, s, data_p, data_end )) );

    if( ! data_p )
    {
        msg_Warn( p_this, "Couldn't find afrt data" );
        return;
    }

    uint8_t afrt_count = *data_p;
    data_p++;

    s->fragment_run_count = 0;
    while( afrt_count-- > 0 &&
           data_end > data_p &&
           (data_p = parse_afrt( p_this, s, data_p, data_end )) );
}