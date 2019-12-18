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
struct vlc_stream_memory_private {size_t i_size; size_t i_pos; size_t p_buffer; } ;
typedef  int /*<<< orphan*/  stream_t ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,size_t,size_t) ; 
 struct vlc_stream_memory_private* vlc_stream_Private (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t Read( stream_t *s, void *p_read, size_t i_read )
{
    struct vlc_stream_memory_private *p_sys = vlc_stream_Private(s);

    if( i_read > p_sys->i_size - p_sys->i_pos )
        i_read = p_sys->i_size - p_sys->i_pos;
    if ( p_read )
        memcpy( p_read, p_sys->p_buffer + p_sys->i_pos, i_read );
    p_sys->i_pos += i_read;
    return i_read;
}