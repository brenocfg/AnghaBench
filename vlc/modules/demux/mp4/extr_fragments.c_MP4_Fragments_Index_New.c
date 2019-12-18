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
struct TYPE_5__ {unsigned int i_entries; unsigned int i_tracks; scalar_t__ i_last_time; void* pi_pos; void* p_times; } ;
typedef  TYPE_1__ mp4_fragments_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP4_Fragments_Index_Delete (TYPE_1__*) ; 
 unsigned int SIZE_MAX ; 
 void* calloc (unsigned int,int) ; 
 TYPE_1__* malloc (int) ; 

mp4_fragments_index_t * MP4_Fragments_Index_New( unsigned i_tracks, unsigned i_num )
{
    if( !i_tracks || !i_num || SIZE_MAX / i_num < i_tracks )
        return NULL;
    mp4_fragments_index_t *p_index = malloc( sizeof(*p_index) );
    if( p_index )
    {
        p_index->p_times = calloc( (size_t)i_num * i_tracks, sizeof(*p_index->p_times) );
        p_index->pi_pos = calloc( i_num, sizeof(*p_index->pi_pos) );
        if( !p_index->p_times || !p_index->pi_pos )
        {
            MP4_Fragments_Index_Delete( p_index );
            return NULL;
        }
        p_index->i_entries = i_num;
        p_index->i_last_time = 0;
        p_index->i_tracks = i_tracks;
    }
    return p_index;
}