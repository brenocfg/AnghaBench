#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  stream_t ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_stream_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_stream_MemoryNew (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const,int) ; 
 scalar_t__ vlc_stream_Peek (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int) ; 
 char* vlc_stream_ReadLine (int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_stream_Tell (int /*<<< orphan*/ *) ; 

__attribute__((used)) inline static char * peek_Readline( stream_t *p_demuxstream, uint64_t *pi_offset )
{
    uint8_t *p_peek;
    ssize_t i_peek = vlc_stream_Peek( p_demuxstream, (const uint8_t **) &p_peek,
                                  *pi_offset + 2048 );
    if( i_peek < 0 || (uint64_t) i_peek < *pi_offset )
        return NULL;

    const uint64_t i_bufsize = (uint64_t) i_peek - *pi_offset;
    char *psz_line = NULL;

    /* Create a stream memory from that offset */
    stream_t *p_memorystream = vlc_stream_MemoryNew( p_demuxstream,
                                                     &p_peek[*pi_offset],
                                                     i_bufsize, true );
    if( p_memorystream )
    {
        psz_line = vlc_stream_ReadLine( p_memorystream );

        *pi_offset += vlc_stream_Tell( p_memorystream );
        vlc_stream_Delete( p_memorystream );
    }

    return psz_line;
}