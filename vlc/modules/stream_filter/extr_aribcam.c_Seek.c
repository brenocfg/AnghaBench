#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  p_sys; int /*<<< orphan*/  s; } ;
typedef  TYPE_1__ stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  RemainFlush (int /*<<< orphan*/ ) ; 
 int VLC_SUCCESS ; 
 int vlc_stream_Seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int Seek( stream_t *p_stream, uint64_t i_pos )
{
    int i_ret = vlc_stream_Seek( p_stream->s, i_pos );
    if ( i_ret == VLC_SUCCESS )
        RemainFlush( p_stream->p_sys );
    return i_ret;
}