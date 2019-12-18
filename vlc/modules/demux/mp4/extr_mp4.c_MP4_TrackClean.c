#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * p_array; } ;
struct TYPE_8__ {TYPE_2__ runs; } ;
struct TYPE_6__ {scalar_t__ p_frame; } ;
struct TYPE_9__ {unsigned int i_chunk_count; TYPE_3__ context; TYPE_1__ asfinfo; int /*<<< orphan*/ * p_sample_size; int /*<<< orphan*/  i_sample_size; int /*<<< orphan*/ * chunk; scalar_t__ p_es; int /*<<< orphan*/  fmt; } ;
typedef  TYPE_4__ mp4_track_t ;
typedef  int /*<<< orphan*/  es_out_t ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyChunk (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  block_ChainRelease (scalar_t__) ; 
 int /*<<< orphan*/  es_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  es_out_Del (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void MP4_TrackClean( es_out_t *out, mp4_track_t *p_track )
{
    es_format_Clean( &p_track->fmt );

    if( p_track->p_es )
        es_out_Del( out, p_track->p_es );

    if( p_track->chunk )
    {
        for( unsigned int i_chunk = 0; i_chunk < p_track->i_chunk_count; i_chunk++ )
            DestroyChunk( &p_track->chunk[i_chunk] );
    }
    free( p_track->chunk );

    if( !p_track->i_sample_size )
        free( p_track->p_sample_size );

    if ( p_track->asfinfo.p_frame )
        block_ChainRelease( p_track->asfinfo.p_frame );

    free( p_track->context.runs.p_array );
}