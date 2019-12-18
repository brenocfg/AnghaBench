#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {long i_index_size; char* p_index; int i_index_payload; int /*<<< orphan*/  i_index_count; } ;
struct TYPE_5__ {TYPE_1__ skeleton; int /*<<< orphan*/  i_length; int /*<<< orphan*/  i_serial_no; } ;
typedef  TYPE_2__ ogg_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_FREQ ; 
 long INDEX_BASE_SIZE ; 
 int /*<<< orphan*/  SetDWLE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetQWLE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * calloc (long,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void OggGetSkeletonIndex( uint8_t **pp_buffer, long *pi_size, ogg_stream_t *p_stream )
{
    uint8_t *p_buffer = calloc( INDEX_BASE_SIZE + p_stream->skeleton.i_index_size, sizeof(uint8_t) );
    if ( !p_buffer ) return;
    *pp_buffer = p_buffer;

    memcpy( p_buffer, "index", 6 );
    SetDWLE( &p_buffer[6], p_stream->i_serial_no );
    SetQWLE( &p_buffer[10], p_stream->skeleton.i_index_count ); /* num keypoints */
    SetQWLE( &p_buffer[18], CLOCK_FREQ );
    SetQWLE( &p_buffer[34], p_stream->i_length );
    memcpy( p_buffer + INDEX_BASE_SIZE, p_stream->skeleton.p_index, p_stream->skeleton.i_index_payload );
    *pi_size = INDEX_BASE_SIZE + p_stream->skeleton.i_index_size;
}