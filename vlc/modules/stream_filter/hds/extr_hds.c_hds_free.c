#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int server_entry_count; TYPE_2__* chunks_head; int /*<<< orphan*/ * server_entries; int /*<<< orphan*/  movie_id; int /*<<< orphan*/  url; int /*<<< orphan*/  metadata; int /*<<< orphan*/  abst_url; int /*<<< orphan*/  quality_segment_modifier; } ;
typedef  TYPE_1__ hds_stream_t ;
struct TYPE_8__ {struct TYPE_8__* next; } ;
typedef  TYPE_2__ chunk_t ;

/* Variables and functions */
 int /*<<< orphan*/  FREENULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chunk_free (TYPE_2__*) ; 
 int /*<<< orphan*/  cleanup_threading (TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void hds_free( hds_stream_t *p_stream )
{
    FREENULL( p_stream->quality_segment_modifier );

    FREENULL( p_stream->abst_url );

    cleanup_threading( p_stream );

    FREENULL( p_stream->metadata );
    FREENULL( p_stream->url );
    FREENULL( p_stream->movie_id );
    for( int i = 0; i < p_stream->server_entry_count; i++ )
    {
        FREENULL( p_stream->server_entries[i] );
    }

    chunk_t* chunk = p_stream->chunks_head;
    while( chunk )
    {
        chunk_t* next = chunk->next;
        chunk_free( chunk );
        chunk = next;
    }

    free( p_stream );
}