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
struct vlc_memstream {int /*<<< orphan*/ * stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_memstream_putc (struct vlc_memstream*,char) ; 
 int /*<<< orphan*/  vlc_memstream_puts (struct vlc_memstream*,char const*) ; 

__attribute__((used)) static void memstream_Append( struct vlc_memstream *ms, const char *psz )
{
    if( ms->stream != NULL )
    {
        vlc_memstream_puts( ms, psz );
        vlc_memstream_putc( ms, '\n' );
    }
}