#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_6__ {scalar_t__ i_length; } ;
typedef  TYPE_1__ block_t ;
struct TYPE_7__ {scalar_t__ size; scalar_t__ data; } ;
typedef  TYPE_2__ AVPacket ;

/* Variables and functions */
 int VLC_TICK_FROM_MS (int) ; 
 size_t __MIN (int,scalar_t__) ; 
 scalar_t__ asprintf (char**,char*,unsigned int,int,scalar_t__,scalar_t__) ; 
 TYPE_1__* block_heap_Alloc (char*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,size_t const) ; 
 int sscanf (char*,char*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ vlc_tick_from_sec (int) ; 

__attribute__((used)) static block_t *BuildSsaFrame( const AVPacket *p_pkt, unsigned i_order )
{
    if( p_pkt->size <= 0 )
        return NULL;

    char buffer[256];
    const size_t i_buffer_size = __MIN( (int)sizeof(buffer) - 1, p_pkt->size );
    memcpy( buffer, p_pkt->data, i_buffer_size );
    buffer[i_buffer_size] = '\0';

    /* */
    int i_layer;
    int h0, m0, s0, c0;
    int h1, m1, s1, c1;
    int i_position = 0;
    if( sscanf( buffer, "Dialogue: %d,%d:%d:%d.%d,%d:%d:%d.%d,%n", &i_layer,
                &h0, &m0, &s0, &c0, &h1, &m1, &s1, &c1, &i_position ) < 9 )
        return NULL;
    if( i_position <= 0 || (unsigned)i_position >= i_buffer_size )
        return NULL;

    char *p;
    if( asprintf( &p, "%u,%d,%.*s", i_order, i_layer, p_pkt->size - i_position, p_pkt->data + i_position ) < 0 )
        return NULL;

    block_t *p_frame = block_heap_Alloc( p, strlen(p) + 1 );
    if( p_frame )
        p_frame->i_length = vlc_tick_from_sec((h1-h0) * 3600 +
                                         (m1-m0) * 60 +
                                         (s1-s0) * 1) +
                             VLC_TICK_FROM_MS (c1-c0) / 100;
    return p_frame;
}