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
typedef  int /*<<< orphan*/  stream_t ;

/* Variables and functions */
 int vlc_stream_Read (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int StreamRead( void *p_context, char *p_buffer, int i_buffer )
{
    stream_t *s = (stream_t*)p_context;
    return vlc_stream_Read( s, p_buffer, i_buffer );
}