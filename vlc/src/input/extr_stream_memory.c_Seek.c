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
typedef  scalar_t__ uint64_t ;
struct vlc_stream_memory_private {scalar_t__ i_size; scalar_t__ i_pos; } ;
typedef  int /*<<< orphan*/  stream_t ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 struct vlc_stream_memory_private* vlc_stream_Private (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int Seek( stream_t *s, uint64_t offset )
{
    struct vlc_stream_memory_private *p_sys = vlc_stream_Private(s);

    if( offset > p_sys->i_size )
        offset = p_sys->i_size;

    p_sys->i_pos = offset;
    return VLC_SUCCESS;
}