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
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,void*) ; 
 int /*<<< orphan*/ * vlc_stream_FilterNew (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

stream_t *stream_FilterAutoNew( stream_t *p_source )
{
    /* Limit number of entries to avoid infinite recursion. */
    for( unsigned i = 0; i < 16; i++ )
    {
        stream_t *p_filter = vlc_stream_FilterNew( p_source, NULL );
        if( p_filter == NULL )
            break;

        msg_Dbg( p_filter, "stream filter added to %p", (void *)p_source );
        p_source = p_filter;
    }
    return p_source;
}